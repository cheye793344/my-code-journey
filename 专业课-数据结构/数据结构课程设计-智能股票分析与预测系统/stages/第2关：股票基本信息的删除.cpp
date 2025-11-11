#include<bits/stdc++.h>
#define MAXSIZE 5000
using namespace std;

typedef struct stockdetail {
    string date;//日期 
    double openprice;//开盘价
    double closeprice;//收盘价
    double highest;//最高价
    double lowest;//最低价
    double volume;//成交量
    double turnover;//成交额
    string changerate;//换手率
    string risefallrate;//涨跌幅
    double risefallamount;//涨跌额
}stockdetail;//股票的价格信息 

typedef struct stock {
    string stockcode;//股票代码
    string indusname;//股票简称
    string sname;//英文名 
    string briname;//行业编码
    string pricate;//一级门类（即行业大类）
    string seccate;//二级门类（即行业二级类）
    string listexchange;//上市交易所
    string wholecompany;//公司全称（即机构名称）
    string launchdate;//上市日期
    string provin;//省份
    string city;//城市
    string legalper;//法人
    string addr;//地址
    string url;//网址
    string email;//邮箱
    string callnum;//电话
    string mainbus;//主营业务
    string scopeofbus;//经营范围
    stockdetail* detail;//定义一个stockdetail类型的数组用来存放该股票每一日的相关价格信息  
    int detail_count;//detail数组的长度 
}stock;

typedef struct {
    stock* elem;                 // 指向数组的指针
    int length;                 // 数组的长度
} SqList;

void InitList(SqList& L) {
    // 使用动态内存分配new进行初始化
    L.elem = new stock[MAXSIZE];
    L.length = 0;
}

void FreeList(SqList& L) {
    // 释放内存
    delete[] L.elem;
    L.length = 0;
}

void ReadDetail(stock& s, string detailDir) {
    // 从Detail文件夹中读取Detail信息
    string detailFile = detailDir + "/" + s.stockcode + ".txt";
    ifstream file(detailFile);
    if (!file.is_open()) {
        s.detail_count = 0;
        s.detail = nullptr;
        return;
    }

    vector<stockdetail> details;
    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;

        stockdetail sd;
        stringstream ss(line);
        string token;

        // 按分号分割数据
        vector<string> tokens;
        while (getline(ss, token, ';')) {
            tokens.push_back(token);
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

    // 将vector转换为数组
    s.detail_count = details.size();
    if (s.detail_count > 0) {
        s.detail = new stockdetail[s.detail_count];
        for (int i = 0; i < s.detail_count; i++) {
            s.detail[i] = details[i];
        }
    }
    else {
        s.detail = nullptr;
    }
}

void ReadFile(SqList& L, string infoFilename, string detailDir) {
    // 从文件中读取股票信息，将其按顺序存入L.elem指向的数组中，数组下标从1开始存储
    ifstream file(infoFilename);
    if (!file.is_open()) {
        return;
    }

    L.length = 0;
    string line;
    stock currentStock;
    bool readingStock = false;

    while (getline(file, line)) {
        if (line.empty()) continue;

        if (line == "#") {
            // 遇到分隔符，保存当前股票信息
            if (readingStock) {
                L.length++;
                L.elem[L.length] = currentStock;
                // 读取detail信息
                ReadDetail(L.elem[L.length], detailDir);
                readingStock = false;
            }
            continue;
        }

        // 解析股票信息
        size_t pos = line.find(':');
        if (pos != string::npos) {
            string key = line.substr(0, pos);
            string value = line.substr(pos + 1);

            if (key == "CODE") {
                readingStock = true;
                currentStock = stock(); // 重置股票信息
                currentStock.stockcode = value;
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
    if (readingStock) {
        L.length++;
        L.elem[L.length] = currentStock;
        ReadDetail(L.elem[L.length], detailDir);
    }

    file.close();
}

void SaveFile(SqList& L, string filename) {
    // 保存基本信息到new_stocks.txt
    ofstream file(filename);
    if (!file.is_open()) {
        return;
    }

    for (int i = 1; i <= L.length; i++) {
        stock s = L.elem[i];
        file << "CODE:" << s.stockcode << endl;
        file << "股票简称:" << s.indusname << endl;
        file << "英文名:" << s.sname << endl;
        file << "机构名称:" << s.wholecompany << endl;
        file << "上市交易所:" << s.listexchange << endl;
        file << "行业编码:" << s.briname << endl;
        file << "行业大类:" << s.pricate << endl;
        file << "行业二级类:" << s.seccate << endl;
        file << "上市日期:" << s.launchdate << endl;
        file << "省份:" << s.provin << endl;
        file << "城市:" << s.city << endl;
        file << "法人:" << s.legalper << endl;
        file << "地址:" << s.addr << endl;
        file << "网址:" << s.url << endl;
        file << "邮箱:" << s.email << endl;
        file << "电话:" << s.callnum << endl;
        file << "主营业务:" << s.mainbus << endl;
        file << "经营范围:" << s.scopeofbus << endl;

        if (i < L.length) {
            file << "#" << endl;
        }
    }

    file.close();
}

void SaveDetail(SqList& L, string detailDir) {
    //保存detail信息到new_detail文件夹
    for (int i = 1; i <= L.length; i++) {
        stock s = L.elem[i];
        string detailFile = detailDir + "/" + s.stockcode + ".txt";
        ofstream file(detailFile);

        if (file.is_open() && s.detail != nullptr) {
            for (int j = 0; j < s.detail_count; j++) {
                stockdetail sd = s.detail[j];
                file << sd.date << ";" << fixed << setprecision(3) << sd.openprice << ";"
                    << sd.closeprice << ";" << sd.highest << ";" << sd.lowest << ";"
                    << sd.volume << ";" << sd.turnover << ";" << sd.changerate << ";"
                    << sd.risefallrate << ";" << sd.risefallamount;
                if (j < s.detail_count - 1) {
                    file << endl;
                }
            }
            file.close();
        }
    }
}

stock* DeleteStock(SqList& L, string indusname) {
    //在顺序表L中删除简称为indusname的股票
    for (int i = 1; i <= L.length; i++) {
        if (L.elem[i].indusname == indusname) {
            // 找到要删除的股票，创建副本返回
            stock* deletedStock = new stock(L.elem[i]);

            // 从顺序表中删除
            for (int j = i; j < L.length; j++) {
                L.elem[j] = L.elem[j + 1];
            }
            L.length--;

            return deletedStock;
        }
    }
    return nullptr; // 没找到
}

void Print(stock* s) {
    // 输出股票信息，double类型变量保留3位小数
    if (s == nullptr) return;

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

    // 输出detail信息
    if (s->detail != nullptr) {
        for (int i = 0; i < s->detail_count; i++) {
            stockdetail sd = s->detail[i];
            cout << "日期: " << sd.date
                << " 开盘价: " << fixed << setprecision(3) << sd.openprice
                << " 收盘价: " << sd.closeprice
                << " 最高价: " << sd.highest
                << " 最低价: " << sd.lowest
                << " 成交量: " << sd.volume
                << " 成交额: " << sd.turnover
                << " 换手率: " << sd.changerate
                << " 涨跌幅: " << sd.risefallrate
                << " 涨跌额: " << sd.risefallamount << endl;
        }
    }
}

//#include"2-股票基本信息的删除.h"


bool CheckStock(SqList& L, string indusname) {
    // 检查股票是否存在函数
    for (int i = 1; i <= L.length; i++) {
        if (L.elem[i].indusname == indusname) {
            return false; // 股票存在，删除失败
        }
    }
    return true; // 股票不存在，删除成功
}

int main() {
    SqList L;
    InitList(L);
    string originInfoFilename = "/data/workspace/myshixun/stocks.txt";
    string newInfoFilename = "/data/workspace/myshixun/2-股票基本信息的删除/new_stocks.txt";
    string detailDir = "/data/workspace/myshixun/detail";
    string newDetailDir = "/data/workspace/myshixun/2-股票基本信息的删除/new_detail";

    ReadFile(L, originInfoFilename, detailDir);

    string indusname;
    cin >> indusname;

    // 执行删除操作
    stock* s = DeleteStock(L, indusname);

    if (s) {
        // 保存到新文件
        SaveFile(L, newInfoFilename);
        SaveDetail(L, newDetailDir);
        // 重新读取新文件
        ReadFile(L, newInfoFilename, newDetailDir);

        // 检查删除是否成功
        if (CheckStock(L, indusname)) {
            // 删除成功，输出被删除的股票信息
            Print(s);
        }
        else {
            cout << "删除失败" << endl;
        }
    }
    else {
        cout << "删除失败" << endl;
    }
    // 释放被删除股票的内存
    FreeList(L);
    return 0;
}