#include "StockSearch.h"
#include "MenuSystem.h"
#include "DataParser.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// 辅助函数声明
double KNNPredict(const vector<vector<double>>& features, const vector<double>& targets,
    const vector<double>& test, int k);
void PerformKNNPrediction(const Stock& stock);

// 第20关：基于K近邻算法的股票涨跌预测
namespace StockFunctions {
    void knnPrediction() {
        MenuSystem menu;
        system("cls");
        cout << "==========================================" << endl;
        cout << "   基于K近邻算法的股票涨跌预测" << endl;
        cout << "==========================================" << endl;

        // 读取股票数据
        cout << "正在读取股票数据..." << endl;
        vector<Stock> allStocks = DataParser::loadAllCompleteStocks("data/stocks.txt", "data/detail");

        if (allStocks.empty()) {
            menu.showMessage("错误：无法读取股票数据文件或文件为空！");
            return;
        }

        // 选择股票进行分析
        cout << "可用股票列表：" << endl;
        cout << "------------------------------------------" << endl;
        int displayCount = min(10, (int)allStocks.size());
        for (int i = 0; i < displayCount; i++) {
            cout << i + 1 << ". " << allStocks[i].stockCode << " - " << allStocks[i].stockName << endl;
        }

        int stockChoice;
        cout << "请选择要预测的股票 (1-" << displayCount << "): ";
        cin >> stockChoice;

        if (stockChoice < 1 || stockChoice > allStocks.size()) {
            menu.showMessage("无效选择！");
            return;
        }

        Stock selectedStock = allStocks[stockChoice - 1];

        if (selectedStock.details.size() < 10) {
            menu.showMessage("该股票数据不足，至少需要10条交易记录！");
            return;
        }

        cout << "正在分析股票: " << selectedStock.stockName << " (" << selectedStock.stockCode << ")" << endl;

        // 执行KNN预测
        PerformKNNPrediction(selectedStock);

        menu.showMessage(""); // 等待按键
    }
}

// KNN预测实现
void PerformKNNPrediction(const Stock& stock) {
    const int K = 3; // K近邻数量

    // 准备训练数据
    vector<vector<double>> features;
    vector<double> targets;

    // 从股票数据中提取特征和目标值
    for (size_t i = 1; i < stock.details.size(); i++) {
        vector<double> feature;

        // 特征1: 当日涨跌幅
        feature.push_back(stock.details[i].riseFallAmount);

        // 特征2: 振幅
        double amplitude = (stock.details[i].highest - stock.details[i].lowest) / stock.details[i].openPrice * 100.0;
        feature.push_back(amplitude);

        // 特征3: 成交额（标准化）
        feature.push_back(stock.details[i].turnover / 10000000.0); // 千万元

        features.push_back(feature);

        // 目标值：次日涨跌幅（使用前一天的涨跌幅作为目标）
        targets.push_back(stock.details[i - 1].riseFallAmount);
    }

    if (features.empty()) {
        cout << "错误：无法提取有效特征数据！" << endl;
        return;
    }

    // 使用最新数据作为测试样本
    vector<double> testFeatures;
    testFeatures.push_back(stock.details[0].riseFallAmount);
    double amplitude = (stock.details[0].highest - stock.details[0].lowest) / stock.details[0].openPrice * 100.0;
    testFeatures.push_back(amplitude);
    testFeatures.push_back(stock.details[0].turnover / 10000000.0);

    string testDate = stock.details[0].date;

    // KNN预测
    double predictedChange = KNNPredict(features, targets, testFeatures, K);

    // 输出预测结果
    cout << endl << "=== KNN预测结果 ===" << endl;
    cout << "目标日期：" << testDate << endl;
    cout << "使用指标：当日涨跌幅(%)、振幅(%)、成交额(千万元)" << endl;
    cout << fixed << setprecision(3);
    cout << "预测次日涨跌幅：" << predictedChange << "%" << endl;

    // 给出涨跌判断
    string trend = (predictedChange > 0) ? "上涨" : "下跌";
    cout << "趋势判断：预计" << trend << endl;
}

// K近邻预测实现
double KNNPredict(const vector<vector<double>>& features, const vector<double>& targets,
    const vector<double>& test, int k) {
    vector<pair<double, double>> distances; // <距离, 目标值>

    // 计算所有训练样本与测试样本的距离
    for (size_t i = 0; i < features.size(); i++) {
        double distance = 0.0;
        for (size_t j = 0; j < features[i].size(); j++) {
            distance += pow(features[i][j] - test[j], 2);
        }
        distance = sqrt(distance);
        distances.push_back(make_pair(distance, targets[i]));
    }

    // 按距离排序
    sort(distances.begin(), distances.end(),
        [](const pair<double, double>& a, const pair<double, double>& b) {
            return a.first < b.first;
        });

    // 取前k个最近邻的平均值
    double sum = 0.0;
    int count = min(k, (int)distances.size());
    for (int i = 0; i < count; i++) {
        sum += distances[i].second;
    }

    return sum / count;
}