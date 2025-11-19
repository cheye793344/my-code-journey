#include "MenuSystem.h"
#include "DataParser.h"
#include <iostream>
#include <vector>
#include <algorithm>

namespace StockFunctions {
    void stockUpdate() {
        MenuSystem menu;
        system("cls");
        std::cout << "==========================================" << std::endl;
        std::cout << "         股票基本信息的修改" << std::endl;
        std::cout << "==========================================" << std::endl;

        // 读取股票数据
        std::cout << "正在读取股票数据..." << std::endl;
        std::vector<Stock> stocks = DataParser::loadAllCompleteStocks("data/stocks.txt", "data/detail");

        if (stocks.empty()) {
            menu.showMessage("错误：无法读取股票数据文件或文件为空！");
            return;
        }

        std::cout << "当前共有 " << stocks.size() << " 支股票" << std::endl;

        // 输入要修改的股票简称和新公司名称
        std::string stockName = menu.getInput("请输入要修改的股票简称: ");
        std::string newCompanyName = menu.getInput("请输入修改后的公司全称: ");

        // 查找股票
        auto it = std::find_if(stocks.begin(), stocks.end(),
            [&stockName](const Stock& stock) {
                return stock.stockName == stockName;
            });

        if (it == stocks.end()) {
            menu.showMessage("修改失败：未找到股票简称 '" + stockName + "'");
            return;
        }

        // 保存修改前的信息
        Stock originalStock = *it;

        // 修改公司名称
        std::string oldCompanyName = it->companyName;
        it->companyName = newCompanyName;

        // 写入新文件
        std::cout << "正在更新数据文件..." << std::endl;
        if (DataParser::writeStocksToFile(stocks, "data/new_stocks.txt")) {
            std::cout << "数据已更新到 new_stocks.txt" << std::endl;
        }
        else {
            menu.showMessage("错误：无法写入新数据文件！");
            return;
        }

        // 显示修改后的信息
        std::cout << std::endl;
        std::cout << "成功修改股票信息！" << std::endl;

        std::cout << std::endl;
        std::cout << "=== 修改前信息 ===" << std::endl;
        std::cout << "公司名称: " << oldCompanyName << std::endl;
        std::cout << "详细数据条数: " << originalStock.detailCount << std::endl;

        std::cout << std::endl;
        std::cout << "=== 修改后信息 ===" << std::endl;
        it->displayInfo();

        menu.showMessage(""); // 等待按键
    }
}