// HeapSortAnalysis.cpp
#include "StockSearch.h"
#include "MenuSystem.h"
#include "DataParser.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// 堆排序相关函数
void HeapAdjust(vector<Stock>& stocks, int s, int m, int& kcn, int& rmn) {
    Stock rc = stocks[s];
    rmn++;

    int j;
    for (j = 2 * s; j <= m; j *= 2) {
        if (j < m) {
            kcn++;
            if (stocks[j].details[0].volume < stocks[j + 1].details[0].volume) {
                j++;
            }
        }

        kcn++;
        if (rc.details[0].volume >= stocks[j].details[0].volume) {
            break;
        }

        stocks[s] = stocks[j];
        rmn++;
        s = j;
    }

    stocks[s] = rc;
    rmn++;
}

void CreatHeap(vector<Stock>& stocks, int& kcn, int& rmn) {
    int n = stocks.size() - 1;
    for (int i = n / 2; i > 0; i--) {
        HeapAdjust(stocks, i, n, kcn, rmn);
    }
}

namespace StockFunctions {
    void heapSortAnalysis() {
        MenuSystem menu;
        system("cls");
        cout << "==========================================" << endl;
        cout << "   基于堆排序的股票成交量统计" << endl;
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

        // 筛选符合条件的股票
        vector<Stock> filteredStocks;
        filteredStocks.push_back(Stock()); // 下标从1开始，第0个位置空出来

        for (auto& stock : allStocks) {
            if (stock.industryCode != targetIndustry) continue;

            bool found = false;
            for (int j = 0; j < stock.detailCount; j++) {
                if (stock.details[j].date == targetDate) {
                    // 将目标日期记录交换到首位
                    if (j != 0) {
                        swap(stock.details[0], stock.details[j]);
                    }
                    found = true;
                    break;
                }
            }

            if (found) {
                filteredStocks.push_back(stock);
            }
        }

        if (filteredStocks.size() <= 1) {
            menu.showMessage("未找到匹配的股票数据！");
            return;
        }

        cout << "找到 " << filteredStocks.size() - 1 << " 支符合条件的股票" << endl;

        // 构建堆
        int kcn = 0, rmn = 0;
        CreatHeap(filteredStocks, kcn, rmn);

        // 输出前3名
        cout << endl << "成交量排名前3的股票：" << endl;
        cout << "------------------------------------------" << endl;

        int num = 0;
        int currentLength = filteredStocks.size() - 1;

        while (currentLength > 0 && num < 3) {
            Stock s = filteredStocks[1];
            cout << "股票代码: " << s.stockCode << endl;
            cout << "股票简称: " << s.stockName << endl;
            cout << "行业编码: " << s.industryCode << endl;
            cout << "一级门类: " << s.primaryCategory << endl;
            cout << "二级门类: " << s.secondaryCategory << endl;
            cout << "公司全称: " << s.companyName << endl;
            cout << "日期: " << s.details[0].date;
            cout << " 成交量: " << (long long)s.details[0].volume << endl;
            cout << "----------------------------" << endl;

            // 堆顶与末尾元素交换
            filteredStocks[1] = filteredStocks[currentLength--];
            // 调整新堆顶
            HeapAdjust(filteredStocks, 1, currentLength, kcn, rmn);
            num++;
        }

        cout << "总的关键字比较次数KCN为: " << kcn << endl;
        cout << "总的记录移动次数RMN为: " << rmn << endl;

        menu.showMessage(""); // 等待按键
    }
}