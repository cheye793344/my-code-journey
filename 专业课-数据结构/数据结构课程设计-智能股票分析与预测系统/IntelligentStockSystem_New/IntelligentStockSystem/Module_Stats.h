#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include "EncodingUtils.h"
// ... includes
#include <iostream>
#include <fstream>
#include <iomanip>
#include <unordered_map>
#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
#include <algorithm>
using namespace std;

namespace Level_9 {
    // 粘贴第9关 (基于链表的涨跌额分析)
#ifndef STOCK_RISE_FALL_ANALYSIS_H
#define STOCK_RISE_FALL_ANALYSIS_H


    using namespace std;

#define MAXSIZE 5000

    typedef struct stockdetail {
        string date;            // 日期
        double openprice;       // 开盘价
        double closeprice;      // 收盘价
        double highest;         // 最高价
        double lowest;          // 最低价
        double volume;          // 成交量
        double turnover;        // 成交额
        string changerate;      // 换手率
        string risefallrate;    // 涨跌幅
        double risefallamount;  // 涨跌额
    } stockdetail;              // 股票的价格信息

    typedef struct stock {
        string stockcode;       // 股票代码
        string indusname;       // 股票简称
        string sname;           // 英文名
        string briname;         // 行业编码
        string pricate;         // 一级门类（即行业大类）
        string seccate;         // 二级门类（即行业二级类）
        string listexchange;    // 上市交易所
        string wholecompany;    // 公司全称（即机构名称）
        string launchdate;      // 上市日期
        string provin;          // 省份
        string city;            // 城市
        string legalper;        // 法人
        string addr;            // 地址
        string url;             // 网址
        string email;           // 邮箱
        string callnum;         // 电话
        string mainbus;         // 主营业务
        string scopeofbus;      // 经营范围
        stockdetail* detail;    // 定义一个stockdetail类型的数组用来存放该股票每一日的相关价格信息
        int detail_count;       // detail数组的长度
    } stock;

    typedef struct {
        stock* elem;                 // 指向数组的指针
        int length;                 // 数组的长度
    } SqList;

    // 链表节点结构（用于存储筛选后的股票信息）
    struct StockNode {
        string stockcode;       // 股票代码
        string indusname;       // 股票简称
        string induscode;       // 行业编码
        string date;            // 交易日期
        double risefallamount;  // 涨跌额
        StockNode* next;        // 指向下一个节点的指针
    };

    // 初始化顺序表
    void InitList(SqList& L) {
        L.elem = new stock[MAXSIZE];
        L.length = 0;
    }

    // 释放顺序表内存
    void FreeList(SqList& L) {
        if (L.elem != NULL) {
            for (int i = 1; i <= L.length; i++) {
                if (L.elem[i].detail != NULL) {
                    delete[] L.elem[i].detail;
                }
            }
            delete[] L.elem;
            L.elem = NULL;
        }
        L.length = 0;
    }

    // 从文件夹Detail中读取Detail信息
    void ReadDetail(stock& s, string detailDir) {
        string filename = detailDir + "/" + s.stockcode + ".txt";
        ifstream file(filename);
        if (!file.is_open()) {
            s.detail = NULL;
            s.detail_count = 0;
            return;
        }

        vector<stockdetail> details;
        string line;

        while (getline(file, line)) {
            if (line.empty()) continue;

            stockdetail sd;
            stringstream ss(line);
            string item;
            vector<string> tokens;

            while (getline(ss, item, ';')) {
                tokens.push_back(item);
            }

            if (tokens.size() >= 10) {
                sd.date = tokens[0];
                sd.openprice = stod(tokens[1]);
                sd.closeprice = stod(tokens[2]);
                sd.highest = stod(tokens[3]);
                sd.lowest = stod(tokens[4]);
                sd.volume = stod(tokens[5]);
                sd.turnover = stod(tokens[6]);
                sd.changerate = tokens[7];
                sd.risefallrate = tokens[8];
                sd.risefallamount = stod(tokens[9]);

                details.push_back(sd);
            }
        }

        file.close();

        s.detail_count = details.size();
        if (s.detail_count > 0) {
            s.detail = new stockdetail[s.detail_count];
            for (int i = 0; i < s.detail_count; i++) {
                s.detail[i] = details[i];
            }
        }
        else {
            s.detail = NULL;
        }
    }

    // 从文件中读取股票信息
    void ReadFile(SqList& L, string infoFilename, string detailDir) {
        ifstream file(infoFilename);
        if (!file.is_open()) {
            cout << "无法打开文件: " << infoFilename << endl;
            return;
        }

        string line;
        stock currentStock;
        bool isNewStock = true;
        int stockCount = 0;

        while (getline(file, line)) {
            if (line.empty()) continue;

            if (line == "#") {
                if (!isNewStock) {
                    L.elem[++stockCount] = currentStock;
                    ReadDetail(L.elem[stockCount], detailDir);
                }
                isNewStock = true;
                continue;
            }

            size_t pos = line.find(':');
            if (pos != string::npos) {
                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);

                if (key == "CODE") {
                    if (!isNewStock) {
                        L.elem[++stockCount] = currentStock;
                        ReadDetail(L.elem[stockCount], detailDir);
                    }
                    currentStock = stock(); // 重置股票信息
                    currentStock.stockcode = value;
                    currentStock.detail = NULL;
                    currentStock.detail_count = 0;
                    isNewStock = false;
                }
                else if (key == "股票简称") {
                    currentStock.indusname = value;
                }
                else if (key == "英文名") {
                    currentStock.sname = value;
                }
                else if (key == "行业编码") {
                    currentStock.briname = value;
                }
                else if (key == "行业大类") {
                    currentStock.pricate = value;
                }
                else if (key == "行业二级类") {
                    currentStock.seccate = value;
                }
                else if (key == "上市交易所") {
                    currentStock.listexchange = value;
                }
                else if (key == "机构名称") {
                    currentStock.wholecompany = value;
                }
                else if (key == "上市日期") {
                    currentStock.launchdate = value;
                }
                else if (key == "省份") {
                    currentStock.provin = value;
                }
                else if (key == "城市") {
                    currentStock.city = value;
                }
                else if (key == "法人") {
                    currentStock.legalper = value;
                }
                else if (key == "地址") {
                    currentStock.addr = value;
                }
                else if (key == "网址") {
                    currentStock.url = value;
                }
                else if (key == "邮箱") {
                    currentStock.email = value;
                }
                else if (key == "电话") {
                    currentStock.callnum = value;
                }
                else if (key == "主营业务") {
                    currentStock.mainbus = value;
                }
                else if (key == "经营范围") {
                    currentStock.scopeofbus = value;
                }
            }
        }

        // 处理最后一个股票
        if (!isNewStock) {
            L.elem[++stockCount] = currentStock;
            ReadDetail(L.elem[stockCount], detailDir);
        }

        L.length = stockCount;
        file.close();
    }

    // 按涨跌额分割链表
    StockNode* SplitStockListByRiseFall(SqList& L, const string& induscode, const string& targetdate) {
        StockNode* negativeHead = NULL;  // 负值组头节点
        StockNode* negativeTail = NULL;  // 负值组尾节点
        StockNode* nonNegativeHead = NULL;  // 非负值组头节点
        StockNode* nonNegativeTail = NULL;  // 非负值组尾节点

        // 遍历所有股票
        for (int i = 1; i <= L.length; i++) {
            stock& s = L.elem[i];

            // 检查行业编码是否匹配
            if (s.briname != induscode) {
                continue;
            }

            // 检查是否有详细信息
            if (s.detail == NULL || s.detail_count == 0) {
                continue;
            }

            // 查找指定日期的交易记录
            for (int j = 0; j < s.detail_count; j++) {
                stockdetail& sd = s.detail[j];

                if (sd.date == targetdate) {
                    // 创建新节点
                    StockNode* newNode = new StockNode;
                    newNode->stockcode = s.stockcode;
                    newNode->indusname = s.indusname;
                    newNode->induscode = s.briname;
                    newNode->date = sd.date;
                    newNode->risefallamount = sd.risefallamount;
                    newNode->next = NULL;

                    // 根据涨跌额分组
                    if (sd.risefallamount < 0) {
                        // 负值组
                        if (negativeHead == NULL) {
                            negativeHead = newNode;
                            negativeTail = newNode;
                        }
                        else {
                            negativeTail->next = newNode;
                            negativeTail = newNode;
                        }
                    }
                    else {
                        // 非负值组
                        if (nonNegativeHead == NULL) {
                            nonNegativeHead = newNode;
                            nonNegativeTail = newNode;
                        }
                        else {
                            nonNegativeTail->next = newNode;
                            nonNegativeTail = newNode;
                        }
                    }
                    break; // 找到对应日期后跳出内层循环
                }
            }
        }

        // 连接两个分组：负值组在前，非负值组在后
        if (negativeHead == NULL) {
            return nonNegativeHead;
        }
        else {
            negativeTail->next = nonNegativeHead;
            return negativeHead;
        }
    }

#endif // STOCK_RISE_FALL_ANALYSIS_H
    void run() {
        cout << "=== 功能：基于链表的股票涨跌额分析 ===" << endl;
        // 原main逻辑，注意 cin >> induscode >> targetdate;
        SqList L;
        InitList(L);
        string infoFilename = "data/stocks.txt";
        string detailDir = "data//detail";
        ReadFile(L, infoFilename, detailDir);
        string induscode;
        string targetdate;
        cout << "请输入行业编码和日期(例如: 4001 2021-01-04): ";
        // ...
        cin >> induscode >> targetdate;
        StockNode* head = SplitStockListByRiseFall(L, induscode, targetdate);
        StockNode* p = head;
        while (p) {
            cout << "股票代码: " << p->stockcode << " ";
            cout << "股票简称: " << p->indusname << " ";
            cout << "行业编码：" << p->induscode << " ";
            cout << "日期: " << p->date << " ";
            cout << "涨跌额: " << p->risefallamount << endl;
            p = p->next;
        }
        while (head) {
            StockNode* tmp = head;
            head = head->next;
            delete tmp;
        }
        FreeList(L);
    }
}

namespace Level_10 {
    // 粘贴第10关 (基于并查集的换手率分析)
#ifndef UNION_FIND_STOCK_ANALYSIS_H
#define UNION_FIND_STOCK_ANALYSIS_H


    using namespace std;

#define MAXSIZE 5000  // 定义最大股票数量

    // 股票每日交易详情结构体
    typedef struct stockdetail {
        string date;            // 交易日期
        double openprice;       // 开盘价
        double closeprice;      // 收盘价
        double highest;         // 最高价
        double lowest;          // 最低价
        double volume;          // 成交量
        double turnover;        // 成交额
        string changerate;      // 换手率
        string risefallrate;    // 涨跌幅
        double risefallamount;  // 涨跌额
    } stockdetail;

    // 股票基本信息结构体
    typedef struct stock {
        string stockcode;       // 股票代码
        string indusname;       // 股票简称
        string sname;           // 英文名
        string briname;         // 行业编码（用于分类的关键字段）
        string pricate;         // 一级门类（即行业大类）
        string seccate;         // 二级门类（即行业二级类）
        string listexchange;    // 上市交易所
        string wholecompany;    // 公司全称（即机构名称）
        string launchdate;      // 上市日期
        string provin;          // 省份
        string city;            // 城市
        string legalper;        // 法人
        string addr;            // 地址
        string url;             // 网址
        string email;           // 邮箱
        string callnum;         // 电话
        string mainbus;         // 主营业务
        string scopeofbus;      // 经营范围
        stockdetail* detail;    // 指向每日交易详情数组的指针
        int detail_count;       // 交易详情记录数量
    } stock;

    // 顺序表结构（存储股票集合）
    typedef struct {
        stock* elem;            // 指向股票数组的指针
        int length;             // 当前存储的股票数量
    } SqList;

    // 初始化顺序表
    void InitList(SqList& L) {
        L.elem = new stock[MAXSIZE];
        L.length = 0;
    }

    // 释放顺序表内存
    void FreeList(SqList& L) {
        if (L.elem != NULL) {
            for (int i = 1; i <= L.length; i++) {
                if (L.elem[i].detail != NULL) {
                    delete[] L.elem[i].detail;
                }
            }
            delete[] L.elem;
            L.elem = NULL;
        }
        L.length = 0;
    }

    // 从Detail文件夹中读取Detail信息
    void ReadDetail(stock& s, string detailDir) {
        string filename = detailDir + "/" + s.stockcode + ".txt";
        ifstream file(filename);
        if (!file.is_open()) {
            s.detail = NULL;
            s.detail_count = 0;
            return;
        }

        vector<stockdetail> details;
        string line;

        while (getline(file, line)) {
            if (line.empty()) continue;

            stockdetail sd;
            stringstream ss(line);
            string item;
            vector<string> tokens;

            while (getline(ss, item, ';')) {
                tokens.push_back(item);
            }

            if (tokens.size() >= 10) {
                sd.date = tokens[0];
                sd.openprice = stod(tokens[1]);
                sd.closeprice = stod(tokens[2]);
                sd.highest = stod(tokens[3]);
                sd.lowest = stod(tokens[4]);
                sd.volume = stod(tokens[5]);
                sd.turnover = stod(tokens[6]);
                sd.changerate = tokens[7];
                sd.risefallrate = tokens[8];
                sd.risefallamount = stod(tokens[9]);

                details.push_back(sd);
            }
        }

        file.close();

        s.detail_count = details.size();
        if (s.detail_count > 0) {
            s.detail = new stockdetail[s.detail_count];
            for (int i = 0; i < s.detail_count; i++) {
                s.detail[i] = details[i];
            }
        }
        else {
            s.detail = NULL;
        }
    }

    // 从文件中读取股票信息
    void ReadFile(SqList& L, string infoFilename, string detailDir) {
        ifstream file(infoFilename);
        if (!file.is_open()) {
            cout << "无法打开文件: " << infoFilename << endl;
            return;
        }

        string line;
        stock currentStock;
        bool isNewStock = true;
        int stockCount = 0;

        while (getline(file, line)) {
            if (line.empty()) continue;

            if (line == "#") {
                if (!isNewStock) {
                    L.elem[++stockCount] = currentStock;
                    ReadDetail(L.elem[stockCount], detailDir);
                }
                isNewStock = true;
                continue;
            }

            size_t pos = line.find(':');
            if (pos != string::npos) {
                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);

                if (key == "CODE") {
                    if (!isNewStock) {
                        L.elem[++stockCount] = currentStock;
                        ReadDetail(L.elem[stockCount], detailDir);
                    }
                    currentStock = stock(); // 重置股票信息
                    currentStock.stockcode = value;
                    currentStock.detail = NULL;
                    currentStock.detail_count = 0;
                    isNewStock = false;
                }
                else if (key == "股票简称") {
                    currentStock.indusname = value;
                }
                else if (key == "英文名") {
                    currentStock.sname = value;
                }
                else if (key == "行业编码") {
                    currentStock.briname = value;
                }
                else if (key == "行业大类") {
                    currentStock.pricate = value;
                }
                else if (key == "行业二级类") {
                    currentStock.seccate = value;
                }
                else if (key == "上市交易所") {
                    currentStock.listexchange = value;
                }
                else if (key == "机构名称") {
                    currentStock.wholecompany = value;
                }
                else if (key == "上市日期") {
                    currentStock.launchdate = value;
                }
                else if (key == "省份") {
                    currentStock.provin = value;
                }
                else if (key == "城市") {
                    currentStock.city = value;
                }
                else if (key == "法人") {
                    currentStock.legalper = value;
                }
                else if (key == "地址") {
                    currentStock.addr = value;
                }
                else if (key == "网址") {
                    currentStock.url = value;
                }
                else if (key == "邮箱") {
                    currentStock.email = value;
                }
                else if (key == "电话") {
                    currentStock.callnum = value;
                }
                else if (key == "主营业务") {
                    currentStock.mainbus = value;
                }
                else if (key == "经营范围") {
                    currentStock.scopeofbus = value;
                }
            }
        }

        // 处理最后一个股票
        if (!isNewStock) {
            L.elem[++stockCount] = currentStock;
            ReadDetail(L.elem[stockCount], detailDir);
        }

        L.length = stockCount;
        file.close();
    }

    // 带路径压缩的查找
    int CompressionFind(int UFSet[], int x) {
        if (UFSet[x] < 0) {
            return x;  // 找到根节点
        }
        else {
            // 路径压缩：将x直接指向根节点
            UFSet[x] = CompressionFind(UFSet, UFSet[x]);
            return UFSet[x];
        }
    }

    // 初始化并查集
    void Init_UFSet(int UFSet[], int size) {
        for (int i = 0; i < size; i++) {
            UFSet[i] = -1;  // 初始时每个元素都是根节点，用负数表示
        }
    }

    // 合并两个子集（Root2成为新根）
    void Union_UFSet(int UFSet[], int Root1, int Root2) {
        // 确保Root1和Root2都是根节点
        Root1 = CompressionFind(UFSet, Root1);
        Root2 = CompressionFind(UFSet, Root2);

        if (Root1 != Root2) {
            // 将Root1合并到Root2
            UFSet[Root2] += UFSet[Root1];  // 更新集合大小
            UFSet[Root1] = Root2;          // Root1指向Root2
        }
    }

    // 按行业分类股票（使用并查集）
    void ClassifyByIndustry(SqList& L, int parent[], string industries[], int firstOccurrence[], int& industryCount) {
        // 初始化并查集
        Init_UFSet(parent, MAXSIZE);

        // 使用map记录每个行业编码第一次出现的位置
        map<string, int> industryMap;
        industryCount = 0;

        // 遍历所有股票，按行业编码分类
        for (int i = 1; i <= L.length; i++) {
            string industryCode = L.elem[i].briname;

            if (industryMap.find(industryCode) == industryMap.end()) {
                // 新的行业编码
                industryMap[industryCode] = i;
                industries[industryCount] = industryCode;
                firstOccurrence[industryCount] = i;
                industryCount++;
            }
            else {
                // 合并到已有的行业集合
                int root1 = CompressionFind(parent, i);
                int root2 = CompressionFind(parent, industryMap[industryCode]);
                Union_UFSet(parent, root1, root2);
            }
        }
    }

    // 计算指定行业在指定日期的总换手率
    double CalculateTotalChangeRate(SqList& L, int parent[], string targetIndustry, string targetDate) {
        double totalChangeRate = 0.0;

        // 遍历所有股票
        for (int i = 1; i <= L.length; i++) {
            // 检查行业编码是否匹配
            if (L.elem[i].briname != targetIndustry) {
                continue;
            }

            // 检查是否有详细信息
            if (L.elem[i].detail == NULL || L.elem[i].detail_count == 0) {
                continue;
            }

            // 查找指定日期的交易记录
            for (int j = 0; j < L.elem[i].detail_count; j++) {
                stockdetail& sd = L.elem[i].detail[j];

                if (sd.date == targetDate) {
                    // 将换手率字符串转换为double
                    // 注意：换手率可能包含%或其他字符，需要处理
                    string changerateStr = sd.changerate;
                    double changerate = 0.0;

                    try {
                        // 尝试直接转换
                        changerate = stod(changerateStr);
                    }
                    catch (const std::invalid_argument& e) {
                        // 如果转换失败，可能是包含%等字符
                        // 尝试提取数字部分
                        string cleanStr;
                        for (char c : changerateStr) {
                            if (isdigit(c) || c == '.' || c == '-') {
                                cleanStr += c;
                            }
                        }
                        if (!cleanStr.empty()) {
                            changerate = stod(cleanStr);
                        }
                    }

                    totalChangeRate += changerate;
                    break; // 找到对应日期后跳出内层循环
                }
            }
        }

        // 四舍五入到两位小数
        return round(totalChangeRate * 100) / 100.0;
    }

#endif // UNION_FIND_STOCK_ANALYSIS_H
    void run() {
        cout << "=== 功能：基于并查集的股票行业换手率分析 ===" << endl;
       
        // ...
        SqList L;
        InitList(L);
        string infoFilename = "data/stocks.txt";
        string detailDir = "data/detail";
        ReadFile(L, infoFilename, detailDir);
        cout << "请输入行业编码和日期: ";
        int parent[MAXSIZE];
        string industries[MAXSIZE];
        int firstOccurrence[MAXSIZE];
        int industryCount = 0;
        ClassifyByIndustry(L, parent, industries, firstOccurrence, industryCount);
        string targetIndustry, targetDate;
        cin >> targetIndustry >> targetDate;
        double totalChangeRate = CalculateTotalChangeRate(L, parent, targetIndustry, targetDate);
        cout << totalChangeRate << endl;
        FreeList(L);
    }
}

namespace Level_11 {
    // 粘贴第11关 (基于堆排序的成交量统计)
#ifndef HEAP_SORT_STOCK_VOLUME_H
#define HEAP_SORT_STOCK_VOLUME_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <algorithm>
    using namespace std;

#define MAXSIZE 5000  // 定义顺序表最大容量

    // 股票每日交易详情结构体
    typedef struct stockdetail {
        string date;            // 交易日期
        double openprice;       // 开盘价
        double closeprice;      // 收盘价
        double highest;         // 最高价
        double lowest;          // 最低价
        double volume;          // 成交量
        double turnover;        // 成交额
        string changerate;      // 换手率
        string risefallrate;    // 涨跌幅
        double risefallamount;  // 涨跌额
    } stockdetail;

    // 股票基本信息结构体
    typedef struct stock {
        string stockcode;       // 股票代码
        string indusname;       // 股票简称
        string sname;           // 英文名
        string briname;         // 行业编码（用于分类的关键字段）
        string pricate;         // 一级门类（即行业大类）
        string seccate;         // 二级门类（即行业二级类）
        string listexchange;    // 上市交易所
        string wholecompany;    // 公司全称（即机构名称）
        string launchdate;      // 上市日期
        string provin;          // 省份
        string city;            // 城市
        string legalper;        // 法人
        string addr;            // 地址
        string url;             // 网址
        string email;           // 邮箱
        string callnum;         // 电话
        string mainbus;         // 主营业务
        string scopeofbus;      // 经营范围
        stockdetail* detail;    // 指向每日交易详情数组的指针
        int detail_count;       // 交易详情记录数量
    } stock;

    // 顺序表结构（存储股票集合）
    typedef struct {
        stock* elem;            // 指向股票数组的指针
        int length;             // 当前存储的股票数量
    } SqList;

    // 初始化顺序表
    void InitList(SqList& L) {
        L.elem = new stock[MAXSIZE];
        L.length = 0;
    }

    // 释放顺序表内存
    void FreeList(SqList& L) {
        if (L.elem != NULL) {
            for (int i = 1; i <= L.length; i++) {
                if (L.elem[i].detail != NULL) {
                    delete[] L.elem[i].detail;
                }
            }
            delete[] L.elem;
            L.elem = NULL;
        }
        L.length = 0;
    }

    // 从Detail文件夹中读取Detail信息
    void ReadDetail(stock& s, string detailDir) {
        string filename = detailDir + "/" + s.stockcode + ".txt";
        ifstream file(filename);
        if (!file.is_open()) {
            s.detail = NULL;
            s.detail_count = 0;
            return;
        }

        vector<stockdetail> details;
        string line;

        while (getline(file, line)) {
            if (line.empty()) continue;

            stockdetail sd;
            stringstream ss(line);
            string item;
            vector<string> tokens;

            while (getline(ss, item, ';')) {
                tokens.push_back(item);
            }

            if (tokens.size() >= 10) {
                sd.date = tokens[0];
                sd.openprice = stod(tokens[1]);
                sd.closeprice = stod(tokens[2]);
                sd.highest = stod(tokens[3]);
                sd.lowest = stod(tokens[4]);
                sd.volume = stod(tokens[5]);
                sd.turnover = stod(tokens[6]);
                sd.changerate = tokens[7];
                sd.risefallrate = tokens[8];
                sd.risefallamount = stod(tokens[9]);

                details.push_back(sd);
            }
        }

        file.close();

        s.detail_count = details.size();
        if (s.detail_count > 0) {
            s.detail = new stockdetail[s.detail_count];
            for (int i = 0; i < s.detail_count; i++) {
                s.detail[i] = details[i];
            }
        }
        else {
            s.detail = NULL;
        }
    }

    // 从文件中读取股票信息
    void ReadFile(SqList& L, string infoFilename, string detailDir) {
        ifstream file(infoFilename);
        if (!file.is_open()) {
            cout << "无法打开文件: " << infoFilename << endl;
            return;
        }

        string line;
        stock currentStock;
        bool isNewStock = true;
        int stockCount = 0;

        while (getline(file, line)) {
            if (line.empty()) continue;

            if (line == "#") {
                if (!isNewStock) {
                    L.elem[++stockCount] = currentStock;
                    ReadDetail(L.elem[stockCount], detailDir);
                }
                isNewStock = true;
                continue;
            }

            size_t pos = line.find(':');
            if (pos != string::npos) {
                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);

                if (key == "CODE") {
                    if (!isNewStock) {
                        L.elem[++stockCount] = currentStock;
                        ReadDetail(L.elem[stockCount], detailDir);
                    }
                    currentStock = stock(); // 重置股票信息
                    currentStock.stockcode = value;
                    currentStock.detail = NULL;
                    currentStock.detail_count = 0;
                    isNewStock = false;
                }
                else if (key == "股票简称") {
                    currentStock.indusname = value;
                }
                else if (key == "英文名") {
                    currentStock.sname = value;
                }
                else if (key == "行业编码") {
                    currentStock.briname = value;
                }
                else if (key == "行业大类") {
                    currentStock.pricate = value;
                }
                else if (key == "行业二级类") {
                    currentStock.seccate = value;
                }
                else if (key == "上市交易所") {
                    currentStock.listexchange = value;
                }
                else if (key == "机构名称") {
                    currentStock.wholecompany = value;
                }
                else if (key == "上市日期") {
                    currentStock.launchdate = value;
                }
                else if (key == "省份") {
                    currentStock.provin = value;
                }
                else if (key == "城市") {
                    currentStock.city = value;
                }
                else if (key == "法人") {
                    currentStock.legalper = value;
                }
                else if (key == "地址") {
                    currentStock.addr = value;
                }
                else if (key == "网址") {
                    currentStock.url = value;
                }
                else if (key == "邮箱") {
                    currentStock.email = value;
                }
                else if (key == "电话") {
                    currentStock.callnum = value;
                }
                else if (key == "主营业务") {
                    currentStock.mainbus = value;
                }
                else if (key == "经营范围") {
                    currentStock.scopeofbus = value;
                }
            }
        }

        // 处理最后一个股票
        if (!isNewStock) {
            L.elem[++stockCount] = currentStock;
            ReadDetail(L.elem[stockCount], detailDir);
        }

        L.length = stockCount;
        file.close();
    }

    // 堆调整函数：调整子树成为大根堆
    // 堆调整函数：调整子树成为大根堆
    void HeapAdjust(SqList& L, int s, int M, int& kcn, int& rmn) {
        stock rc = L.elem[s];  // 暂存堆顶元素
        rmn++;  // 记录移动次数

        int j;
        for (j = 2 * s; j <= M; j *= 2) {
            // 比较左右子节点，选择较大的
            if (j < M) {
                kcn++;  // 比较次数
                if (L.elem[j].detail[0].volume < L.elem[j + 1].detail[0].volume) {
                    j++;  // 选择右子节点
                }
            }

            // 比较当前节点与选中的子节点
            kcn++;  // 比较次数
            if (rc.detail[0].volume >= L.elem[j].detail[0].volume) {
                break;  // 调整结束
            }

            // 将子节点上移
            L.elem[s] = L.elem[j];
            rmn++;  // 记录移动次数
            s = j;
        }

        // 将暂存元素放入最终位置
        L.elem[s] = rc;
        rmn++;  // 记录移动次数
    }

    // 建堆函数：将无序序列构建成大根堆
    void CreatHeap(SqList& L, int& kcn, int& rmn) {
        int n = L.length;
        // 从最后一个非叶子节点开始调整
        for (int i = n / 2; i > 0; i--) {
            HeapAdjust(L, i, n, kcn, rmn);
        }
    }

#endif // HEAP_SORT_STOCK_VOLUME_H
    void run() {
        cout << "=== 功能：基于堆排序的股票成交量统计 ===" << endl;
        
        // ...
        SqList L;
        InitList(L);  // 初始化顺序表
        string infoFile = "data/stocks.txt", detailDir = "data/detail";
        ReadFile(L, infoFile, detailDir);  // 加载数据
        cout << "请输入行业编码和日期: ";
        string targetInd, targetDate;
        cin >> targetInd >> targetDate;  // 输入目标行业和日期
        int k = 0;
        for (int i = 1; i <= L.length; ++i) {
            // 检查行业匹配
            if (L.elem[i].briname != targetInd) continue;
            bool ok = false;
            // 在交易记录中查找目标日期
            for (int j = 0; j < L.elem[i].detail_count; ++j) {
                if (L.elem[i].detail[j].date == targetDate) {
                    // 将目标日期记录交换到首位（便于后续堆排序）
                    swap(L.elem[i].detail[0], L.elem[i].detail[j]);
                    ok = true;
                    break;
                }
            }
            // 若找到则加入筛选列表
            if (ok) L.elem[++k] = L.elem[i];
        }
        L.length = k;  // 更新有效长度
        int num = 0;
        int kcn = 0, rmn = 0;
        CreatHeap(L, kcn, rmn);
        while (L.length > 0) {
            // 输出堆顶元素（当前成交量最大）
            if (num == 3)
                break;
            stock s = L.elem[1];
            cout << "股票代码: " << s.stockcode << '\n'
                << "股票简称: " << s.indusname << '\n'
                << "行业编码: " << s.briname << '\n'
                << "一级门类: " << s.pricate << '\n'
                << "二级门类: " << s.seccate << '\n'
                << "公司全称: " << s.wholecompany << '\n'
                << "日期: " << s.detail[0].date
                << " 成交量: " << (long long)s.detail[0].volume << '\n'
                << "----------------------------\n";

            // 堆顶与末尾元素交换
            L.elem[1] = L.elem[L.length--];
            // 调整新堆顶
            HeapAdjust(L, 1, L.length, kcn, rmn);
            num++;
        }
        cout << "总的关键字比较次数KCN为：" << kcn << endl;
        cout << "总的记录移动次数RMN为：" << rmn << endl;
        FreeList(L);  // 释放内存
    }
}

namespace Level_12 {
    // 粘贴第12关 (基于归并排序的成交量统计)
#ifndef MERGE_SORT_STOCK_VOLUME_H
#define MERGE_SORT_STOCK_VOLUME_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <iomanip>
#include <unordered_map>
#include <algorithm>
    using namespace std;

#define MAXSIZE 5000

    // 股票每日交易详情结构体
    typedef struct stockdetail {
        string date;            // 交易日期
        double openprice;       // 开盘价
        double closeprice;      // 收盘价
        double highest;         // 最高价
        double lowest;          // 最低价
        double volume;          // 成交量
        double turnover;        // 成交额
        string changerate;      // 换手率
        string risefallrate;    // 涨跌幅
        double risefallamount;  // 涨跌额
    } stockdetail;

    // 股票基本信息结构体
    typedef struct stock {
        string stockcode;       // 股票代码
        string indusname;       // 股票简称
        string sname;           // 英文名
        string briname;         // 行业编码
        string pricate;         // 一级门类（即行业大类）
        string seccate;         // 二级门类（即行业二级类）
        string listexchange;    // 上市交易所
        string wholecompany;    // 公司全称（即机构名称）
        string launchdate;      // 上市日期
        string provin;          // 省份
        string city;            // 城市
        string legalper;        // 法人
        string addr;            // 地址
        string url;             // 网址
        string email;           // 邮箱
        string callnum;         // 电话
        string mainbus;         // 主营业务
        string scopeofbus;      // 经营范围
        stockdetail* detail;    // 每日交易详情数组指针
        int detail_count;       // 交易详情数量
    } stock;

    // 日期-成交量结构体 
    typedef struct DailyVolume {
        string date;            // 交易日期
        double volume;          // 成交量
    } DailyVolume;

    // 顺序表结构
    typedef struct {
        stock* elem;            // 股票数组指针
        int length;             // 当前股票数量
    } SqList;

    // 顺序表结构
    typedef struct {
        DailyVolume* elem;      // 日期-成交量数组指针
        int length;             // 当前日期-成交量数量 
    } SqListDailyVolume;

    // 初始化顺序表
    void InitList(SqList& L) {
        L.elem = new stock[MAXSIZE + 1];  // 下标从1开始
        L.length = 0;
    }

    // 释放顺序表内存
    void FreeList(SqList& L) {
        if (L.elem != NULL) {
            for (int i = 1; i <= L.length; i++) {
                if (L.elem[i].detail != NULL) {
                    delete[] L.elem[i].detail;
                }
            }
            delete[] L.elem;
            L.elem = NULL;
        }
        L.length = 0;
    }

    // 初始化日期-成交量顺序表
    void InitDailyVolumeList(SqListDailyVolume& DL) {
        DL.elem = new DailyVolume[MAXSIZE + 1];  // 下标从1开始
        DL.length = 0;
    }

    // 释放日期-成交量顺序表内存
    void FreeDailyVolume(SqListDailyVolume& DL) {
        if (DL.elem != NULL) {
            delete[] DL.elem;
            DL.elem = NULL;
        }
        DL.length = 0;
    }

    // 从Detail文件夹中读取Detail信息
    void ReadDetail(stock& s, string detailDir) {
        string filename = detailDir + "/" + s.stockcode + ".txt";
        ifstream file(filename);
        if (!file.is_open()) {
            s.detail = NULL;
            s.detail_count = 0;
            return;
        }

        vector<stockdetail> details;
        string line;

        while (getline(file, line)) {
            if (line.empty()) continue;

            stockdetail sd;
            stringstream ss(line);
            string item;
            vector<string> tokens;

            while (getline(ss, item, ';')) {
                tokens.push_back(item);
            }

            if (tokens.size() >= 10) {
                sd.date = tokens[0];
                sd.openprice = stod(tokens[1]);
                sd.closeprice = stod(tokens[2]);
                sd.highest = stod(tokens[3]);
                sd.lowest = stod(tokens[4]);
                sd.volume = stod(tokens[5]);
                sd.turnover = stod(tokens[6]);
                sd.changerate = tokens[7];
                sd.risefallrate = tokens[8];
                sd.risefallamount = stod(tokens[9]);

                details.push_back(sd);
            }
        }

        file.close();

        s.detail_count = details.size();
        if (s.detail_count > 0) {
            s.detail = new stockdetail[s.detail_count];
            for (int i = 0; i < s.detail_count; i++) {
                s.detail[i] = details[i];
            }
        }
        else {
            s.detail = NULL;
        }
    }

    // 从文件中读取股票信息
    void ReadFile(SqList& L, string infoFilename, string detailDir) {
        ifstream file(infoFilename);
        if (!file.is_open()) {
            cout << "无法打开文件: " << infoFilename << endl;
            return;
        }

        string line;
        stock currentStock;
        bool isNewStock = true;
        int stockCount = 0;

        while (getline(file, line)) {
            if (line.empty()) continue;

            if (line == "#") {
                if (!isNewStock) {
                    L.elem[++stockCount] = currentStock;
                    ReadDetail(L.elem[stockCount], detailDir);
                }
                isNewStock = true;
                continue;
            }

            size_t pos = line.find(':');
            if (pos != string::npos) {
                string key = line.substr(0, pos);
                string value = line.substr(pos + 1);

                if (key == "CODE") {
                    if (!isNewStock) {
                        L.elem[++stockCount] = currentStock;
                        ReadDetail(L.elem[stockCount], detailDir);
                    }
                    currentStock = stock(); // 重置股票信息
                    currentStock.stockcode = value;
                    currentStock.detail = NULL;
                    currentStock.detail_count = 0;
                    isNewStock = false;
                }
                else if (key == "股票简称") {
                    currentStock.indusname = value;
                }
                else if (key == "英文名") {
                    currentStock.sname = value;
                }
                else if (key == "行业编码") {
                    currentStock.briname = value;
                }
                else if (key == "行业大类") {
                    currentStock.pricate = value;
                }
                else if (key == "行业二级类") {
                    currentStock.seccate = value;
                }
                else if (key == "上市交易所") {
                    currentStock.listexchange = value;
                }
                else if (key == "机构名称") {
                    currentStock.wholecompany = value;
                }
                else if (key == "上市日期") {
                    currentStock.launchdate = value;
                }
                else if (key == "省份") {
                    currentStock.provin = value;
                }
                else if (key == "城市") {
                    currentStock.city = value;
                }
                else if (key == "法人") {
                    currentStock.legalper = value;
                }
                else if (key == "地址") {
                    currentStock.addr = value;
                }
                else if (key == "网址") {
                    currentStock.url = value;
                }
                else if (key == "邮箱") {
                    currentStock.email = value;
                }
                else if (key == "电话") {
                    currentStock.callnum = value;
                }
                else if (key == "主营业务") {
                    currentStock.mainbus = value;
                }
                else if (key == "经营范围") {
                    currentStock.scopeofbus = value;
                }
            }
        }

        // 处理最后一个股票
        if (!isNewStock) {
            L.elem[++stockCount] = currentStock;
            ReadDetail(L.elem[stockCount], detailDir);
        }

        L.length = stockCount;
        file.close();
    }

    // 归并函数 - 严格按照教材算法8.10实现
    // 归并函数 - 严格按照教材算法8.10实现
    // 第二种实现：更接近教材图片的归并排序
    // 归并操作 - 严格按照教材算法8.10
    // 归并操作 - 严格按照教材算法8.10
    void Merge(DailyVolume R[], DailyVolume T[], int low, int mid, int high, int& kcn, int& rmn) {//t:192
        int i = low, j = mid + 1, k = low;


        // 将R中的记录由小到大地并入T中
        while (i <= mid && j <= high) {//t:1129
            kcn++; // 关键字比较次数+1
            if (R[i].volume <= R[j].volume) {//t:584
                rmn++; // 记录移动次数+1
                T[k++] = R[i++];
                //kcn++; 
            }
            else {//t:545
                rmn++; // 记录移动次数+1
                T[k++] = R[j++];
                //kcn++; 
            }
        }

        // 将剩余的R[i..mid]复制到T中
        while (i <= mid) {//t:191 
            rmn++; // 记录移动次数+1
            T[k++] = R[i++];
        }

        // 将剩余的R[j..high]复制到T中
        while (j <= high) { //t:161
            rmn++; // 记录移动次数+1
            T[k++] = R[j++];
        }

    }

    // 归并排序递归函数 - 严格按照教材算法8.11
    void MSort(DailyVolume R[], DailyVolume T[], int low, int high, int& kcn, int& rmn) {
        //t:385
        // R[low..high]归并排序后放入T[low..high]中
        if (low == high) {//193
            //rmn++; // 记录移动次数+1
            T[low] = R[low];
        }
        else {//t:192
            // 将当前序列一分为二，求出分裂点mid
            int mid = (low + high) / 2;
            // 使用动态分配创建辅助数组S
            DailyVolume* S = new DailyVolume[MAXSIZE + 1];

            // 对子序列R[low..mid]递归进行归并排序，结果放入S[low..mid]
            MSort(R, S, low, mid, kcn, rmn);

            // 对子序列R[mid+1..high]递归进行归并排序，结果放入S[mid+1..high]
            MSort(R, S, mid + 1, high, kcn, rmn);

            // 将S[low..mid]和S[mid+1..high]归并到T[low..high]
            Merge(S, T, low, mid, high, kcn, rmn);

            // 释放辅助数组
          //delete[] S; 
        }
    }

    // 归并排序主函数 - 严格按照教材算法8.11的MergeSort
    void MergeSort(SqListDailyVolume& DL, int& kcn, int& rmn) {//t:1


        // 调用MSort进行归并排序，从下标1开始到DL.length
        MSort(DL.elem, DL.elem, 1, DL.length, kcn, rmn);

    }


    // 按日期累加行业briname中所有股票的每日成交量
    void industryDailyVolume(SqList& L, SqListDailyVolume& DL, string briname, int& kcn, int& rmn) {
        // 使用简单数组存储日期-成交量对
        DailyVolume tempArray[MAXSIZE];
        int tempCount = 0;

        // 遍历所有股票
        for (int i = 1; i <= L.length; i++) {
            // 检查行业编码是否匹配
            if (L.elem[i].briname != briname) {
                continue;
            }

            // 检查是否有详细信息
            if (L.elem[i].detail == NULL || L.elem[i].detail_count == 0) {
                continue;
            }

            // 累加每日成交量
            for (int j = 0; j < L.elem[i].detail_count; j++) {
                string date = L.elem[i].detail[j].date;
                double volume = L.elem[i].detail[j].volume;

                // 在临时数组中查找该日期
                bool found = false;
                for (int k = 0; k < tempCount; k++) {

                    if (tempArray[k].date == date) {
                        tempArray[k].volume += volume;
                        found = true;
                        break;
                    }
                }

                // 如果没找到，添加新条目
                if (!found) {
                    tempArray[tempCount].date = date;
                    tempArray[tempCount].volume = volume;
                    tempCount++;
                }
            }
        }

        // 将临时数组数据存入DL（下标从1开始）
        DL.length = 0;
        for (int i = 0; i < tempCount; i++) {
            DL.elem[++DL.length] = tempArray[i];
        }

        // 对DL进行归并排序
        MergeSort(DL, kcn, rmn);
    }

#endif // MERGE_SORT_STOCK_VOLUME_H
    void run() {
        cout << "=== 功能：基于归并排序的股票成交量统计 ===" << endl;
       
        // ...
        SqList L;
        InitList(L);
        SqListDailyVolume DL;
        InitDailyVolumeList(DL);
        string infoFile = "data/stocks.txt";
        string detailDir = "data/detail";
        ReadFile(L, infoFile, detailDir);
        cout << "请输入行业编码: ";
        string briname;
        cin >> briname;

        int kcn = 0;
        int rmn = 0;
        industryDailyVolume(L, DL, briname, kcn, rmn);

        cout << "总的关键字比较次数KCN为：" << kcn << endl;
        cout << "总的记录移动次数RMN为：" << rmn << endl;
        for (int i = 1; i <= DL.length; i++)
            cout << DL.elem[i].date << " " << fixed << std::setprecision(3) << DL.elem[i].volume << endl;

        FreeList(L);
    }
}