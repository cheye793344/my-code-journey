#pragma once
#include <iostream>
#include <string>
#include <vector>
#include<limits>
class MenuSystem {
private:
    std::string currentMenu;

public:
    void showMainMenu() {
        system("cls");
        std::cout << "==========================================" << std::endl;
        std::cout << "       智能股票分析与预测系统" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "1. 股票信息管理与分析" << std::endl;
        std::cout << "2. 股票信息推荐与预测" << std::endl;
        std::cout << "3. 退出系统" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "请选择功能 (1-3): ";
    }

    void showManagementMenu() {
        system("cls");
        std::cout << "==========================================" << std::endl;
        std::cout << "         股票信息管理与分析" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "1. 股票基本信息维护" << std::endl;
        std::cout << "2. 股票基本信息查找" << std::endl;
        std::cout << "3. 股票行情信息统计分析" << std::endl;
        std::cout << "4. 返回主菜单" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "请选择功能 (1-4): ";
    }

    void showMaintenanceMenu() {
        system("cls");
        std::cout << "==========================================" << std::endl;
        std::cout << "         股票基本信息维护" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "1. 股票基本信息的存储" << std::endl;
        std::cout << "2. 股票基本信息的删除" << std::endl;
        std::cout << "3. 股票基本信息的修改" << std::endl;
        std::cout << "4. 返回上一级" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "请选择功能 (1-4): ";
    }

    void showSearchMenu() {
        system("cls");
        std::cout << "==========================================" << std::endl;
        std::cout << "         股票基本信息查找" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "1. 基于折半查找的股票信息查找" << std::endl;
        std::cout << "2. 基于二叉排序树的股票信息查找" << std::endl;
        std::cout << "3. 基于字典树的股票信息查找" << std::endl;
        std::cout << "4. 基于开放地址的股票信息查找" << std::endl;
        std::cout << "5. 基于链地址的股票信息查找" << std::endl;
        std::cout << "6. 返回上一级" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "请选择功能 (1-6): ";
    }

    void showAnalysisMenu() {
        system("cls");
        std::cout << "==========================================" << std::endl;
        std::cout << "       股票行情信息统计分析" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "1. 基于链表的股票涨跌额分析" << std::endl;
        std::cout << "2. 基于并查集的股票行业换手率分析" << std::endl;
        std::cout << "3. 基于堆排序的股票成交量统计" << std::endl;
        std::cout << "4. 基于归并排序的股票成交量统计" << std::endl;
        std::cout << "5. 基于决策树的股票分类统计" << std::endl;
        std::cout << "6. 返回上一级" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "请选择功能 (1-6): ";
    }

    void showRecommendationMenu() {
        system("cls");
        std::cout << "==========================================" << std::endl;
        std::cout << "         股票信息推荐与预测" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "1. 股票推荐" << std::endl;
        std::cout << "2. 股票预测" << std::endl;
        std::cout << "3. 返回主菜单" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "请选择功能 (1-3): ";
    }

    void showKGMenu() {
        system("cls");
        std::cout << "==========================================" << std::endl;
        std::cout << "             股票推荐" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "1. 基于规则的股票信息实体识别" << std::endl;
        std::cout << "2. 基于规则的股票信息关系抽取" << std::endl;
        std::cout << "3. 基于邻接表的股票知识图谱构建" << std::endl;
        std::cout << "4. 基于知识图谱的股票推荐" << std::endl;
        std::cout << "5. 返回上一级" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "请选择功能 (1-5): ";
    }

    void showPredictionMenu() {
        system("cls");
        std::cout << "==========================================" << std::endl;
        std::cout << "             股票预测" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "1. 基于皮尔逊相关系数的股票指标重要性分析" << std::endl;
        std::cout << "2. 基于朴素贝叶斯分类器的股票涨跌预测" << std::endl;
        std::cout << "3. 基于K近邻算法的股票涨跌预测" << std::endl;
        std::cout << "4. 返回上一级" << std::endl;
        std::cout << "==========================================" << std::endl;
        std::cout << "请选择功能 (1-4): ";
    }

    void showMessage(const std::string& message) {
        std::cout << std::endl << message << std::endl;
        std::cout << "按任意键继续...";
        std::cin.get();
        std::cin.get();
    }

    std::string getInput(const std::string& prompt) {
    std::string input;
    std::cout << prompt;
    
    // 关键1：清空 cin 缓冲区中残留的换行符（避免跳过输入）
    std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
    
    // 关键2：用 getline 读取整行（包括空格），直到按下回车
    std::getline(std::cin, input);
    
    return input;
}

    int getIntInput(const std::string& prompt) {
        int input;
        std::cout << prompt;
        std::cin >> input;
        return input;
    }

    double getDoubleInput(const std::string& prompt) {
        double input;
        std::cout << prompt;
        std::cin >> input;
        return input;
    }
};