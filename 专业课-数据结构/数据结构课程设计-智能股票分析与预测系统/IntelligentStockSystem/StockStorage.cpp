#include "MenuSystem.h"
#include "DataParser.h"
#include <iostream>
#include <vector>

namespace StockFunctions {
    void stockStorage() {
        MenuSystem menu;
        system("cls");
        std::cout << "==========================================" << std::endl;
        std::cout << "         股票基本信息的存储" << std::endl;
        std::cout << "==========================================" << std::endl;

        // 读取股票数据
        std::cout << "正在读取股票数据..." << std::endl;
        std::vector<Stock> stocks = DataParser::loadAllCompleteStocks("data/stocks.txt", "data/detail");

        if (stocks.empty()) {
            menu.showMessage("错误：无法读取股票数据文件或文件为空！");
            return;
        }

        std::cout << "数据读取完成！共读取 " << stocks.size() << " 支股票" << std::endl;
        std::cout << "每支股票包含 " << (stocks.empty() ? 0 : stocks[0].detailCount) << " 条交易记录" << std::endl;

        // 输入位置查询股票信息
        std::cout << std::endl;
        int pos = menu.getIntInput("请输入要查询的股票在顺序表中的位置 (0-" + std::to_string(stocks.size() - 1) + "): ");

        if (pos >= 0 && pos < static_cast<int>(stocks.size())) {
            Stock stock = stocks[pos];
            std::cout << std::endl;
            stock.displayInfo();

            // 显示部分详细交易数据
            if (!stock.details.empty()) {
                std::cout << "最近5条交易记录:" << std::endl;
                std::cout << "日期\t\t开盘价\t收盘价\t最高价\t最低价\t涨跌幅" << std::endl;
                int count = min(5, static_cast<int>(stock.details.size()));
                for (int i = 0; i < count; ++i) {
                    const auto& detail = stock.details[i];
                    std::cout << detail.date << "\t"
                        << detail.openPrice << "\t"
                        << detail.closePrice << "\t"
                        << detail.highest << "\t"
                        << detail.lowest << "\t"
                        << detail.riseFallRate << std::endl;
                }
            }
        }
        else {
            menu.showMessage("位置无效！请输入 0 到 " + std::to_string(stocks.size() - 1) + " 之间的数字");
            return;
        }

        menu.showMessage(""); // 等待按键
    }
}