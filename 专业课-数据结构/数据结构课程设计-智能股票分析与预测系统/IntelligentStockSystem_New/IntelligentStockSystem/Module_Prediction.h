#define _CRT_SECURE_NO_WARNINGS
#pragma once
#include "EncodingUtils.h"
// ... includes
#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>
using namespace std;

namespace Level_18 {
    // 第18关 (皮尔逊相关系数)
    // 定义最大数组大小
    const int MAX_STOCK_DATA = 1000;
    const int MAX_LABELS = MAX_STOCK_DATA - 1;
    const int MAX_INDICATOR_SIZE = MAX_LABELS;
    const int MAX_INDICATORS = 5;

    typedef struct StockDetail {
        string date;          // 日期
        double openPrice;     // 开盘价
        double closePrice;    // 收盘价
        double highest;       // 最高价
        double lowest;        // 最低价
        double volume;        // 成交量
        double turnover;      // 成交额
        string changeRate;    // 换手率
        string riseFallRate;  // 涨跌幅
        double riseFallAmount;// 涨跌额
    } StockDetail;

    struct IndicatorScore {
        string name;       // 指标名称
        double corrScore;  // 皮尔逊相关系数（绝对值）
    };

    bool LoadStockFromFile(const string& filename, StockDetail detailsList[], int& count) {
        // 从文件加载股票数据，返回是否成功
        ifstream file(filename);
        if (!file.is_open()) {
            return false;
        }

        count = 0;
        string line;
        while (getline(file, line) && count < MAX_STOCK_DATA) {
            if (line.empty()) continue;

            stringstream ss(line);
            vector<string> tokens;
            string token;

            while (getline(ss, token, ';')) {
                tokens.push_back(token);
            }

            if (tokens.size() >= 9) {
                try {
                    detailsList[count].date = tokens[0];
                    detailsList[count].openPrice = stod(tokens[1]);
                    detailsList[count].closePrice = stod(tokens[2]);
                    detailsList[count].highest = stod(tokens[3]);
                    detailsList[count].lowest = stod(tokens[4]);
                    detailsList[count].volume = stod(tokens[5]);
                    detailsList[count].turnover = stod(tokens[6]);
                    detailsList[count].changeRate = tokens[7];
                    detailsList[count].riseFallRate = tokens[8];
                    count++;
                }
                catch (const exception& e) {
                    continue;
                }
            }
        }
        file.close();
        return count > 1;
    }

    void CreatePriceLabels(const StockDetail detailsList[], int count, int labels[], int& labelCount) {
        // 创建价格变动标签（1上涨，0下跌）
        labelCount = 0;

        // 数据按"最新日期在前"存储：索引0=最新日期，索引1=前一天，索引2=前两天...
        // 用第i天的数据预测第i-1天的涨跌（因为第i-1天是第i天的"次日"）
        for (int i = 1; i < count; i++) {
            // 比较第i天（较新）和第i-1天（较旧）的收盘价
            if (detailsList[i - 1].closePrice > detailsList[i].closePrice) {
                labels[labelCount] = 1; // 上涨
            }
            else {
                labels[labelCount] = 0; // 下跌
            }
            labelCount++;
        }
    }

    double ComputeCorrelationScore(const double indicator[], const int labels[], int n,
        double& sumX, double& sumY, double& sumXY) {
        // 计算指标与标签的皮尔逊相关系数绝对值
        if (n <= 1) return 0.0;

        // 重新初始化所有累加变量
        sumX = 0.0, sumY = 0.0, sumXY = 0.0;
        double sumX2 = 0.0, sumY2 = 0.0;

        // 计算各项和
        for (int i = 0; i < n; i++) {
            double x = indicator[i];
            double y = labels[i];
            sumX += x;
            sumY += y;
            sumXY += x * y;
            sumX2 += x * x;
            sumY2 += y * y;
        }

        // 计算皮尔逊相关系数
        double numerator = n * sumXY - sumX * sumY;
        double denominator1 = n * sumX2 - sumX * sumX;
        double denominator2 = n * sumY2 - sumY * sumY;

        if (denominator1 <= 0 || denominator2 <= 0) {
            return 0.0;
        }

        double denominator = sqrt(denominator1 * denominator2);

        if (denominator == 0) return 0.0;

        double correlation = numerator / denominator;

        return abs(correlation);
    }

    void GetRiseFallRates(const StockDetail detailsList[], int count, double indicator[], int& indicatorCount) {
        // 获取涨跌幅指标数据（%）
        indicatorCount = 0;
        // 跳过最新一天，因为它的次日涨跌未知
        for (int i = 1; i < count; i++) {
            string rateStr = detailsList[i].riseFallRate;
            // 去除百分号并转换为数值
            if (!rateStr.empty()) {
                if (rateStr.back() == '%') {
                    rateStr.pop_back();
                }
                try {
                    indicator[indicatorCount] = stod(rateStr);
                    indicatorCount++;
                }
                catch (const exception& e) {
                    // 跳过转换错误的数据
                    continue;
                }
            }
        }
    }

    void GetVolumesInWanShou(const StockDetail detailsList[], int count, double indicator[], int& indicatorCount) {
        // 获取成交量指标数据（转换为万手）
        indicatorCount = 0;
        for (int i = 1; i < count; i++) {
            // 成交量转换为万手（1手=100股，1万手=10000手）
            indicator[indicatorCount] = detailsList[i].volume / 10000.0;
            indicatorCount++;
        }
    }

    void GetAmplitudes(const StockDetail detailsList[], int count, double indicator[], int& indicatorCount) {
        // 计算振幅指标数据（%）
        indicatorCount = 0;
        for (int i = 1; i < count; i++) {
            double amplitude = (detailsList[i].highest - detailsList[i].lowest) / detailsList[i].openPrice * 100.0;
            indicator[indicatorCount] = amplitude;
            indicatorCount++;
        }
    }

    void GetTurnoverRates(const StockDetail detailsList[], int count, double indicator[], int& indicatorCount) {
        // 获取换手率指标数据（%）
        indicatorCount = 0;
        for (int i = 1; i < count; i++) {
            string rateStr = detailsList[i].changeRate;
            if (!rateStr.empty()) {
                if (rateStr.back() == '%') {
                    rateStr.pop_back();
                }
                try {
                    indicator[indicatorCount] = stod(rateStr);
                    indicatorCount++;
                }
                catch (const exception& e) {
                    continue;
                }
            }
        }
    }

    void GetTurnoverInQianWan(const StockDetail detailsList[], int count, double indicator[], int& indicatorCount) {
        // 获取成交额指标数据（转换为千万元）
        indicatorCount = 0;
        for (int i = 1; i < count; i++) {
            // 成交额转换为千万元
            indicator[indicatorCount] = detailsList[i].turnover / 10000000.0;
            indicatorCount++;
        }
    }

    void SortIndicatorScores(IndicatorScore scores[], int count, bool descending) {
        // 对指标相关系数进行排序（降序/升序）
        for (int i = 0; i < count - 1; i++) {
            for (int j = 0; j < count - i - 1; j++) {
                if (descending) {
                    if (scores[j].corrScore < scores[j + 1].corrScore) {
                        IndicatorScore temp = scores[j];
                        scores[j] = scores[j + 1];
                        scores[j + 1] = temp;
                    }
                }
                else {
                    if (scores[j].corrScore > scores[j + 1].corrScore) {
                        IndicatorScore temp = scores[j];
                        scores[j] = scores[j + 1];
                        scores[j + 1] = temp;
                    }
                }
            }
        }
    }
    void run() {
        cout << "=== 功能：基于皮尔逊相关系数的指标重要性分析 ===" << endl;
        //cout << "请输入数据文件名(例如 data/detail/000001.txt): ";
        // ...
        StockDetail detailsList[MAX_STOCK_DATA];
        int labels[MAX_LABELS];
        string inputFile;
        
        int detailCount = 0;
        int labelCount = 0;
        cout << "请输入数据文件名(例如cn_000007.txt): " << endl;
        cin >> inputFile;
        string filename = "data/detail/" + inputFile;
        if (!LoadStockFromFile(filename, detailsList, detailCount)) {
            cerr << "Error: 数据读取失败或有效数据量不足" << endl;
            return;
        }
        
        CreatePriceLabels(detailsList, detailCount, labels, labelCount);

        if (labelCount == 0) {
            cerr << "Error: 标签生成失败" << endl;
            return;
        }

        // 指标名称数组
        string indicatorNames[MAX_INDICATORS] = {
            "涨跌幅（%）", "成交量（万手）", "振幅（%）", "换手率（%）", "成交额（千万元）"
        };

        IndicatorScore indicatorScores[MAX_INDICATORS];
        double sumX, sumY, sumXY;
        double indicator[MAX_INDICATOR_SIZE];
        int indicatorCount = 0;

        // 计算各个指标的相关系数
        GetRiseFallRates(detailsList, detailCount, indicator, indicatorCount);
        indicatorScores[0] = { indicatorNames[0],
            ComputeCorrelationScore(indicator, labels, indicatorCount, sumX, sumY, sumXY) };

        GetVolumesInWanShou(detailsList, detailCount, indicator, indicatorCount);
        indicatorScores[1] = { indicatorNames[1],
            ComputeCorrelationScore(indicator, labels, indicatorCount, sumX, sumY, sumXY) };

        GetAmplitudes(detailsList, detailCount, indicator, indicatorCount);
        indicatorScores[2] = { indicatorNames[2],
            ComputeCorrelationScore(indicator, labels, indicatorCount, sumX, sumY, sumXY) };

        GetTurnoverRates(detailsList, detailCount, indicator, indicatorCount);
        indicatorScores[3] = { indicatorNames[3],
            ComputeCorrelationScore(indicator, labels, indicatorCount, sumX, sumY, sumXY) };

        GetTurnoverInQianWan(detailsList, detailCount, indicator, indicatorCount);
        indicatorScores[4] = { indicatorNames[4],
            ComputeCorrelationScore(indicator, labels, indicatorCount, sumX, sumY, sumXY) };

        SortIndicatorScores(indicatorScores, MAX_INDICATORS, true);

        // 输出
        cout << "=== 股票指标重要性排序（基于皮尔逊相关系数）===" << endl;
        cout << fixed << setprecision(3);
        cout << "排名 | 指标名称 | 相关系数" << endl;
        cout << "----------------------------------------" << endl;
        for (int i = 0; i < MAX_INDICATORS; ++i) {
            cout << i + 1 << " | "
                << indicatorScores[i].name << " | "
                << indicatorScores[i].corrScore << endl;
        }

        cout << "\n=== 筛选出的Top3重要指标 ===" << endl;
        cout << "排名 | 指标名称" << endl;
        cout << "------------------------" << endl;
        for (int i = 0; i < 3 && i < MAX_INDICATORS; ++i) {
            cout << setw(2) << i + 1 << "  | " << indicatorScores[i].name << endl;
        }

    }
}

namespace Level_19 {
    // 第19关 (朴素贝叶斯)
    // 定义最大数组大小
    const int MAX_SAMPLES = 1000;
    const int MAX_FEATURES = 3;
    const int MAX_NODE_COUNT = 5;

    struct Sample {
        string currentDate;
        double features[MAX_FEATURES];
        int label;
        int featureCount;
    };

    // 节点类型：特征节点 / 标签节点
    enum NodeType { FEATURE, LABEL };

    // 边的参数结构体（存储高斯分布的均值和方差）
    struct EdgeParams {
        double mean = 0.0;       // 均值（初始化为0）
        double variance = 1e-6;  // 方差（默认最小阈值，避免除以0）
        bool exists = false;     // 标记边是否存在
    };

    // 贝叶斯网络图结构体
    struct BayesianGraph {
        string nodeNames[MAX_NODE_COUNT] = { "涨跌幅", "振幅", "成交额", "跌", "涨" };
        NodeType nodeTypes[MAX_NODE_COUNT] = { FEATURE, FEATURE, FEATURE, LABEL, LABEL };
        int nodeCount = MAX_NODE_COUNT;
        EdgeParams adj[MAX_NODE_COUNT][MAX_NODE_COUNT];
        double prior[2] = { 0.0, 0.0 };

        // 构造函数：初始化邻接矩阵
        BayesianGraph() {
            for (int i = 0; i < 3; ++i) {
                for (int j = 3; j < 5; ++j) {
                    adj[i][j].exists = true;
                }
            }
        }

        int FindNodeIndex(NodeType type, int index = -1) const {
            // 查找节点索引
            if (type == FEATURE) {
                if (index >= 0 && index < 3) {
                    return index;
                }
                return -1;
            }
            else { // LABEL
                if (index == 0) return 3; // 跌
                if (index == 1) return 4; // 涨
                return -1;
            }
        }

        void ComputePriorProbabilities(const Sample samples[], int sampleCount) {
            // 计算先验概率
            int countRise = 0;
            int countFall = 0;

            for (int i = 0; i < sampleCount; i++) {
                if (samples[i].label == 1) {
                    countRise++;
                }
                else if (samples[i].label == 0) {
                    countFall++;
                }
            }

            prior[1] = (double)countRise / sampleCount; // 涨的先验概率
            prior[0] = (double)countFall / sampleCount; // 跌的先验概率
        }

        void ComputeEdgeMeans(const Sample samples[], int sampleCount) {
            // 计算边的均值
            int countRise = 0;
            int countFall = 0;
            double sumRise[MAX_FEATURES] = { 0 };
            double sumFall[MAX_FEATURES] = { 0 };

            // 计算各类别的特征和
            for (int i = 0; i < sampleCount; i++) {
                if (samples[i].label == 1) {
                    countRise++;
                    for (int j = 0; j < MAX_FEATURES; j++) {
                        sumRise[j] += samples[i].features[j];
                    }
                }
                else if (samples[i].label == 0) {
                    countFall++;
                    for (int j = 0; j < MAX_FEATURES; j++) {
                        sumFall[j] += samples[i].features[j];
                    }
                }
            }

            // 计算均值
            for (int i = 0; i < MAX_FEATURES; i++) {
                int featureNode = FindNodeIndex(FEATURE, i);
                int riseNode = FindNodeIndex(LABEL, 1);
                int fallNode = FindNodeIndex(LABEL, 0);

                if (countRise > 0) {
                    adj[featureNode][riseNode].mean = sumRise[i] / countRise;
                }
                if (countFall > 0) {
                    adj[featureNode][fallNode].mean = sumFall[i] / countFall;
                }
            }
        }

        void ComputeEdgeVariances(const Sample samples[], int sampleCount) {
            // 计算边的方差
            int countRise = 0;
            int countFall = 0;
            double sumSqRise[MAX_FEATURES] = { 0 };
            double sumSqFall[MAX_FEATURES] = { 0 };

            // 计算各类别的特征平方和
            for (int i = 0; i < sampleCount; i++) {
                if (samples[i].label == 1) {
                    countRise++;
                    for (int j = 0; j < MAX_FEATURES; j++) {
                        double diff = samples[i].features[j] - adj[j][4].mean;
                        sumSqRise[j] += diff * diff;
                    }
                }
                else if (samples[i].label == 0) {
                    countFall++;
                    for (int j = 0; j < MAX_FEATURES; j++) {
                        double diff = samples[i].features[j] - adj[j][3].mean;
                        sumSqFall[j] += diff * diff;
                    }
                }
            }

            // 计算方差
            for (int i = 0; i < MAX_FEATURES; i++) {
                int featureNode = FindNodeIndex(FEATURE, i);
                int riseNode = FindNodeIndex(LABEL, 1);
                int fallNode = FindNodeIndex(LABEL, 0);

                if (countRise > 1) {
                    adj[featureNode][riseNode].variance = sumSqRise[i] / (countRise - 1);
                }
                if (countFall > 1) {
                    adj[featureNode][fallNode].variance = sumSqFall[i] / (countFall - 1);
                }

                // 避免方差为0
                if (adj[featureNode][riseNode].variance < 1e-6) {
                    adj[featureNode][riseNode].variance = 1e-6;
                }
                if (adj[featureNode][fallNode].variance < 1e-6) {
                    adj[featureNode][fallNode].variance = 1e-6;
                }
            }
        }

        void Train(const Sample samples[], int sampleCount) {
            // 训练网络
            ComputePriorProbabilities(samples, sampleCount);
            ComputeEdgeMeans(samples, sampleCount);
            ComputeEdgeVariances(samples, sampleCount);
        }

        double CalculateLogProbability(const double features[], int label) const {
            // 计算对数概率
            double logProb = log(prior[label]);

            for (int i = 0; i < MAX_FEATURES; i++) {
                int featureNode = FindNodeIndex(FEATURE, i);
                int labelNode = FindNodeIndex(LABEL, label);

                const EdgeParams& edge = adj[featureNode][labelNode];
                double x = features[i];
                double mean = edge.mean;
                double variance = edge.variance;

                // 高斯概率密度函数的对数
                double exponent = -((x - mean) * (x - mean)) / (2 * variance);
                double M_PI = 3.14159265358979323846;
                double constant = -0.5 * log(2 * M_PI * variance);
                logProb += constant + exponent;
            }

            return logProb;
        }

        int Predict(const double features[]) const {
            // 预测
            double logProbRise = CalculateLogProbability(features, 1);
            double logProbFall = CalculateLogProbability(features, 0);

            return (logProbRise > logProbFall) ? 1 : 0;
        }
    };

    Sample ParseSampleLine(const string& line) {
        // 解析样本数据行
        Sample sample;
        stringstream ss(line);
        string token;
        vector<string> tokens;

        while (getline(ss, token, ';')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 6) {
            sample.currentDate = tokens[0];
            sample.features[0] = stod(tokens[2]); // 涨跌幅
            sample.features[1] = stod(tokens[3]); // 振幅
            sample.features[2] = stod(tokens[4]); // 成交额
            sample.label = stoi(tokens[5]);       // 次日涨跌标签
            sample.featureCount = 3;
        }

        return sample;
    }

    int LoadTrainData(const string& filename, Sample samples[]) {
        // 加载训练数据
        ifstream file(filename);
        if (!file.is_open()) {
            return 0;
        }

        string line;
        int count = 0;

        // 跳过表头
        getline(file, line);

        while (getline(file, line) && count < MAX_SAMPLES) {
            if (line.empty()) continue;

            Sample sample = ParseSampleLine(line);
            samples[count] = sample;
            count++;
        }

        file.close();
        return count;
    }
    void run() {
        cout << "=== 功能：基于朴素贝叶斯分类器的股票涨跌预测 ===" << endl;
        cout << "请输入训练数据文件: ";
        // ...
        string inputFile;
        cout << "请输入数据文件名(例如2_cn_000007.txt): " << endl;
        cin >> inputFile;
        string filename = "data/" + inputFile;
        //getline(cin, inputFile);
        Sample allSamples[MAX_SAMPLES];
        int sampleCount = LoadTrainData(filename, allSamples);
        if (sampleCount < 2) {
            cerr << "数据量不足，至少需要2条数据！" << endl;
            return;
        }

        Sample latest = allSamples[0];
        Sample trainSamples[MAX_SAMPLES];
        int trainCount = 0;
        for (int i = 1; i < sampleCount && trainCount < MAX_SAMPLES; ++i) {
            trainSamples[trainCount++] = allSamples[i];
        }

        BayesianGraph graph;
        graph.Train(trainSamples, trainCount);

        int prediction = graph.Predict(latest.features);

        cout << "=== 预测结果 ===" << endl;
        cout << "日期：" << latest.currentDate << endl;
        cout << "输入指标：" << endl;
        cout << "涨跌幅：" << latest.features[0] << "% | 振幅：" << latest.features[1] << "% | 成交额：" << latest.features[2] << "千万元" << endl;
        cout << "预测结果：" << (prediction == 1 ? "次日上涨" : "次日下跌") << endl;

    }
}

namespace Level_20 {
    // 第20关 (K近邻)

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

    void run() {
        cout << "=== 功能：基于K最近邻算法的股票涨跌幅预测 ===" << endl;
        cout << "请输入数据文件: ";
        // ...
        TradingDay days[MAX_DAYS];
        int labels[MAX_DAYS];
        int dayCount = 0;

        string inputFile;
        //getline(cin, inputFile);
        cout << "请输入数据文件名(例如2_cn_000007.txt): " << endl;
        cin >> inputFile;
        string filename = "data/" + inputFile;
        if (!LoadDataFromFile(filename, days, dayCount, labels)) {
            cerr << "错误：数据加载失败，程序退出" << endl;
            return;
        }

        string targetDate = days[0].date;
        double predictedChange = PredictNextChange(days, dayCount);

        cout << "=== KNN预测结果 ===" << endl;
        cout << "目标日期：" << targetDate << endl;
        cout << "使用指标：当日涨跌幅(%)、振幅(%)、成交额(千万元)" << endl;
        cout << fixed << setprecision(3);
        cout << "预测次日涨跌幅：" << predictedChange << "%" << endl;

    }
}