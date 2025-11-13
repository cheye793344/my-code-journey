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

//#include "5-基于二叉排序树的股票信息查找.h" 
int main() {
    BSTree T1 = NULL;
    BSTree T2 = NULL;
    InitBSTree(T1);
    InitBSTree(T2);
    SqList L;
    InitList(L);
    string infoFilename = "/data/workspace/myshixun/stocks.txt";
    string detailDir = "/data/workspace/myshixun/detail";
    ReadFile(L, infoFilename, detailDir);
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
    return 0;
}
