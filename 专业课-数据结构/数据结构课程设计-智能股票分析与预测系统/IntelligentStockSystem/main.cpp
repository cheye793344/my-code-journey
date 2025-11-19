#include <iostream>
#include <string>
#include "MenuSystem.h"
#include "StockManagement.h"
// 函数声明 - 这些将对应你20关的功能
namespace StockFunctions {
    // 股票管理功能 (1-3关)
    void stockStorage();
    void stockDelete();
    void stockUpdate();

    // 股票查找功能 (4-8关)
    void binarySearchStock(){}
    void BSTSearchStock(){}
    void trieSearchStock(){}
    void openHashSearchStock(){}
    void chainHashSearchStock(){}

    // 统计分析功能 (9-13关)
    void linkedListAnalysis(){}
    void unionFindAnalysis(){}
    void heapSortAnalysis(){}
    void mergeSortAnalysis(){}
    void decisionTreeAnalysis(){}

    // 知识图谱功能 (14-17关)
    void entityRecognition(){}
    void relationExtraction(){}
    void buildKnowledgeGraph(){}
    void knowledgeGraphRecommendation(){}

    // 预测功能 (18-20关)
    void pearsonCorrelationAnalysis(){}
    void naiveBayesPrediction(){}
    void knnPrediction(){}
}

int main() {
    MenuSystem menu;
    int choice;

    do {
        menu.showMainMenu();
        choice = menu.getIntInput("");

        switch (choice) {
        case 1: {
            // 股票信息管理与分析
            int managementChoice;
            do {
                menu.showManagementMenu();
                managementChoice = menu.getIntInput("");

                switch (managementChoice) {
                case 1: {
                    // 股票基本信息维护
                    int maintenanceChoice;
                    do {
                        menu.showMaintenanceMenu();
                        maintenanceChoice = menu.getIntInput("");

                        switch (maintenanceChoice) {
                        case 1: StockFunctions::stockStorage(); break;
                        case 2: StockFunctions::stockDelete(); break;
                        case 3: StockFunctions::stockUpdate(); break;
                        case 4: break;
                        default: menu.showMessage("无效选择！"); break;
                        }
                    } while (maintenanceChoice != 4);
                    break;
                }
                case 2: {
                    // 股票基本信息查找
                    int searchChoice;
                    do {
                        menu.showSearchMenu();
                        searchChoice = menu.getIntInput("");

                        switch (searchChoice) {
                        case 1: StockFunctions::binarySearchStock(); break;
                        case 2: StockFunctions::BSTSearchStock(); break;
                        case 3: StockFunctions::trieSearchStock(); break;
                        case 4: StockFunctions::openHashSearchStock(); break;
                        case 5: StockFunctions::chainHashSearchStock(); break;
                        case 6: break;
                        default: menu.showMessage("无效选择！"); break;
                        }
                    } while (searchChoice != 6);
                    break;
                }
                case 3: {
                    // 股票行情信息统计分析
                    int analysisChoice;
                    do {
                        menu.showAnalysisMenu();
                        analysisChoice = menu.getIntInput("");

                        switch (analysisChoice) {
                        case 1: StockFunctions::linkedListAnalysis(); break;
                        case 2: StockFunctions::unionFindAnalysis(); break;
                        case 3: StockFunctions::heapSortAnalysis(); break;
                        case 4: StockFunctions::mergeSortAnalysis(); break;
                        case 5: StockFunctions::decisionTreeAnalysis(); break;
                        case 6: break;
                        default: menu.showMessage("无效选择！"); break;
                        }
                    } while (analysisChoice != 6);
                    break;
                }
                case 4: break;
                default: menu.showMessage("无效选择！"); break;
                }
            } while (managementChoice != 4);
            break;
        }
        case 2: {
            // 股票信息推荐与预测
            int recommendationChoice;
            do {
                menu.showRecommendationMenu();
                recommendationChoice = menu.getIntInput("");

                switch (recommendationChoice) {
                case 1: {
                    // 股票推荐
                    int kgChoice;
                    do {
                        menu.showKGMenu();
                        kgChoice = menu.getIntInput("");

                        switch (kgChoice) {
                        case 1: StockFunctions::entityRecognition(); break;
                        case 2: StockFunctions::relationExtraction(); break;
                        case 3: StockFunctions::buildKnowledgeGraph(); break;
                        case 4: StockFunctions::knowledgeGraphRecommendation(); break;
                        case 5: break;
                        default: menu.showMessage("无效选择！"); break;
                        }
                    } while (kgChoice != 5);
                    break;
                }
                case 2: {
                    // 股票预测
                    int predictionChoice;
                    do {
                        menu.showPredictionMenu();
                        predictionChoice = menu.getIntInput("");

                        switch (predictionChoice) {
                        case 1: StockFunctions::pearsonCorrelationAnalysis(); break;
                        case 2: StockFunctions::naiveBayesPrediction(); break;
                        case 3: StockFunctions::knnPrediction(); break;
                        case 4: break;
                        default: menu.showMessage("无效选择！"); break;
                        }
                    } while (predictionChoice != 4);
                    break;
                }
                case 3: break;
                default: menu.showMessage("无效选择！"); break;
                }
            } while (recommendationChoice != 3);
            break;
        }
        case 3:
            menu.showMessage("感谢使用智能股票分析与预测系统！");
            break;
        default:
            menu.showMessage("无效选择，请重新输入！");
            break;
        }
    } while (choice != 3);

    return 0;
}