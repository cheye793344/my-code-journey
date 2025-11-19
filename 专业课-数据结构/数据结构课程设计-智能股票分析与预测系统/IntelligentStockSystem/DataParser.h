#pragma once
#include <string>
#include <vector>
#include <sstream>
#include <algorithm>
#include "FileReader.h"
#include "Stock.h"

class DataParser {
public:
    // 解析股票基本信息
    static std::vector<Stock> parseStocks(const std::string& filename) {
        std::vector<Stock> stocks;
        std::vector<std::string> lines = FileReader::readFile(filename);

        Stock currentStock;
        bool readingStock = false;

        for (const auto& line : lines) {
            if (line.empty()) continue;

            if (line.find("CODE:") != std::string::npos) {
                if (readingStock) {
                    stocks.push_back(currentStock);
                }
                readingStock = true;
                currentStock = Stock();
                currentStock.stockCode = trim(line.substr(5)); // 去掉"CODE:"
            }
            else if (line == "#") {
                // 分隔符，继续读取下一支股票
                if (readingStock) {
                    stocks.push_back(currentStock);
                    readingStock = false;
                    currentStock = Stock();
                }
            }
            else if (line.find(":") != std::string::npos) {
                parseStockField(line, currentStock);
            }
        }

        // 添加最后一支股票
        if (readingStock) {
            stocks.push_back(currentStock);
        }

        return stocks;
    }

    // 解析股票详细数据
    static void parseStockDetails(Stock& stock, const std::string& detailPath) {
        std::string filename = detailPath + "/" + stock.stockCode + ".txt";
        std::vector<std::string> lines = FileReader::readFile(filename);

        for (const auto& line : lines) {
            if (line.empty()) continue;

            StockDetail detail;
            std::vector<std::string> fields = split(line, ';');

            if (fields.size() >= 10) {
                detail.date = trim(fields[0]);
                detail.openPrice = safeStod(fields[1]);
                detail.closePrice = safeStod(fields[2]);
                detail.highest = safeStod(fields[3]);
                detail.lowest = safeStod(fields[4]);
                detail.volume = safeStod(fields[5]);
                detail.turnover = safeStod(fields[6]);
                detail.changeRate = trim(fields[7]);
                detail.riseFallRate = trim(fields[8]);
                detail.riseFallAmount = safeStod(fields[9]);

                stock.details.push_back(detail);
            }
        }

        stock.detailCount = stock.details.size();
    }

    // 将股票数据写回文件
    static bool writeStocksToFile(const std::vector<Stock>& stocks, const std::string& filename) {
        std::ofstream file(filename);
        if (!file.is_open()) return false;

        for (size_t i = 0; i < stocks.size(); ++i) {
            const Stock& stock = stocks[i];

            file << "CODE: " << stock.stockCode << std::endl;
            file << "股票简称: " << stock.stockName << std::endl;
            file << "英文名: " << stock.englishName << std::endl;
            file << "机构名称: " << stock.companyName << std::endl;
            file << "上市交易所: " << stock.listExchange << std::endl;
            file << "行业编码: " << stock.industryCode << std::endl;
            file << "行业大类: " << stock.primaryCategory << std::endl;
            file << "行业二级类: " << stock.secondaryCategory << std::endl;
            file << "上市日期: " << stock.launchDate << std::endl;
            file << "省份: " << stock.province << std::endl;
            file << "城市: " << stock.city << std::endl;
            file << "法人: " << stock.legalPerson << std::endl;
            file << "地址: " << stock.address << std::endl;
            file << "网址: " << stock.website << std::endl;
            file << "邮箱: " << stock.email << std::endl;
            file << "电话: " << stock.phone << std::endl;
            file << "主营业务: " << stock.mainBusiness << std::endl;
            file << "经营范围: " << stock.businessScope << std::endl;

            if (i < stocks.size() - 1) {
                file << "#" << std::endl;
            }
        }

        file.close();
        return true;
    }

    // 加载单个股票的完整数据（包括详细信息）
    static Stock loadCompleteStock(const Stock& basicStock, const std::string& detailPath) {
        Stock completeStock = basicStock;  // 这会调用拷贝构造函数
        parseStockDetails(completeStock, detailPath);
        return completeStock;
    }

    // 加载所有股票的完整数据
    static std::vector<Stock> loadAllCompleteStocks(const std::string& stocksFile, const std::string& detailPath) {
        std::vector<Stock> stocks = parseStocks(stocksFile);
        for (auto& stock : stocks) {
            parseStockDetails(stock, detailPath);
        }
        return stocks;
    }

private:
    static void parseStockField(const std::string& line, Stock& stock) {
        size_t colonPos = line.find(":");
        if (colonPos == std::string::npos) return;

        std::string key = trim(line.substr(0, colonPos));
        std::string value = trim(line.substr(colonPos + 1));

        if (key == "股票简称") stock.stockName = value;
        else if (key == "英文名") stock.englishName = value;
        else if (key == "机构名称") stock.companyName = value;
        else if (key == "上市交易所") stock.listExchange = value;
        else if (key == "行业编码") stock.industryCode = value;
        else if (key == "行业大类") stock.primaryCategory = value;
        else if (key == "行业二级类") stock.secondaryCategory = value;
        else if (key == "上市日期") stock.launchDate = value;
        else if (key == "省份") stock.province = value;
        else if (key == "城市") stock.city = value;
        else if (key == "法人") stock.legalPerson = value;
        else if (key == "地址") stock.address = value;
        else if (key == "网址") stock.website = value;
        else if (key == "邮箱") stock.email = value;
        else if (key == "电话") stock.phone = value;
        else if (key == "主营业务") stock.mainBusiness = value;
        else if (key == "经营范围") stock.businessScope = value;
    }

    static std::string trim(const std::string& str) {
        size_t start = str.find_first_not_of(" \t\n\r");
        size_t end = str.find_last_not_of(" \t\n\r");
        if (start == std::string::npos) return "";
        return str.substr(start, end - start + 1);
    }

    static std::vector<std::string> split(const std::string& str, char delimiter) {
        std::vector<std::string> tokens;
        std::stringstream ss(str);
        std::string token;

        while (std::getline(ss, token, delimiter)) {
            tokens.push_back(trim(token));
        }

        return tokens;
    }

    static double safeStod(const std::string& str) {
        try {
            return std::stod(str);
        }
        catch (...) {
            return 0.0;
        }
    }
};