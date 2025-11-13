#ifndef UNION_FIND_STOCK_ANALYSIS_H
#define UNION_FIND_STOCK_ANALYSIS_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <string>
#include <vector>
#include <map>
#include <cmath>
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
    string changerate;      // 换手率（字符串形式，可能包含%）
    string risefallrate;    // 涨跌幅（字符串形式）
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

//#include "10-基于并查集的股票行业换手率分析.h"
int main() {
    SqList L;
    InitList(L);
    string infoFilename = "/data/workspace/myshixun/stocks.txt";
    string detailDir = "/data/workspace/myshixun/detail";
    ReadFile(L, infoFilename, detailDir);
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
    return 0;
}
