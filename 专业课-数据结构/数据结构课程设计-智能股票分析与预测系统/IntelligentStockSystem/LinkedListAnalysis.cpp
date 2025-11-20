// LinkedListAnalysis.cpp
#include "StockSearch.h"
#include "MenuSystem.h"
#include "DataParser.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// 复用第9关的核心数据结构
struct StockNode {
    string stockcode;
    string indusname;
    string induscode;
    string date;
    double risefallamount;
    StockNode* next;

    StockNode() : risefallamount(0), next(nullptr) {}
};

namespace StockFunctions {
    void linkedListAnalysis() {
        MenuSystem menu;
        system("cls");
        cout << "==========================================" << endl;
        cout << "   基于链表的股票涨跌额分析" << endl;
        cout << "==========================================" << endl;

        // 读取股票数据
        cout << "正在读取股票数据..." << endl;
        vector<Stock> allStocks = DataParser::loadAllCompleteStocks("data/stocks.txt", "data/detail");

        if (allStocks.empty()) {
            menu.showMessage("错误：无法读取股票数据文件或文件为空！");
            return;
        }

        cout << "数据读取完成！共读取 " << allStocks.size() << " 支股票" << endl;

        // 输入行业编码和目标日期
        string induscode = menu.getInput("请输入行业编码: ");
        string targetdate = menu.getInput("请输入目标日期(YYYY-MM-DD): ");

        // 构建链表
        StockNode* negativeHead = nullptr;
        StockNode* negativeTail = nullptr;
        StockNode* nonNegativeHead = nullptr;
        StockNode* nonNegativeTail = nullptr;

        // 遍历所有股票
        for (const auto& stock : allStocks) {
            // 检查行业编码是否匹配
            if (stock.industryCode != induscode) {
                continue;
            }

            // 检查是否有详细信息
            if (stock.details.empty()) {
                continue;
            }

            // 查找指定日期的交易记录
            for (const auto& detail : stock.details) {
                if (detail.date == targetdate) {
                    // 创建新节点
                    StockNode* newNode = new StockNode();
                    newNode->stockcode = stock.stockCode;
                    newNode->indusname = stock.stockName;
                    newNode->induscode = stock.industryCode;
                    newNode->date = detail.date;
                    newNode->risefallamount = detail.riseFallAmount;
                    newNode->next = nullptr;

                    // 根据涨跌额分组
                    if (detail.riseFallAmount < 0) {
                        // 负值组
                        if (negativeHead == nullptr) {
                            negativeHead = newNode;
                            negativeTail = newNode;
                        }
                        else {
                            negativeTail->next = newNode;
                            negativeTail = newNode;
                        }
                    }
                    else {
                        // 非负值组
                        if (nonNegativeHead == nullptr) {
                            nonNegativeHead = newNode;
                            nonNegativeTail = newNode;
                        }
                        else {
                            nonNegativeTail->next = newNode;
                            nonNegativeTail = newNode;
                        }
                    }
                    break; // 找到对应日期后跳出内层循环
                }
            }
        }

        // 连接两个分组：负值组在前，非负值组在后
        StockNode* head = negativeHead;
        if (negativeTail != nullptr) {
            negativeTail->next = nonNegativeHead;
        }
        else {
            head = nonNegativeHead;
        }

        // 输出结果
        cout << endl << "分析结果：" << endl;
        cout << "行业编码: " << induscode << " 日期: " << targetdate << endl;
        cout << "------------------------------------------" << endl;

        StockNode* p = head;
        int count = 0;
        while (p != nullptr) {
            cout << "股票代码: " << p->stockcode << " ";
            cout << "股票简称: " << p->indusname << " ";
            cout << "行业编码: " << p->induscode << " ";
            cout << "日期: " << p->date << " ";
            cout << "涨跌额: " << p->risefallamount << endl;
            p = p->next;
            count++;
        }

        if (count == 0) {
            cout << "未找到匹配的股票数据！" << endl;
        }
        else {
            cout << "共找到 " << count << " 支股票" << endl;
        }

        // 释放链表内存
        while (head != nullptr) {
            StockNode* tmp = head;
            head = head->next;
            delete tmp;
        }

        menu.showMessage(""); // 等待按键
    }
}