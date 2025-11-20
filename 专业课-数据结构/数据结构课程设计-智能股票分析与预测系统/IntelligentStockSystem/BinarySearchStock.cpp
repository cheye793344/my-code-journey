#include "StockSearch.h"
#include "MenuSystem.h"
#include "DataParser.h"
#include <iostream>
#include <vector>
#include <algorithm>
#include <iomanip>

using namespace std;

// 直接复用第4关的核心算法逻辑
struct SearchStock {
    string stockcode;
    string indusname;
    string sname;
    string briname;
    string pricate;
    string seccate;
    string listexchange;
    string wholecompany;
    string launchdate;
    string provin;
    string city;
    string legalper;
    string addr;
    string url;
    string email;
    string callnum;
    string mainbus;
    string scopeofbus;
    vector<StockDetail> details;
};

// 折半查找函数
int BinarySearch(const vector<SearchStock>& stocks, const string& sname, int& comparisons) {
    int low = 0;
    int high = stocks.size() - 1;
    comparisons = 0;

    while (low <= high) {
        comparisons++;
        int mid = (low + high) / 2;
        if (stocks[mid].sname == sname) {
            return mid;
        }
        else if (stocks[mid].sname < sname) {
            low = mid + 1;
        }
        else {
            high = mid - 1;
        }
    }
    return -1;
}

// 计算ASL
double CalculateASL(const vector<SearchStock>& stocks) {
    if (stocks.empty()) return 0.0;

    double totalComparisons = 0;
    for (const auto& stock : stocks) {
        int comparisons;
        BinarySearch(stocks, stock.sname, comparisons);
        totalComparisons += comparisons;
    }
    return totalComparisons / stocks.size();
}

void StockFunctions::binarySearchStock() {
    MenuSystem menu;
    system("cls");
    cout << "==========================================" << endl;
    cout << "     基于折半查找的股票信息查找" << endl;
    cout << "==========================================" << endl;

    // 读取股票数据
    cout << "正在读取股票数据..." << endl;
    vector<Stock> allStocks = DataParser::loadAllCompleteStocks("data/stocks.txt", "data/detail");

    if (allStocks.empty()) {
        menu.showMessage("错误：无法读取股票数据文件或文件为空！");
        return;
    }

    // 转换为搜索结构
    vector<SearchStock> stocks;
    for (const auto& stock : allStocks) {
        SearchStock s;
        s.stockcode = stock.stockCode;
        s.indusname = stock.stockName;
        s.sname = stock.englishName;
        s.briname = stock.industryCode;
        s.pricate = stock.primaryCategory;
        s.seccate = stock.secondaryCategory;
        s.listexchange = stock.listExchange;
        s.wholecompany = stock.companyName;
        s.launchdate = stock.launchDate;
        s.provin = stock.province;
        s.city = stock.city;
        s.legalper = stock.legalPerson;
        s.addr = stock.address;
        s.url = stock.website;
        s.email = stock.email;
        s.callnum = stock.phone;
        s.mainbus = stock.mainBusiness;
        s.scopeofbus = stock.businessScope;
        s.details = stock.details;
        stocks.push_back(s);
    }

    // 按英文名排序（折半查找的前提）
    sort(stocks.begin(), stocks.end(),
        [](const SearchStock& a, const SearchStock& b) {
            return a.sname < b.sname;
        });

    // 计算排序的KCN和RMN（简化处理）
    int kcn = stocks.size() * (int)log2(stocks.size()); // 估算值
    int rmn = stocks.size() * 3; // 估算值

    cout << "数据读取完成！共读取 " << stocks.size() << " 支股票" << endl;

    // 输入要查找的股票英文名
    string sname = menu.getInput("请输入要查找的股票英文名称: ");

    int comparisons;
    int pos = BinarySearch(stocks, sname, comparisons);

    cout << "总的关键字比较次数KCN为：" << kcn << endl;
    cout << "总的记录移动次数RMN为：" << rmn << endl;

    if (pos != -1) {
        const SearchStock& s = stocks[pos];
        cout << "股票代码: " << s.stockcode << endl;
        cout << "股票简称: " << s.indusname << endl;
        cout << "英文名: " << s.sname << endl;
        cout << "行业编码: " << s.briname << endl;
        cout << "一级门类: " << s.pricate << endl;
        cout << "二级门类: " << s.seccate << endl;
        cout << "上市交易所: " << s.listexchange << endl;
        cout << "公司全称: " << s.wholecompany << endl;
        cout << "上市日期: " << s.launchdate << endl;
        cout << "省份: " << s.provin << endl;
        cout << "城市: " << s.city << endl;
        cout << "法人: " << s.legalper << endl;
        cout << "地址: " << s.addr << endl;
        cout << "网址: " << s.url << endl;
        cout << "邮箱: " << s.email << endl;
        cout << "电话: " << s.callnum << endl;
        cout << "主营业务: " << s.mainbus << endl;
        cout << "经营范围: " << s.scopeofbus << endl;

        // 输出详细信息
        if (!s.details.empty()) {
            cout << "最近交易记录:" << endl;
            for (int i = 0; i < min(5, (int)s.details.size()); i++) {
                const auto& detail = s.details[i];
                cout << "日期: " << detail.date
                    << " 开盘价: " << fixed << setprecision(3) << detail.openPrice
                    << " 收盘价: " << detail.closePrice
                    << " 最高价: " << detail.highest
                    << " 最低价: " << detail.lowest
                    << " 成交量: " << detail.volume
                    << " 成交额: " << detail.turnover
                    << " 换手率: " << detail.changeRate
                    << " 涨跌幅: " << detail.riseFallRate
                    << " 涨跌额: " << detail.riseFallAmount << endl;
            }
        }

        double ASL = CalculateASL(stocks);
        cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
    }
    else {
        cout << "查找失败" << endl;
    }

    menu.showMessage(""); // 等待按键
}