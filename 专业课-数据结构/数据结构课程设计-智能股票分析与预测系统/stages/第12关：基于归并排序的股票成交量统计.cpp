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

//#include "12-基于归并排序的股票成交量统计.h" 
int main() {
    SqList L;
    InitList(L);
    SqListDailyVolume DL;
    InitDailyVolumeList(DL);
    string infoFile = "data/stocks.txt";
    string detailDir = "data/detail";
    ReadFile(L, infoFile, detailDir);

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
    return 0;
}
