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

// 堆调整函数：调整子树成为大根堆
// 堆调整函数：调整子树成为大根堆
void HeapAdjust(SqList& L, int s, int m, int& kcn, int& rmn) {
    stock rc = L.elem[s];  // 暂存堆顶元素
    rmn++;  // 记录移动次数

    int j;
    for (j = 2 * s; j <= m; j *= 2) {
        // 比较左右子节点，选择较大的
        if (j < m) {
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

//#include "11-基于堆排序的股票成交量统计.h"

int main() {
    SqList L;
    InitList(L);  // 初始化顺序表
    string infoFile = "data/stocks.txt";
    string detailDir = "data/detail";
    ReadFile(L, infoFile, detailDir);  // 加载数据
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
    return 0;
}