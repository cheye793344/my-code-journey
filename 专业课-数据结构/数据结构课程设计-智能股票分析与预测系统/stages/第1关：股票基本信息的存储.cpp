#include<string>
#include<iostream>
#include<fstream>
#include<vector>
#include<sstream>
#include<iomanip>
#define MAXSIZE 5000
using namespace std;

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
} stockdetail;

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
    stockdetail* detail;    // 动态数组，存放每日价格信息
    int detail_count;       // detail 数组长度
} stock;

typedef struct {
    stock* elem;            // 指向股票数组的指针
    int length;             // 当前顺序表中股票数量
} SqList;

// 初始化顺序表
void InitList(SqList& L) {
    L.elem = new stock[MAXSIZE];
    L.length = 0;
}

// 释放内存
void FreeList(SqList& L) {
    for (int i = 0; i < L.length; ++i) {
        if (L.elem[i].detail != nullptr) {
            delete[] L.elem[i].detail;
        }
    }
    delete[] L.elem;
    L.length = 0;
}

// 读取某只股票的 detail 数据
void ReadDetail(stock& s, const string& detailDir) {
    string filename = detailDir + "/" + s.stockcode + ".txt";
    ifstream file(filename);
    if (!file.is_open()) return;

    // 第一次读取统计行数
    int lineCount = 0;
    string line;
    while (getline(file, line)) {
        if (!line.empty()) ++lineCount;
    }
    file.close();

    // 分配内存
    s.detail_count = lineCount;
    s.detail = new stockdetail[lineCount];

    // 第二次打开文件读取数据
    file.open(filename);
    int index = 0;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stringstream ss(line);
        vector<string> tokens;
        string token;
        while (getline(ss, token, ';')) {
            tokens.push_back(token);
        }

        if (tokens.size() >= 10) {
            s.detail[index].date = tokens[0];
            s.detail[index].openprice = stod(tokens[1]);
            s.detail[index].closeprice = stod(tokens[2]);
            s.detail[index].highest = stod(tokens[3]);
            s.detail[index].lowest = stod(tokens[4]);
            s.detail[index].volume = stod(tokens[5]);
            s.detail[index].turnover = stod(tokens[6]);
            s.detail[index].changerate = tokens[7];
            s.detail[index].risefallrate = tokens[8];
            s.detail[index].risefallamount = stod(tokens[9]);
            ++index;
        }
    }
    file.close();
}

// 读取 stocks.txt 并构建顺序表
void ReadFile(SqList& L, const string& infoFilename, const string& detailDir) {
    ifstream file(infoFilename);
    if (!file.is_open()) {
        cerr << "无法打开文件: " << infoFilename << endl;
        return;
    }

    string line;
    stock currentStock;
    bool isReadingStock = false;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line == "#") {
            if (isReadingStock) {
                ReadDetail(currentStock, detailDir);  // 加载详细数据
                L.elem[L.length] = currentStock;     // 存入顺序表（从下标 0 开始）
                L.length++;
                currentStock = stock();              // 重置
            }
            isReadingStock = false;
            continue;
        }

        size_t colonPos = line.find(':');
        if (colonPos != string::npos) {
            string key = line.substr(0, colonPos);
            string value = line.substr(colonPos + 1);

            if (key == "CODE") {
                currentStock.stockcode = value;
                isReadingStock = true;
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

    // 处理最后一个没有以 '#' 结尾的情况
    if (isReadingStock) {
        ReadDetail(currentStock, detailDir);
        L.elem[L.length] = currentStock;
        L.length++;
    }

    file.close();
}

// 输出第 pos 个股票的信息（pos 从 1 开始）
void Print(SqList L, int pos) {
    if (pos < 1 || pos > L.length) {
        cout << "位置无效" << endl;
        return;
    }

    stock s = L.elem[pos - 1];  // 注意：这里使用 pos-1 因为顺序表是从 0 开始存的

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

    // 输出每日行情（double 类型保留三位小数）
    cout << fixed << setprecision(3);
    for (int i = 0; i < s.detail_count; ++i) {
        cout << "日期: " << s.detail[i].date;
        cout << " 开盘价: " << s.detail[i].openprice;
        cout << " 收盘价: " << s.detail[i].closeprice;
        cout << " 最高价: " << s.detail[i].highest;
        cout << " 最低价: " << s.detail[i].lowest;
        cout << " 成交量: " << s.detail[i].volume;
        cout << " 成交额: " << s.detail[i].turnover;
        cout << " 换手率: " << s.detail[i].changerate;
        cout << " 涨跌幅: " << s.detail[i].risefallrate;
        cout << " 涨跌额: " << s.detail[i].risefallamount << endl;
    }
}



//#include "1-股票基本信息的存储.h" 
int main() {
    SqList L;
    InitList(L);
    string infoFilename = "data/stocks.txt";
    string detailDir = "data/detail";
    ReadFile(L, infoFilename, detailDir);
    int pos;
    cin >> pos;
    Print(L, pos);
    FreeList(L);
    return 0;
}
