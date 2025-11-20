#pragma once
#include <string>
#include <vector>
#include <iostream>

// 股票详细信息结构
struct StockDetail {
    std::string date;           // 日期
    double openPrice;           // 开盘价
    double closePrice;          // 收盘价
    double highest;             // 最高价
    double lowest;              // 最低价
    double volume;              // 成交量
    double turnover;            // 成交额
    std::string changeRate;     // 换手率
    std::string riseFallRate;   // 涨跌幅
    double riseFallAmount;      // 涨跌额

    // 构造函数
    StockDetail() : openPrice(0), closePrice(0), highest(0), lowest(0),
        volume(0), turnover(0), riseFallAmount(0) {}
};

// 股票基本信息结构
struct Stock {
    std::string stockCode;      // 股票代码
    std::string stockName;      // 股票简称
    std::string englishName;    // 英文名
    std::string industryCode;   // 行业编码
    std::string primaryCategory;// 行业大类
    std::string secondaryCategory; // 行业二级类
    std::string listExchange;   // 上市交易所
    std::string companyName;    // 公司名称
    std::string launchDate;     // 上市日期
    std::string province;       // 省份
    std::string city;           // 城市
    std::string legalPerson;    // 法人
    std::string address;        // 地址
    std::string website;        // 网址
    std::string email;          // 邮箱
    std::string phone;          // 电话
    std::string mainBusiness;   // 主营业务
    std::string businessScope;  // 经营范围

    std::vector<StockDetail> details;  // 详细交易数据
    int detailCount;            // 数据条数

    // 构造函数
    Stock() : detailCount(0) {}
    //拷贝构造函数
    Stock(const Stock& other) {
        copyFrom(other);
    }
    // 赋值运算符
    Stock& operator=(const Stock& other) {
        if (this != &other) {
            copyFrom(other);
        }
        return *this;
    }

    // 显示股票信息
    void displayInfo() const {
        std::cout << "==========================================" << std::endl;
        std::cout << "股票代码: " << stockCode << std::endl;
        std::cout << "股票简称: " << stockName << std::endl;
        std::cout << "英文名: " << englishName << std::endl;
        std::cout << "公司名称: " << companyName << std::endl;
        std::cout << "上市交易所: " << listExchange << std::endl;
        std::cout << "行业编码: " << industryCode << std::endl;
        std::cout << "行业大类: " << primaryCategory << std::endl;
        std::cout << "行业二级类: " << secondaryCategory << std::endl;
        std::cout << "上市日期: " << launchDate << std::endl;
        std::cout << "省份: " << province << std::endl;
        std::cout << "城市: " << city << std::endl;
        std::cout << "法人: " << legalPerson << std::endl;
        std::cout << "地址: " << address << std::endl;
        std::cout << "网址: " << website << std::endl;
        std::cout << "邮箱: " << email << std::endl;
        std::cout << "电话: " << phone << std::endl;
        std::cout << "主营业务: " << mainBusiness << std::endl;
        std::cout << "经营范围: " << businessScope << std::endl;
        std::cout << "详细数据条数: " << detailCount << std::endl;
        std::cout << "==========================================" << std::endl;

        // 显示部分详细数据预览
        if (!details.empty()) {
            std::cout << "最近3条交易记录预览:" << std::endl;
            std::cout << "日期\t\t开盘价\t收盘价\t涨跌幅" << std::endl;
            //int count = min(3, static_cast<int>(details.size()));
            int count = (3 < static_cast<int>(details.size()) ? 3 : static_cast<int>(details.size()));
            for (int i = 0; i < count; ++i) {
                const auto& detail = details[i];
                std::cout << detail.date << "\t"
                    << detail.openPrice << "\t"
                    << detail.closePrice << "\t"
                    << detail.riseFallRate << std::endl;
            }
        }
        std::cout << "==========================================" << std::endl;
    }

private:
    // 拷贝辅助函数
    void copyFrom(const Stock& other) {
        stockCode = other.stockCode;
        stockName = other.stockName;
        englishName = other.englishName;
        industryCode = other.industryCode;
        primaryCategory = other.primaryCategory;
        secondaryCategory = other.secondaryCategory;
        listExchange = other.listExchange;
        companyName = other.companyName;
        launchDate = other.launchDate;
        province = other.province;
        city = other.city;
        legalPerson = other.legalPerson;
        address = other.address;
        website = other.website;
        email = other.email;
        phone = other.phone;
        mainBusiness = other.mainBusiness;
        businessScope = other.businessScope;

        // 关键修复：深拷贝 details 向量
        details = other.details;
        detailCount = other.detailCount;
    }
};

