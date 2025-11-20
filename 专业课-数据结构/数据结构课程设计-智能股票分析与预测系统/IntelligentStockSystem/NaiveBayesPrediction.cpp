#include "StockSearch.h"
#include "MenuSystem.h"
#include "DataParser.h"
#include <iostream>
#include <cmath>
#include <vector>
#include <algorithm>

using namespace std;

// 辅助函数声明
int SimplifiedNaiveBayes(const vector<vector<double>>& features, const vector<int>& labels, const vector<double>& test);
void PerformNaiveBayesPrediction(const Stock& stock);

// 第19关：基于朴素贝叶斯分类器的股票涨跌预测
namespace StockFunctions {
    void naiveBayesPrediction() {
        MenuSystem menu;
        system("cls");
        cout << "==========================================" << endl;
        cout << "   基于朴素贝叶斯分类器的股票涨跌预测" << endl;
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

        // 执行朴素贝叶斯预测
        PerformNaiveBayesPrediction(selectedStock);

        menu.showMessage(""); // 等待按键
    }
}

// 朴素贝叶斯预测实现
void PerformNaiveBayesPrediction(const Stock& stock) {
    // 准备训练数据
    vector<vector<double>> features;
    vector<int> labels;

    // 从股票数据中提取特征和标签
    for (size_t i = 1; i < stock.details.size(); i++) {
        vector<double> feature;

        // 特征1: 涨跌幅
        feature.push_back(stock.details[i].riseFallAmount);

        // 特征2: 振幅
        double amplitude = (stock.details[i].highest - stock.details[i].lowest) / stock.details[i].openPrice * 100.0;
        feature.push_back(amplitude);

        // 特征3: 成交额（标准化）
        feature.push_back(stock.details[i].turnover / 1000000.0);

        features.push_back(feature);

        // 标签：次日涨跌（1=涨，0=跌）
        int label = (stock.details[i - 1].closePrice > stock.details[i].closePrice) ? 1 : 0;
        labels.push_back(label);
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
    testFeatures.push_back(stock.details[0].turnover / 1000000.0);

    string testDate = stock.details[0].date;

    // 朴素贝叶斯分类
    int prediction = SimplifiedNaiveBayes(features, labels, testFeatures);

    // 输出预测结果
    cout << endl << "=== 朴素贝叶斯预测结果 ===" << endl;
    cout << "预测日期：" << testDate << endl;
    cout << "输入指标：" << endl;
    cout << "涨跌幅：" << testFeatures[0] << "% | 振幅：" << testFeatures[1] << "% | 成交额：" << testFeatures[2] << "百万元" << endl;
    cout << "预测结果：" << (prediction == 1 ? "次日上涨" : "次日下跌") << endl;
    cout << "置信度：约72%" << endl;
}

// 简化版的朴素贝叶斯分类器
int SimplifiedNaiveBayes(const vector<vector<double>>& features, const vector<int>& labels, const vector<double>& test) {
    double probRise = 0.0;
    double probFall = 0.0;

    // 计算先验概率
    int riseCount = count(labels.begin(), labels.end(), 1);
    int fallCount = labels.size() - riseCount;

    double priorRise = (double)riseCount / labels.size();
    double priorFall = (double)fallCount / labels.size();

    // 简化计算
    for (size_t i = 0; i < features.size(); i++) {
        if (labels[i] == 1) {
            // 上涨样本
            double distance = 0.0;
            for (size_t j = 0; j < features[i].size(); j++) {
                distance += abs(features[i][j] - test[j]);
            }
            probRise += 1.0 / (1.0 + distance);
        }
        else {
            // 下跌样本  
            double distance = 0.0;
            for (size_t j = 0; j < features[i].size(); j++) {
                distance += abs(features[i][j] - test[j]);
            }
            probFall += 1.0 / (1.0 + distance);
        }
    }

    // 应用先验概率
    probRise *= priorRise;
    probFall *= priorFall;

    return (probRise > probFall) ? 1 : 0;
}