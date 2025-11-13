#ifndef CHAIN_ADDRESSING_HASH_SEARCH_H
#define CHAIN_ADDRESSING_HASH_SEARCH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstring>
#include <vector>
using namespace std;

#define m 400

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

typedef struct LNode {
    stock data;                  // 股票信息
    struct LNode* next;         // 指向下一级结点
} LNode, * LinkList;

// 全局变量，用于存储detail文件夹路径
string globalDetailDir;

// 链表初始化
void InitList(LinkList* H) {
    for (int i = 0; i < m; i++) {
        H[i] = new LNode;  // 创建头结点
        H[i]->next = NULL;
    }
}

// 实现散列函数
int Hash(string sname) {
    int sum = 0;
    for (int i = 0; i < sname.length(); i++) {
        sum += (i * i * int(sname[i]));
    }
    return sum % 397;
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

// 后插法往散列表中插入新的股票
void ListInsert(LinkList* H, stock s, int& sumCmp) {
    int hashVal = Hash(s.sname);
    LinkList p = H[hashVal];
    int cmpCount = 0;

    // 先读取详细信息（使用全局变量）
    ReadDetail(s, globalDetailDir);

    // 遍历链表，统计比较次数
    while (p->next != NULL) {
        cmpCount++;
        p = p->next;
    }

    // 创建新节点并插入
    LinkList newNode = new LNode;
    newNode->data = s;
    newNode->next = NULL;
    p->next = newNode;

    sumCmp += cmpCount + 1;  // +1 是因为新节点也需要比较一次
}

// 从文件中读取股票信息
int ReadFile(LinkList* H, int& sumCmp, string infoFilename, string detailDir) {
    // 设置全局detail目录路径
    globalDetailDir = detailDir;

    ifstream file(infoFilename);
    if (!file.is_open()) {
        cout << "无法打开文件: " << infoFilename << endl;
        return 0;
    }

    string line;
    stock currentStock;
    bool isNewStock = true;
    int stockCount = 0;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line == "#") {
            if (!isNewStock) {
                ListInsert(H, currentStock, sumCmp);
                stockCount++;
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
                    ListInsert(H, currentStock, sumCmp);
                    stockCount++;
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
        ListInsert(H, currentStock, sumCmp);
        stockCount++;
    }

    file.close();
    return stockCount;
}

// 在散列表中查找股票
int SearchHL(LinkList* H, string key) {
    int hashVal = Hash(key);
    LinkList p = H[hashVal]->next;  // 跳过头结点

    while (p != NULL) {
        if (p->data.sname == key) {
            return hashVal;  // 返回散列表位置
        }
        p = p->next;
    }

    return -1;  // 查找失败
}

// 返回基于链地址法的散列查找的ASL
double GetASL(int sumCmp, int count) {
    if (count == 0) return 0.0;
    return (double)sumCmp / count;
}

// 输出股票信息
void Print(LinkList T, string sname) {
    // 在链表中查找匹配的股票
    LinkList p = T;
    while (p != NULL) {
        if (p->data.sname == sname) {
            stock* s = &(p->data);

            cout << "股票代码: " << s->stockcode << endl;
            cout << "股票简称: " << s->indusname << endl;
            cout << "英文名: " << s->sname << endl;
            cout << "行业编码: " << s->briname << endl;
            cout << "一级门类: " << s->pricate << endl;
            cout << "二级门类: " << s->seccate << endl;
            cout << "上市交易所: " << s->listexchange << endl;
            cout << "公司全称: " << s->wholecompany << endl;
            cout << "上市日期: " << s->launchdate << endl;
            cout << "省份: " << s->provin << endl;
            cout << "城市: " << s->city << endl;
            cout << "法人: " << s->legalper << endl;
            cout << "地址: " << s->addr << endl;
            cout << "网址: " << s->url << endl;
            cout << "邮箱: " << s->email << endl;
            cout << "电话: " << s->callnum << endl;
            cout << "主营业务: " << s->mainbus << endl;
            cout << "经营范围: " << s->scopeofbus << endl;

            // 输出详细信息
            if (s->detail != NULL && s->detail_count > 0) {
                for (int i = 0; i < s->detail_count; i++) {
                    cout << "日期: " << s->detail[i].date
                        << " 开盘价: " << fixed << setprecision(3) << s->detail[i].openprice
                        << " 收盘价: " << fixed << setprecision(3) << s->detail[i].closeprice
                        << " 最高价: " << fixed << setprecision(3) << s->detail[i].highest
                        << " 最低价: " << fixed << setprecision(3) << s->detail[i].lowest
                        << " 成交量: " << fixed << setprecision(3) << s->detail[i].volume
                        << " 成交额: " << fixed << setprecision(3) << s->detail[i].turnover
                        << " 换手率: " << s->detail[i].changerate
                        << " 涨跌幅: " << s->detail[i].risefallrate
                        << " 涨跌额: " << fixed << setprecision(3) << s->detail[i].risefallamount << endl;
                }
            }
            return;
        }
        p = p->next;
    }
}

#endif // CHAIN_ADDRESSING_HASH_SEARCH_H

//#include "8-基于链地址法的股票信息散列查找.h" 
int main() {
    LinkList H[m];
    InitList(H);
    string infoFilename = "/data/workspace/myshixun/stocks.txt";
    string detailDir = "/data/workspace/myshixun/detail";
    int count = 0;	// 记录元素的总数
    int sumCmp = 0; // 在插入的过程中统计比较次数，便于计算ASL
    count = ReadFile(H, sumCmp, infoFilename, detailDir);
    string sname; // 输入要查找的股票英文名称
    getline(cin, sname);
    int pos = SearchHL(H, sname);
    if (pos != -1) {
        LinkList p = H[pos]->next; // 查找成功，将p指向单链表头结点
        Print(p, sname);
        double ASL = GetASL(sumCmp, count);
        cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
    }
    else {
        cout << "查找失败" << endl;
    }
    return 0;
}
