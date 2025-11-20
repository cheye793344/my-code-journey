// UnionFindAnalysis.cpp
#include "StockSearch.h"
#include "MenuSystem.h"
#include "DataParser.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>
#include <cmath>

using namespace std;

// 并查集相关函数
int CompressionFind(vector<int>& UFSet, int x) {
    if (UFSet[x] < 0) {
        return x;
    }
    else {
        UFSet[x] = CompressionFind(UFSet, UFSet[x]);
        return UFSet[x];
    }
}

void Union_UFSet(vector<int>& UFSet, int Root1, int Root2) {
    Root1 = CompressionFind(UFSet, Root1);
    Root2 = CompressionFind(UFSet, Root2);

    if (Root1 != Root2) {
        UFSet[Root2] += UFSet[Root1];
        UFSet[Root1] = Root2;
    }
}

namespace StockFunctions {
    void unionFindAnalysis() {
        MenuSystem menu;
        system("cls");
        cout << "==========================================" << endl;
        cout << "   基于并查集的股票行业换手率分析" << endl;
        cout << "==========================================" << endl;

        // 读取股票数据
        cout << "正在读取股票数据..." << endl;
        vector<Stock> allStocks = DataParser::loadAllCompleteStocks("data/stocks.txt", "data/detail");

        if (allStocks.empty()) {
            menu.showMessage("错误：无法读取股票数据文件或文件为空！");
            return;
        }

        cout << "数据读取完成！共读取 " << allStocks.size() << " 支股票" << endl;

        // 输入目标行业和目标日期
        string targetIndustry = menu.getInput("请输入目标行业编码: ");
        string targetDate = menu.getInput("请输入目标日期(YYYY-MM-DD): ");

        // 计算总换手率
        double totalChangeRate = 0.0;
        int stockCount = 0;

        for (const auto& stock : allStocks) {
            // 检查行业编码是否匹配
            if (stock.industryCode != targetIndustry) {
                continue;
            }

            // 检查是否有详细信息
            if (stock.details.empty()) {
                continue;
            }

            // 查找指定日期的交易记录
            for (const auto& detail : stock.details) {
                if (detail.date == targetDate) {
                    // 处理换手率字符串
                    string changerateStr = detail.changeRate;
                    double changerate = 0.0;

                    try {
                        // 尝试直接转换
                        changerate = stod(changerateStr);
                    }
                    catch (const std::invalid_argument& e) {
                        // 如果转换失败，提取数字部分
                        string cleanStr;
                        for (char c : changerateStr) {
                            if (isdigit(c) || c == '.' || c == '-') {
                                cleanStr += c;
                            }
                        }
                        if (!cleanStr.empty()) {
                            changerate = stod(cleanStr);
                        }
                    }

                    totalChangeRate += changerate;
                    stockCount++;
                    break;
                }
            }
        }

        // 输出结果
        cout << endl << "分析结果：" << endl;
        cout << "行业编码: " << targetIndustry << " 日期: " << targetDate << endl;
        cout << "------------------------------------------" << endl;

        if (stockCount > 0) {
            double averageChangeRate = totalChangeRate;
            // 四舍五入到两位小数
            averageChangeRate = round(averageChangeRate * 100) / 100.0;
            cout << "总换手率: " << fixed << setprecision(2) << averageChangeRate << endl;
            cout << "涉及股票数量: " << stockCount << " 支" << endl;
        }
        else {
            cout << "未找到匹配的股票数据！" << endl;
        }

        menu.showMessage(""); // 等待按键
    }
}