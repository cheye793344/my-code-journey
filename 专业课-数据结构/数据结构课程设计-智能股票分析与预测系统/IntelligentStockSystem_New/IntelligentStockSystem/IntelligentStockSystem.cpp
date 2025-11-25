#include <iostream>
#include <string>
#include <cstdlib>
#include "EncodingUtils.h"
#include "Module_Maintenance.h"
#include "Module_Search.h"
#include "Module_Stats.h"
#include "Module_Recommendation.h"
#include "Module_Prediction.h"

using namespace std;

void ClearScreen() {
    system("cls");
}

void Pause() {
    cout << "\n按任意键继续...";
    cin.ignore();
    cin.get();
}

// 股票基本信息管理与分析菜单
void Menu_InfoManagement() {
    while (true) {
        ClearScreen();
        cout << "================ 股票信息管理与分析 ================" << endl;
        cout << "1. 股票基本信息维护 (存储/删除/修改)" << endl;
        cout << "2. 股票基本信息查找 (多种算法)" << endl;
        cout << "3. 股票行情信息统计分析 (涨跌/换手率/成交量)" << endl;
        cout << "0. 返回上一级" << endl;
        cout << "===================================================" << endl;
        cout << "请选择: ";
        int choice;
        cin >> choice;
        // 清除输入缓冲区的换行符，防止影响后续getline
        string dummy; getline(cin, dummy);

        if (choice == 0) break;

        switch (choice) {
        case 1: // 维护
            while (true) {
                ClearScreen();
                cout << "--- 股票基本信息维护 ---" << endl;
                cout << "1. 信息存储 (Level 1)" << endl;
                cout << "2. 信息删除 (Level 2)" << endl;
                cout << "3. 信息修改 (Level 3)" << endl;
                cout << "0. 返回" << endl;
                cout << "请选择: ";
                int subC; cin >> subC; getline(cin, dummy);
                if (subC == 0) break;
                if (subC == 1) { Level_1::run(); Pause(); }
                else if (subC == 2) { Level_2::run(); Pause(); }
                else if (subC == 3) { Level_3::run(); Pause(); }
            }
            break;
        case 2: // 查找
            while (true) {
                ClearScreen();
                cout << "--- 股票基本信息查找 ---" << endl;
                cout << "1. 折半查找 (Level 4)" << endl;
                cout << "2. 二叉排序树查找 (Level 5)" << endl;
                cout << "3. 字典树查找 (Level 6)" << endl;
                cout << "4. 开放地址法散列 (Level 7)" << endl;
                cout << "5. 链地址法散列 (Level 8)" << endl;
                cout << "0. 返回" << endl;
                cout << "请选择: ";
                int subC; cin >> subC; getline(cin, dummy);
                if (subC == 0) break;
                if (subC == 1) { Level_4::run(); Pause(); }
                else if (subC == 2) { Level_5::run(); Pause(); }
                else if (subC == 3) { Level_6::run(); Pause(); }
                else if (subC == 4) { Level_7::run(); Pause(); }
                else if (subC == 5) { Level_8::run(); Pause(); }
            }
            break;
        case 3: // 统计
            while (true) {
                ClearScreen();
                cout << "--- 股票行情信息统计分析 ---" << endl;
                cout << "1. 链表涨跌额分析 (Level 9)" << endl;
                cout << "2. 并查集行业换手率 (Level 10)" << endl;
                cout << "3. 堆排序成交量 (Level 11)" << endl;
                cout << "4. 归并排序成交量 (Level 12)" << endl;
                cout << "0. 返回" << endl;
                cout << "请选择: ";
                int subC; cin >> subC; getline(cin, dummy);
                if (subC == 0) break;
                if (subC == 1) { Level_9::run(); Pause(); }
                else if (subC == 2) { Level_10::run(); Pause(); }
                else if (subC == 3) { Level_11::run(); Pause(); }
                else if (subC == 4) { Level_12::run(); Pause(); }
            }
            break;
        }
    }
}

// 股票信息推荐与预测菜单
void Menu_RecAndPred() {
    while (true) {
        ClearScreen();
        cout << "================ 股票信息推荐与预测 ================" << endl;
        cout << "1. 股票推荐 (知识图谱/规则/决策树)" << endl;
        cout << "2. 股票预测 (贝叶斯/KNN/相关性)" << endl;
        cout << "0. 返回上一级" << endl;
        cout << "===================================================" << endl;
        cout << "请选择: ";
        int choice;
        cin >> choice;
        string dummy; getline(cin, dummy);

        if (choice == 0) break;

        switch (choice) {
        case 1: // 推荐
            while (true) {
                ClearScreen();
                cout << "--- 股票推荐 ---" << endl;
                cout << "1. 决策树分类 (Level 13)" << endl;
                cout << "2. 规则实体识别 (Level 14)" << endl;
                cout << "3. 规则关系挖掘 (Level 15)" << endl;
                cout << "4. 知识图谱构建 (Level 16)" << endl;
                cout << "5. 知识图谱推荐 (Level 17)" << endl;
                cout << "0. 返回" << endl;
                cout << "请选择: ";
                int subC; cin >> subC; getline(cin, dummy);
                if (subC == 0) break;
                if (subC == 1) { Level_13::run(); Pause(); }
                else if (subC == 2) { Level_14::run(); Pause(); }
                else if (subC == 3) { Level_15::run(); Pause(); }
                else if (subC == 4) { Level_16::run(); Pause(); }
                else if (subC == 5) { Level_17::run(); Pause(); }
            }
            break;
        case 2: // 预测
            while (true) {
                ClearScreen();
                cout << "--- 股票预测 ---" << endl;
                cout << "1. 皮尔逊指标分析 (Level 18)" << endl;
                cout << "2. 朴素贝叶斯预测 (Level 19)" << endl;
                cout << "3. K近邻预测 (Level 20)" << endl;
                cout << "0. 返回" << endl;
                cout << "请选择: ";
                int subC; cin >> subC; getline(cin, dummy);
                if (subC == 0) break;
                if (subC == 1) { Level_18::run(); Pause(); }
                else if (subC == 2) { Level_19::run(); Pause(); }
                else if (subC == 3) { Level_20::run(); Pause(); }
            }
            break;
        }
    }
}

int main() {
    // 设置编码，防止乱码
    // 如果你的源文件是UTF-8，且VS按GBK编译，这里设置65001；
    // 如果VS正确识别了UTF-8 BOM，则不需要，但为了保险起见，建议系统默认。
    // 使用我们提供的工具类来尝试适配
    // system("chcp 65001"); // 视具体情况启用，如果输出乱码请取消注释

    while (true) {
        ClearScreen();
        cout << "================ 智能股票分析与预测系统 ================" << endl;
        cout << "1. 股票信息管理与分析" << endl;
        cout << "2. 股票信息推荐与预测" << endl;
        cout << "0. 退出系统" << endl;
        cout << "=======================================================" << endl;
        cout << "请输入选项: ";

        int choice;
        if (!(cin >> choice)) {
            cin.clear(); cin.ignore(1000, '\n'); continue;
        }
        string dummy; getline(cin, dummy); // 吃掉回车

        if (choice == 0) break;
        if (choice == 1) Menu_InfoManagement();
        else if (choice == 2) Menu_RecAndPred();
    }
    return 0;
}