#ifndef OPEN_ADDRESSING_HASH_SEARCH_H
#define OPEN_ADDRESSING_HASH_SEARCH_H

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

typedef struct {
    // 开放地址法散列表的存储表示
    stock* key;
    int length;
} HashTable;

// 散列表初始化
void InitHT(HashTable& HT) {
    HT.key = new stock[m];
    HT.length = 0;

    // 初始化所有位置为空
    for (int i = 0; i < m; i++) {
        HT.key[i].sname = ""; // 用空字符串表示空位置
        HT.key[i].detail = NULL;
        HT.key[i].detail_count = 0;
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

// 往散列表中插入新的股票
void HTInsert(HashTable& HT, stock s, int& sumCmp, string detailDir) {
    int hashVal = Hash(s.sname);
    int currentPos = hashVal;
    int cmpCount = 0;

    // 先读取详细信息
    ReadDetail(s, detailDir);

    // 线性探测
    while (true) {
        cmpCount++;

        // 如果当前位置为空，则插入
        if (HT.key[currentPos].sname == "") {
            HT.key[currentPos] = s;
            HT.length++;
            break;
        }
        // 如果遇到相同的键（理论上不应该出现），也插入
        else if (HT.key[currentPos].sname == s.sname) {
            // 先释放原有的详细信息内存
            if (HT.key[currentPos].detail != NULL) {
                delete[] HT.key[currentPos].detail;
            }
            HT.key[currentPos] = s;
            break;
        }
        // 冲突，继续探测下一个位置
        else {
            currentPos = (currentPos + 1) % m;

            // 如果回到起始位置，说明散列表已满
            if (currentPos == hashVal) {
                break;
            }
        }
    }

    sumCmp += cmpCount;
}

// 从文件中读取股票信息
void ReadFile(HashTable& HT, int& sumCmp, string infoFilename, string detailDir) {
    ifstream file(infoFilename);
    if (!file.is_open()) {
        cout << "无法打开文件: " << infoFilename << endl;
        return;
    }

    string line;
    stock currentStock;
    bool isNewStock = true;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line == "#") {
            if (!isNewStock) {
                HTInsert(HT, currentStock, sumCmp, detailDir);
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
                    HTInsert(HT, currentStock, sumCmp, detailDir);
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
        HTInsert(HT, currentStock, sumCmp, detailDir);
    }

    file.close();
}

// 输出股票信息
void Print(HashTable HT, int pos) {
    if (pos < 0 || pos >= m || HT.key[pos].sname == "") {
        return;
    }

    stock* s = &HT.key[pos];

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

// 使用线性探测法在散列表中查找
int SearchHash(HashTable HT, string key) {
    int hashVal = Hash(key);
    int currentPos = hashVal;

    // 线性探测
    while (true) {
        // 如果当前位置为空，说明查找失败
        if (HT.key[currentPos].sname == "") {
            return -1;
        }
        // 如果找到目标键
        else if (HT.key[currentPos].sname == key) {
            return currentPos;
        }
        // 冲突，继续探测下一个位置
        else {
            currentPos = (currentPos + 1) % m;

            // 如果回到起始位置，说明查找失败
            if (currentPos == hashVal) {
                return -1;
            }
        }
    }
}

// 返回基于开放地址法的散列查找的ASL
double GetASL(HashTable HT, int sumCmp) {
    if (HT.length == 0) return 0.0;
    return (double)sumCmp / HT.length;
}

#endif // OPEN_ADDRESSING_HASH_SEARCH_H

//#include "7-基于开放地址法的股票信息散列查找.h" 
int main() {
    HashTable HT;
    InitHT(HT);
    string infoFilename = "data/stocks.txt";
    string detailDir = "data/detail";
    int sumCmp = 0; // 在插入的过程中统计比较次数，便于计算ASL
    ReadFile(HT, sumCmp, infoFilename, detailDir);
    string sname; // 输入要查找的股票英文名称
    getline(cin, sname);
    int pos = SearchHash(HT, sname);
    if (pos != -1) {
        Print(HT, pos);
        double ASL = GetASL(HT, sumCmp);
        cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
    }
    else {
        cout << "查找失败" << endl;
    }
    return 0;
}
