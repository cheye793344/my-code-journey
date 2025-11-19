#include "MenuSystem.h"
#include "DataParser.h"
#include <iostream>
#include <vector>
#include <algorithm>

namespace StockFunctions {
    void stockDelete() {
        MenuSystem menu;
        system("cls");
        std::cout << "==========================================" << std::endl;
        std::cout << "         股票基本信息的删除" << std::endl;
        std::cout << "==========================================" << std::endl;

        // 读取股票数据
        std::cout << "正在读取股票数据..." << std::endl;
        std::vector<Stock> stocks = DataParser::loadAllCompleteStocks("data/stocks.txt", "data/detail");

        if (stocks.empty()) {
            menu.showMessage("错误：无法读取股票数据文件或文件为空！");
            return;
        }

        std::cout << "当前共有 " << stocks.size() << " 支股票" << std::endl;

        // 输入要删除的股票简称
        std::string stockName = menu.getInput("请输入要删除的股票简称: ");

        // 查找股票
        auto it = std::find_if(stocks.begin(), stocks.end(),
            [&stockName](const Stock& stock) {
                return stock.stockName == stockName;
            });

        if (it == stocks.end()) {
            menu.showMessage("删除失败：未找到股票简称 '" + stockName + "'");
            return;
        }

        // 保存被删除的股票信息
        Stock deletedStock = *it;

        // 从向量中删除
        stocks.erase(it);

        // 写入新文件
        std::cout << "正在更新数据文件..." << std::endl;
        if (DataParser::writeStocksToFile(stocks, "data/new_stocks.txt")) {
            std::cout << "数据已更新到 new_stocks.txt" << std::endl;
        }
        else {
            menu.showMessage("错误：无法写入新数据文件！");
            return;
        }

        // 显示被删除的股票信息
        std::cout << std::endl;
        std::cout << "成功删除股票！被删除的股票信息如下：" << std::endl;
        deletedStock.displayInfo();

        std::cout << "原股票数量: " << stocks.size() + 1 << std::endl;
        std::cout << "现股票数量: " << stocks.size() << std::endl;

        menu.showMessage(""); // 等待按键
    }
}