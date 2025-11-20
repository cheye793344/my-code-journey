// MergeSortAnalysis.cpp
#include "StockSearch.h"
#include "MenuSystem.h"
#include "DataParser.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>
#include <map>

using namespace std;

// 日期-成交量结构体
struct DailyVolume {
    string date;
    double volume;

    DailyVolume() : volume(0) {}
    DailyVolume(string d, double v) : date(d), volume(v) {}
};

// 归并排序相关函数
// Merge 函数保持不变
void Merge(vector<DailyVolume>& R, vector<DailyVolume>& T, int low, int mid, int high, int& kcn, int& rmn) {
    int i = low, j = mid + 1, k = low;

    while (i <= mid && j <= high) {
        kcn++;
        if (R[i].volume <= R[j].volume) {
            rmn++;
            T[k++] = R[i++];
        }
        else {
            rmn++;
            T[k++] = R[j++];
        }
    }

    while (i <= mid) {
        rmn++;
        T[k++] = R[i++];
    }

    while (j <= high) {
        rmn++;
        T[k++] = R[j++];
    }
}

// 修正后的 MSort 函数
// R: 源数组
// T: 临时数组，用于存放合并结果
// low, high: 当前排序区间
void MSort(vector<DailyVolume>& R, vector<DailyVolume>& T, int low, int high, int& kcn, int& rmn) {
    if (low == high) {
        // 单个元素，直接复制到 T 中对应位置（在这个场景下可以省略，因为 Merge 会处理）
        T[low] = R[low];
    }
    else {
        int mid = (low + high) / 2;

        // 递归地对左右两半进行排序
        // 注意：这里将 R 和 T 的角色互换，确保合并时源数据是正确的
        MSort(R, T, low, mid, kcn, rmn);
        MSort(R, T, mid + 1, high, kcn, rmn);

        // 将排好序的左右两半从 R 合并到 T
        Merge(R, T, low, mid, high, kcn, rmn);

        // 将合并好的结果从 T 复制回 R，以便上一层递归使用
        for (int i = low; i <= high; i++) {
            R[i] = T[i];
        }
    }
}

// 修正后的 MergeSort 函数
void MergeSort(vector<DailyVolume>& data, int& kcn, int& rmn) {
    if (data.empty()) return;
    // 创建一个与原数组大小相同的临时数组
    vector<DailyVolume> T(data.size());
    // 调用修正后的 MSort 函数
    MSort(data, T, 0, data.size() - 1, kcn, rmn);
}

namespace StockFunctions {
    void mergeSortAnalysis() {
        MenuSystem menu;
        system("cls");
        cout << "==========================================" << endl;
        cout << "   基于归并排序的股票成交量统计" << endl;
        cout << "==========================================" << endl;

        // 读取股票数据
        cout << "正在读取股票数据..." << endl;
        vector<Stock> allStocks = DataParser::loadAllCompleteStocks("data/stocks.txt", "data/detail");

        if (allStocks.empty()) {
            menu.showMessage("错误：无法读取股票数据文件或文件为空！");
            return;
        }

        cout << "数据读取完成！共读取 " << allStocks.size() << " 支股票" << endl;

        // 输入目标行业
        string targetIndustry = menu.getInput("请输入目标行业编码: ");

        // 按日期累加成交量
        vector<DailyVolume> dailyVolumes;
        map<string, double> volumeMap;

        for (const auto& stock : allStocks) {
            if (stock.industryCode != targetIndustry) continue;

            for (const auto& detail : stock.details) {
                volumeMap[detail.date] += detail.volume;
            }
        }

        // 转换为向量
        for (const auto& pair : volumeMap) {
            dailyVolumes.push_back(DailyVolume(pair.first, pair.second));
        }

        if (dailyVolumes.empty()) {
            menu.showMessage("未找到匹配的股票数据！");
            return;
        }

        cout << "找到 " << dailyVolumes.size() << " 天的交易数据" << endl;

        // 归并排序
        int kcn = 0, rmn = 0;
        MergeSort(dailyVolumes, kcn, rmn);

        // 输出结果
        cout << endl << "按成交量排序的结果：" << endl;
        cout << "------------------------------------------" << endl;

        for (const auto& dv : dailyVolumes) {
            cout << dv.date << " " << fixed << setprecision(3) << dv.volume << endl;
        }
        
        cout << "总的关键字比较次数KCN为: " << kcn << endl;
        cout << "总的记录移动次数RMN为: " << rmn << endl;

        menu.showMessage(""); // 等待按键
    }
}