#include <iostream>
#include <cmath>
#include <fstream>
#include <string>
#include <sstream>
#include <iomanip>
#include <algorithm>
#include <vector>

using namespace std;

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

//#include "18-基于皮尔逊相关系数的股票指标重要性分析.h"

int main() {
    StockDetail detailsList[MAX_STOCK_DATA];
    int labels[MAX_LABELS];
    string inputFile;
    int detailCount = 0;
    int labelCount = 0;

    cin >> inputFile;

    if (!LoadStockFromFile(inputFile, detailsList, detailCount)) {
        cerr << "Error: 数据读取失败或有效数据量不足" << endl;
        return 1;
    }
    CreatePriceLabels(detailsList, detailCount, labels, labelCount);

    if (labelCount == 0) {
        cerr << "Error: 标签生成失败" << endl;
        return 1;
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

    return 0;
}