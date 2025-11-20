#ifndef DICTIONARY_TREE_SEARCH_H
#define DICTIONARY_TREE_SEARCH_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include <cstring>
//#include <dirent.h>
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
    stock* elem;            // 指向数组的指针
    int length;             // 数组的长度
} SqList;

typedef struct TNode {      // 字典树 
    stock* stockPtr;        // 股票指针
    struct TNode* child[53]; // 子结点的指针数组，由26个小写字母，26个大写字母，1个空格组成
} TNode, * TrieTree;

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

// 初始化字典树结点
TNode* InitTNode() {
    TNode* p = new TNode;
    p->stockPtr = NULL;
    for (int i = 0; i < 53; i++) {
        p->child[i] = NULL;
    }
    return p;
}

// 构建基于链式存储的字典树
TNode* BuildTree(SqList& L) {
    TNode* root = InitTNode();
    for (int i = 1; i <= L.length; i++) {
        TNode* p = root;
        for (int j = 0; j < L.elem[i].sname.length(); j++) {
            char ch = L.elem[i].sname[j];
            int x;
            if (ch == ' ')
                x = 52;
            else if (ch >= 'a' && ch <= 'z')
                x = ch - 'a';
            else if (ch >= 'A' && ch <= 'Z')
                x = ch - 'A' + 26;
            else
                continue; // 跳过非法字符

            if (p->child[x] == NULL) {
                p->child[x] = InitTNode();
            }
            p = p->child[x];
        }
        p->stockPtr = &L.elem[i];
    }
    return root;
}

// 查找前缀对应的节点
TNode* SearchPrefixNode(TNode* root, string prefix) {
    TNode* p = root;
    for (int i = 0; i < prefix.length(); i++) {
        char ch = prefix[i];
        int x;
        if (ch == ' ')
            x = 52;
        else if (ch >= 'a' && ch <= 'z')
            x = ch - 'a';
        else if (ch >= 'A' && ch <= 'Z')
            x = ch - 'A' + 26;
        else
            return NULL; // 非法字符

        if (p->child[x] == NULL) {
            return NULL; // 前缀不存在
        }
        p = p->child[x];
    }
    return p;
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

// 收集所有以该结点为根的子树中的股票
void CollectStocks(TNode* node, stock** s, int& count) {
    if (node == NULL) return;

    if (node->stockPtr != NULL) {
        s[count++] = node->stockPtr;
    }

    for (int i = 0; i < 53; i++) {
        if (node->child[i] != NULL) {
            CollectStocks(node->child[i], s, count);
        }
    }
}

// 计算查找成功时的平均查找长度ASL
double GetASL(SqList& L) {
    if (L.length == 0) return 0.0;

    double totalLength = 0.0;
    int totalStocks = 0;

    // 遍历所有股票，计算每个股票英文名的长度
    for (int i = 1; i <= L.length; i++) {
        if (!L.elem[i].sname.empty()) {
            totalLength += L.elem[i].sname.length();
            totalStocks++;
        }
    }

    if (totalStocks == 0) return 0.0;
    return totalLength / totalStocks;
}

// 输出股票信息
void Print(stock* s) {
    if (s == NULL) return;

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
}

#endif // DICTIONARY_TREE_SEARCH_H

//#include "6-基于字典树的股票信息查找.h" 
int main() {
    SqList L;
    InitList(L);
    string infoFilename = "data/stocks.txt";
    string detailDir = "data/detail";
    ReadFile(L, infoFilename, detailDir);
    TNode* root = BuildTree(L);
    string prefix;
    getline(cin, prefix);
    // 查找前缀节点
    TNode* prefixNode = SearchPrefixNode(root, prefix);

    // 使用动态数组存储匹配的股票
    stock** matchedStocks = new stock * [MAXSIZE];
    int count = 0;

    if (prefixNode != NULL) {
        // 收集所有匹配的股票
        CollectStocks(prefixNode, matchedStocks, count);
    }

    if (count > 0) {
        for (int i = 0; i < count; i++) {
            Print(matchedStocks[i]);
        }
        double ASL = GetASL(L);
        cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
    }
    else {
        cout << "查找失败" << endl;
    }

    // 释放动态分配的内存
    delete[] matchedStocks;
    FreeList(L);
    return 0;
}
