#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>
#include <iomanip>
#include <cstring>
#include <errno.h> 

using namespace std;

#define K_NEIGHBORS 3  // K近邻数量
#define MAX_DAYS 1000  // 最大交易日数量
static double g_minVal[3] = { 0.0, 0.0, 0.0 };
static double g_maxVal[3] = { 1.0, 1.0, 1.0 };
static bool   g_minmax_ready = false;
struct TradingDay {
    string date;               // 当前日期
    double change;             // 当日涨跌幅（%）
    double amplitude;          // 振幅（%）
    double amountMil;          // 成交额（千万元）
    double nextChange;         // 次日涨跌幅（%）
};

struct NeighborNode {
    double distance;           // 与目标样本的距离
    double nextChange;         // 该邻居的次日涨跌幅（%）
    NeighborNode* next;        // 下一个邻居节点

    // 构造函数
    NeighborNode(double d = 0, double nc = 0) : distance(d), nextChange(nc), next(nullptr) {}

    static NeighborNode* createSentinelList() {
        // 创建仅含一个哨兵头结点的链表
        NeighborNode* dummy = new NeighborNode();
        dummy->next = nullptr;
        return dummy;
    }

    void insertOrdered(NeighborNode* dummy, double dist, double nc) {
        // 递增有序插入
        NeighborNode* prev = dummy;
        NeighborNode* cur = dummy->next;
        while (cur && cur->distance <= dist) {
            prev = cur;
            cur = cur->next;
        }
        NeighborNode* node = new NeighborNode(dist, nc);
        node->next = cur;
        prev->next = node;
    }

    void trimList(NeighborNode* dummy) {
        // 仅保留前 K_NEIGHBORS 个节点
        int kept = 0;
        NeighborNode* cur = dummy;
        while (cur && cur->next) {
            ++kept;                       // cur->next 将成为第 kept 个
            if (kept >= K_NEIGHBORS) {    // 下一节点为第 K+1 个，删除其后所有
                NeighborNode* p = cur->next->next;
                while (p) {
                    NeighborNode* q = p->next;
                    delete p;
                    p = q;
                }
                cur->next->next = nullptr;
                return;
            }
            cur = cur->next;
        }
    }

    double calculateAverage(NeighborNode* dummy) {
        //计算邻居节点平均值
        int n = 0;
        double s = 0.0;
        NeighborNode* p = dummy->next;
        while (p && n < K_NEIGHBORS) {
            s += p->nextChange;
            ++n;
            p = p->next;
        }
        if (n == 0) return 0.0;
        return s / n;
    }

    void freeList(NeighborNode* dummy) {
        //释放链表内存
        NeighborNode* p = dummy;
        while (p) {
            NeighborNode* q = p->next;
            delete p;
            p = q;
        }
    }
};

void FindFeatureMinMax(const double features[][3], int featureCount, double minVal[], double maxVal[]) {
    //拆分归一化的最小值/最大值计算
    if (featureCount <= 0) {
        for (int j = 0; j < 3; ++j) { minVal[j] = 0.0; maxVal[j] = 1.0; }
        return;
    }
    for (int j = 0; j < 3; ++j) {
        minVal[j] = features[0][j];
        maxVal[j] = features[0][j];
    }
    for (int i = 1; i < featureCount; ++i) {
        for (int j = 0; j < 3; ++j) {
            if (features[i][j] < minVal[j]) minVal[j] = features[i][j];
            if (features[i][j] > maxVal[j]) maxVal[j] = features[i][j];
        }
    }
}

void NormalizeFeatures(double features[][3], int featureCount) {
    //归一化函数
    double minVal[3], maxVal[3];
    FindFeatureMinMax(features, featureCount, minVal, maxVal);

    // 记录到全局，供目标样本复用
    for (int j = 0; j < 3; ++j) {
        g_minVal[j] = minVal[j];
        g_maxVal[j] = maxVal[j];
    }
    g_minmax_ready = true;

    for (int i = 0; i < featureCount; ++i) {
        for (int j = 0; j < 3; ++j) {
            double denom = (maxVal[j] - minVal[j]);
            features[i][j] = (denom == 0.0) ? 0.0 : (features[i][j] - minVal[j]) / denom;
        }
    }
}

double EuclideanDistance(const double a[], const double b[]) {
    //欧几里得距离计算
    double sum = 0.0;
    for (int i = 0; i < 3; ++i) {
        sum += pow(a[i] - b[i], 2);
    }
    return sqrt(sum);
}

bool ParseTradingLine(const string& line, int lineNum, TradingDay& day, int& label) {
    //解析单行数据
    if (line.empty()) return false;

    string fields[6];
    string token;
    stringstream ss(line);
    int idx = 0;
    while (std::getline(ss, token, ';')) {
        if (idx < 6) fields[idx++] = token;
    }
    if (idx < 6) return false;

    day.date = fields[0];
    try {
        day.change = stod(fields[2]);
        day.amplitude = stod(fields[3]);
        day.amountMil = stod(fields[4]);
    }
    catch (...) {
        return false;
    }
    day.nextChange = 0.0; // 稍后由 SetNextChanges 填充

    try {
        label = stoi(fields[5]);
    }
    catch (...) {
        label = -1;
    }
    return true;
}

void SetNextChanges(TradingDay days[], const int labels[], int dayCount) {
    //设置次日涨跌幅
      // 数据按“最新在前”。对于 i>=1，i 的 nextChange = i-1 的 change
    for (int i = 1; i < dayCount; ++i) {
        days[i].nextChange = days[i - 1].change;
    }
    // days[0]（最新一天）无 nextChange（保持 0）
}

bool LoadDataFromFile(const string& filename, TradingDay days[], int& dayCount, int labels[]) {
    //加载数据
    ifstream fin(filename.c_str());
    if (!fin.is_open()) {
        cerr << "无法打开文件：" << filename << "，错误：" << strerror(errno) << endl;
        return false;
    }
    string line;
    dayCount = 0;

    // 跳过表头
    if (!getline(fin, line)) {
        fin.close();
        return false;
    }

    int lineNum = 1;
    while (getline(fin, line)) {
        ++lineNum;
        TradingDay d;
        int lbl = -1;
        if (!ParseTradingLine(line, lineNum, d, lbl)) continue;
        if (dayCount < MAX_DAYS) {
            days[dayCount] = d;
            labels[dayCount] = lbl;
            ++dayCount;
        }
        else {
            break;
        }
    }
    fin.close();

    SetNextChanges(days, labels, dayCount);
    return (dayCount > 0);
}

void ExtractTrainData(const TradingDay days[], int dayCount, double features[][3], double nextChanges[], int& featureCount) {
    //提取训练数据
    featureCount = 0;
    // 训练集中不包含最新一天（其 nextChange 未知）
    for (int i = 1; i < dayCount; ++i) {
        features[featureCount][0] = days[i].change;
        features[featureCount][1] = days[i].amplitude;
        features[featureCount][2] = days[i].amountMil;
        nextChanges[featureCount] = days[i].nextChange; // 由上一天的 change 填充
        ++featureCount;
    }
}

void NormalizeTargetFeature(const TradingDay days[], double targetFeatures[]) {
    //归一化目标特征
    targetFeatures[0] = days[0].change;
    targetFeatures[1] = days[0].amplitude;
    targetFeatures[2] = days[0].amountMil;

    for (int j = 0; j < 3; ++j) {
        double denom = (g_maxVal[j] - g_minVal[j]);
        targetFeatures[j] = (!g_minmax_ready || denom == 0.0)
            ? 0.0
            : (targetFeatures[j] - g_minVal[j]) / denom;
    }
}

double PredictNextChange(const TradingDay days[], int dayCount) {
    //预测函数
    if (dayCount <= 1) return 0.0;

    static double features[MAX_DAYS][3];
    static double nextChanges[MAX_DAYS];
    int nTrain = 0;

    ExtractTrainData(days, dayCount, features, nextChanges, nTrain);
    if (nTrain <= 0) return 0.0;

    // 训练集归一化并记录 min/max
    NormalizeFeatures(features, nTrain);

    // 归一化目标样本（最新一天）
    double target[3];
    NormalizeTargetFeature(days, target);

    // KNN：用有序链表维护最近 K 个
    NeighborNode* dummy = NeighborNode::createSentinelList();
    for (int i = 0; i < nTrain; ++i) {
        double dist = EuclideanDistance(features[i], target);
        dummy->insertOrdered(dummy, dist, nextChanges[i]);
        dummy->trimList(dummy);
    }

    double pred = dummy->calculateAverage(dummy);
    dummy->freeList(dummy);
    return pred;
}

//#include "20-基于K最近邻算法的股票涨跌幅预测.h"

int main() {
    TradingDay days[MAX_DAYS];
    int labels[MAX_DAYS];
    int dayCount = 0;

    string inputFile;
    getline(cin, inputFile);

    if (!LoadDataFromFile(inputFile, days, dayCount, labels)) {
        cerr << "错误：数据加载失败，程序退出" << endl;
        return 1;
    }

    string targetDate = days[0].date;
    double predictedChange = PredictNextChange(days, dayCount);

    cout << "=== KNN预测结果 ===" << endl;
    cout << "目标日期：" << targetDate << endl;
    cout << "使用指标：当日涨跌幅(%)、振幅(%)、成交额(千万元)" << endl;
    cout << fixed << setprecision(3);
    cout << "预测次日涨跌幅：" << predictedChange << "%" << endl;

    return 0;
}