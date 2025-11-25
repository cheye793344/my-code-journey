#pragma once
#include "EncodingUtils.h"
#include <string>
#include <sstream>
#include <vector>
#include <iomanip>
#include <fstream>
// 包含所有需要的头文件

using namespace std;

namespace Level_4 {
    // 粘贴第4关代码 (基于折半查找)
    // 替换 main -> run
    // 修改路径 data/stocks.txt
#define MAXSIZE 5000
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
        if (L.elem != nullptr) {
            for (int i = 1; i <= L.length; i++) {
                if (L.elem[i].detail != nullptr) {
                    delete[] L.elem[i].detail;
                }
            }
            delete[] L.elem;
            L.elem = nullptr;
        }
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

    void BubbleSort(SqList& L, int& kcn, int& rmn) {
        // 将股票信息按英文名称的字典序从小到大进行冒泡排序，并计算kcn和rmn
        kcn = 0;
        rmn = 0;

        for (int i = 1; i <= L.length - 1; i++) {
            bool swapped = false;
            for (int j = 1; j <= L.length - i; j++) {
                // 关键字比较
                kcn++;
                if (L.elem[j].sname > L.elem[j + 1].sname) {
                    // 交换元素
                    stock temp = L.elem[j];
                    L.elem[j] = L.elem[j + 1];
                    L.elem[j + 1] = temp;

                    // 记录移动次数（交换一次移动3次）
                    rmn += 3;
                    swapped = true;
                }
            }
            // 如果没有发生交换，说明已经有序
            if (!swapped) {
                break;
            }
        }
    }

    void Print(SqList L, int pos) {
        // 输出股票信息，double类型变量保留3位小数，详见输出样例
        if (pos < 1 || pos > L.length) return;

        stock s = L.elem[pos];
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

        // 输出detail信息
        if (s.detail != nullptr) {
            for (int i = 0; i < s.detail_count; i++) {
                stockdetail sd = s.detail[i];
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

    int BinarySearch(SqList& L, string sname) {
        // 在顺序表L中折半查找股票英文名称等于sname的数据元素
        // 若找到，则返回该元素在表中的下标，否则返回-1
        int low = 1;
        int high = L.length;

        while (low <= high) {
            int mid = (low + high) / 2;
            if (L.elem[mid].sname == sname) {
                return mid;
            }
            else if (L.elem[mid].sname < sname) {
                low = mid + 1;
            }
            else {
                high = mid - 1;
            }
        }
        return -1;
    }

    double GetASL(SqList& L) {
        // 返回基于顺序表的折半查找的ASL
        // 对于有序表的折半查找，ASL ≈ log₂(n+1) - 1
        if (L.length == 0) return 0;

        double sum = 0;
        for (int i = 1; i <= L.length; i++) {
            int low = 1;
            int high = L.length;
            int count = 0;

            while (low <= high) {
                count++;
                int mid = (low + high) / 2;
                if (L.elem[mid].sname == L.elem[i].sname) {
                    break;
                }
                else if (L.elem[mid].sname < L.elem[i].sname) {
                    low = mid + 1;
                }
                else {
                    high = mid - 1;
                }
            }
            sum += count;
        }
        return sum / L.length;
    }

    void run() {
        cout << "=== 功能：基于折半查找的股票信息查找 ===" << endl;
        // 原 main 逻辑
        SqList L;
        InitList(L);
        string infoFilename = "data/stocks.txt";
        string detailDir = "data/detail";
        ReadFile(L, infoFilename, detailDir);
        int kcn = 0;
        int rmn = 0;
        BubbleSort(L, kcn, rmn);
        string sname;
        cout << "请输入要查找的股票英文名: ";
        // ...
        getline(cin, sname);
        cout << "总的关键字比较次数KCN为：" << kcn << endl;
        cout << "总的记录移动次数RMN为：" << rmn << endl;
        int pos = BinarySearch(L, sname);
        if (pos != -1) {
            Print(L, pos);
            double ASL = GetASL(L);
            cout << "ASL为：" << fixed << setprecision(2) << ASL << endl;
        }
        else {
            cout << "查找失败" << endl;
        }
        FreeList(L);
    }
}

namespace Level_5 {
    // 粘贴第5关代码 (基于二叉排序树)

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

    typedef struct BSTNode {
        stock data;                  // 股票信息
        struct BSTNode* lchild;     // 左孩子指针
        struct BSTNode* rchild;     // 右孩子指针
    } BSTNode, * BSTree;

    void InitList(SqList& L) {
        // 使用动态内存分配new进行初始化
        L.elem = new stock[MAXSIZE];
        L.length = 0;
    }

    void FreeList(SqList& L) {
        // 释放内存
        if (L.elem != nullptr) {
            for (int i = 1; i <= L.length; i++) {
                if (L.elem[i].detail != nullptr) {
                    delete[] L.elem[i].detail;
                }
            }
            delete[] L.elem;
            L.elem = nullptr;
        }
        L.length = 0;
    }

    void ReadDetail(stock& s, string detailDir) {
        // 从文件夹Detail中读取Detail信息
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
        // 从文件中读取股票信息，将其按顺序存入L.elem指向的数组中
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

    int Partition(SqList& L, int low, int high, int& kcn, int& rmn) {
        // 对顺序表中的子表elem[low..high]进行一趟排序，返回枢轴位置
        // 用子表的第一个记录做枢轴记录
        // 注：L.elem[0]用来存枢轴记录
        L.elem[0] = L.elem[low];
        rmn++;
        stock pivotkey = L.elem[low];  // 保存枢轴记录
        while (low < high)
        {
            // 从右侧向左扫描，找到第一个小于枢轴的记录
            while (low < high)
            {
                if (strcmp(L.elem[high].sname.c_str(), pivotkey.sname.c_str()) >= 0)
                {
                    high--;
                    kcn++;  // 关键字比较
                }
                else
                {
                    kcn++;
                    break;
                }
            }
            L.elem[low] = L.elem[high];
            rmn++;


            // 从左侧向右扫描，找到第一个大于枢轴的记录
            while (low < high) {
                if (strcmp(L.elem[low].sname.c_str(), pivotkey.sname.c_str()) <= 0) {
                    kcn++;  // 关键字比较
                    low++;
                }
                else {
                    kcn++;
                    break;
                }
            }
            L.elem[high] = L.elem[low];
            rmn++;
        }

        L.elem[low] = L.elem[0];
        rmn++;
        return low;
    }

    void QSort(SqList& L, int low, int high, int& kcn, int& rmn) {
        // 对顺序表L中的子序列L.elem[low..high]做快速排序
        if (low < high) {
            int pivotloc = Partition(L, low, high, kcn, rmn); // 将L.elem[low..high]一分为二
            QSort(L, low, pivotloc - 1, kcn, rmn); // 对低子表递归排序
            QSort(L, pivotloc + 1, high, kcn, rmn); // 对高子表递归排序
        }
    }

    void QuickSort(SqList& L, int& kcn, int& rmn) {
        kcn = 0;
        rmn = 0;
        if (L.length > 0) {
            QSort(L, 1, L.length, kcn, rmn);
        }
    }

    void InitBSTree(BSTree& T) {
        // 二叉排序树初始化
        T = NULL;
    }

    void InsertBST(BSTree& T, stock e) {
        // 当二叉排序树T中不存在关键字等于e.sname的数据元素时，则插入该元素
        if (T == NULL) {
            T = new BSTNode;
            T->data = e;
            T->lchild = T->rchild = NULL;
        }
        else if (e.sname < T->data.sname) {
            InsertBST(T->lchild, e);
        }
        else if (e.sname > T->data.sname) {
            InsertBST(T->rchild, e);
        }
        // 如果相等，不插入（已存在）
    }

    void buildTree(BSTree& T, SqList L) {
        // 根据L中的信息构建按英文名称二叉排序树
        InitBSTree(T);
        for (int i = 1; i <= L.length; i++) {
            InsertBST(T, L.elem[i]);
        }
    }

    void Print(BSTNode* T) {
        // 输出股票信息，double类型变量保留3位小数，详见输出样例
        if (T == NULL) return;

        stock s = T->data;
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

        // 输出detail信息
        if (s.detail != nullptr) {
            for (int i = 0; i < s.detail_count; i++) {
                stockdetail sd = s.detail[i];
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

    BSTNode* SearchBST(BSTree& T, string sname) {
        // 查找对应股票，查找成功返回对应的树结点，否则返回NULL
        BSTNode* p = T;
        while (p != NULL) {
            if (sname == p->data.sname) {
                return p;
            }
            else if (sname < p->data.sname) {
                p = p->lchild;
            }
            else {
                p = p->rchild;
            }
        }
        return NULL;
    }

    // 辅助函数：计算单个节点的查找长度
    int searchPathLength(BSTree T, string sname, int depth) {
        if (T == NULL) return 0;
        if (sname == T->data.sname) {
            return depth;
        }
        else if (sname < T->data.sname) {
            return searchPathLength(T->lchild, sname, depth + 1);
        }
        else {
            return searchPathLength(T->rchild, sname, depth + 1);
        }
    }

    // 辅助函数：中序遍历计算所有节点的查找长度总和
    void inOrderTraversal(BSTree T, vector<string>& names) {
        if (T == NULL) return;
        inOrderTraversal(T->lchild, names);
        names.push_back(T->data.sname);
        inOrderTraversal(T->rchild, names);
    }

    double GetASL(BSTree& T, int count) {
        // 返回基于二叉排序树查找的ASL
        if (T == NULL || count == 0) return 0;

        // 获取所有股票英文名
        vector<string> names;
        inOrderTraversal(T, names);

        // 计算所有节点的查找长度总和
        int totalComparisons = 0;
        for (const string& name : names) {
            totalComparisons += searchPathLength(T, name, 1);
        }

        return static_cast<double>(totalComparisons) / count;
    }
    void run() {
        cout << "=== 功能：基于二叉排序树的股票信息查找 ===" << endl;
        // ...
        BSTree T1 = NULL;
        BSTree T2 = NULL;
        InitBSTree(T1);
        InitBSTree(T2);
        SqList L;
        InitList(L);
        string infoFilename = "data/stocks.txt";
        string detailDir = "data//detail";
        ReadFile(L, infoFilename, detailDir);
        cout << "请输入股票英文名称:" << endl;
        buildTree(T1, L);
        int kcn = 0; // 记录总的关键字比较次数
        int rmn = 0; // 记录总的记录移动次数
        QuickSort(L, kcn, rmn);
        buildTree(T2, L);
        string sname;
        getline(cin, sname);
        cout << "总的关键字比较次数KCN为：" << kcn << endl;
        cout << "总的记录移动次数RMN为：" << rmn << endl;
        BSTNode* t1 = SearchBST(T1, sname);
        BSTNode* t2 = SearchBST(T2, sname);
        if (t1 != NULL) {
            Print(t1);
            double ASL1 = GetASL(T1, L.length);
            cout << "排序前ASL为：" << fixed << setprecision(2) << ASL1 << endl;
        }
        else
            cout << "查找失败" << endl;
        if (t2 != NULL) {
            double ASL2 = GetASL(T2, L.length);
            cout << "排序后ASL为：" << fixed << setprecision(2) << ASL2 << endl;
        }

        FreeList(L);
    }
}

namespace Level_6 {
    // 粘贴第6关代码 (基于字典树)
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
    void run() {
        cout << "=== 功能：基于字典树的股票信息查找 ===" << endl;
        // ...
        SqList L;
        InitList(L);
        string infoFilename = "data/stocks.txt";
        string detailDir = "data/detail";
        ReadFile(L, infoFilename, detailDir);
        cout << "请输入股票英文名称前缀：" << endl;
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
    }
}

namespace Level_7 {
    // 粘贴第7关代码 (基于开放地址法散列)
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
    void run() {
        cout << "=== 功能：基于开放地址法的股票信息散列查找 ===" << endl;
        // ...
        HashTable HT;
        InitHT(HT);
        string infoFilename = "data/stocks.txt";
        string detailDir = "data/detail";
        int sumCmp = 0; // 在插入的过程中统计比较次数，便于计算ASL
        ReadFile(HT, sumCmp, infoFilename, detailDir);
        cout << "请输入要查找的股票英文名称：" << endl;
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
    }
}

namespace Level_8 {
    // 粘贴第8关代码 (基于链地址法散列)
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
    void run() {
        cout << "=== 功能：基于链地址法的股票信息散列查找 ===" << endl;
        // ...
        LinkList H[m];
        InitList(H);
        string infoFilename = "data/stocks.txt";
        string detailDir = "data/detail";
        int count = 0;	// 记录元素的总数
        int sumCmp = 0; // 在插入的过程中统计比较次数，便于计算ASL
        count = ReadFile(H, sumCmp, infoFilename, detailDir);
        cout << "请输入要查找的股票英文名称：" << endl;
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
    }
}