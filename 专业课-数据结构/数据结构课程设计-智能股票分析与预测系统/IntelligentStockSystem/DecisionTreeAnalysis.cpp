// DecisionTreeAnalysis.cpp
#include "StockSearch.h"
#include "MenuSystem.h"
#include "DataParser.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// 决策树节点
struct BiTNode {
    Stock data;
    BiTNode* lchild;
    BiTNode* rchild;
    string decision;

    BiTNode() : lchild(nullptr), rchild(nullptr) {}
};

namespace StockFunctions {
    void decisionTreeAnalysis() {
        MenuSystem menu;
        system("cls");
        cout << "==========================================" << endl;
        cout << "   基于决策树的股票分类统计" << endl;
        cout << "==========================================" << endl;

        // 读取股票数据
        cout << "正在读取股票数据..." << endl;
        vector<Stock> allStocks = DataParser::loadAllCompleteStocks("data/stocks.txt", "data/detail");

        if (allStocks.empty()) {
            menu.showMessage("错误：无法读取股票数据文件或文件为空！");
            return;
        }

        cout << "数据读取完成！共读取 " << allStocks.size() << " 支股票" << endl;

        // 输入股票简称
        string stockName = menu.getInput("请输入要查询的股票简称: ");

        // 查找目标股票
        Stock* targetStock = nullptr;
        for (auto& stock : allStocks) {
            if (stock.stockName == stockName) {
                targetStock = &stock;
                break;
            }
        }

        if (targetStock == nullptr) {
            menu.showMessage("未找到股票简称 '" + stockName + "'");
            return;
        }

        // 决策树分类
        vector<string> decisions;

        cout << endl << "股票分类决策路径：" << endl;
        cout << "------------------------------------------" << endl;

        // 决策1: 二级门类是否为计算机、通信和其他电子设备制造业
        if (targetStock->secondaryCategory.find("计算机") != string::npos ||
            targetStock->secondaryCategory.find("通信") != string::npos ||
            targetStock->secondaryCategory.find("电子设备") != string::npos) {
            decisions.push_back("二级门类为计算机、通信和其他电子设备制造业");
            cout << "二级门类为计算机、通信和其他电子设备制造业" << endl;
        }
        else {
            decisions.push_back("二级门类不为计算机、通信和其他电子设备制造业");
            cout << "二级门类不为计算机、通信和其他电子设备制造业" << endl;
            menu.showMessage(""); // 等待按键
            return;
        }

        // 决策2: 最近一天跌涨幅>0
        if (!targetStock->details.empty()) {
            string rateStr = targetStock->details[0].riseFallRate;
            if (!rateStr.empty()) {
                // 去除百分号
                if (rateStr.back() == '%') {
                    rateStr.pop_back();
                }
                try {
                    double rate = stod(rateStr);
                    if (rate > 0) {
                        decisions.push_back("最近一天跌涨幅>0");
                        cout << "最近一天跌涨幅>0" << endl;
                    }
                    else {
                        decisions.push_back("最近一天跌涨幅<=0");
                        cout << "最近一天跌涨幅<=0" << endl;
                        menu.showMessage(""); // 等待按键
                        return;
                    }
                }
                catch (...) {
                    decisions.push_back("最近一天跌涨幅数据异常");
                    cout << "最近一天跌涨幅数据异常" << endl;
                    menu.showMessage(""); // 等待按键
                    return;
                }
            }
        }

        // 决策3: 最近一天成交量>1000万股
        if (!targetStock->details.empty()) {
            if (targetStock->details[0].volume > 10000000) {
                decisions.push_back("最近一天成交量>1000万股");
                cout << "最近一天成交量>1000万股" << endl;
            }
            else {
                decisions.push_back("最近一天成交量<=1000万股");
                cout << "最近一天成交量<=1000万股" << endl;
            }
        }

        cout << endl << "股票完整信息：" << endl;
        cout << "------------------------------------------" << endl;
        targetStock->displayInfo();

        menu.showMessage(""); // 等待按键
    }
}