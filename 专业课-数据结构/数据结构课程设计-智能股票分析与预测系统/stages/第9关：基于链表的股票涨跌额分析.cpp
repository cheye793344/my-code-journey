#ifndef STOCK_RISE_FALL_ANALYSIS_H
#define STOCK_RISE_FALL_ANALYSIS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <vector>
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

//#include "9-基于链表的股票涨跌额分析.h"

int main() {
    SqList L;
    InitList(L);
    string infoFilename = "data/stocks.txt";
    string detailDir = "data/detail";
    ReadFile(L, infoFilename, detailDir);
    string induscode;
    string targetdate;
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
    return 0;
}
