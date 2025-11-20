#include <iostream>
#include <cmath>
#include <iomanip>
#include <fstream>
#include <string>
#include <sstream>
#include <stdexcept>
#include<vector>

using namespace std;

// 定义最大数组大小
const double M_PI = 3.14159265358979323846;
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

//#include "19-基于朴素贝叶斯分类器的股票涨跌预测.h"

int main() {
    string inputFile;
    getline(cin, inputFile);
    Sample allSamples[MAX_SAMPLES];
    int sampleCount = LoadTrainData(inputFile, allSamples);
    if (sampleCount < 2) {
        cerr << "数据量不足，至少需要2条数据！" << endl;
        return 1;
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

    return 0;
}