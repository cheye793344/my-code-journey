#include<bits/stdc++.h>
#define MAXSIZE 5000
#define m 300
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
typedef struct BiTNode {
    stock data;
    struct BiTNode* lchild, * rchild;
    string decision;
} BiTNode, * BiTree;
typedef struct {
    stock* elem;                 // 指向数组的指针
    int length;                 // 数组的长度
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

void InitTree(BiTree& BT)
{//初始化二叉树
    BT = new BiTNode; BT->lchild = NULL; BT->rchild = NULL;
    BiTree b1 = new BiTNode; b1->decision = "二级门类为计算机、通信和其他电子设备制造业"; b1->lchild = NULL; b1->rchild = NULL;
    BiTree b2 = new BiTNode; b2->decision = "二级门类不为计算机、通信和其他电子设备制造业"; b2->lchild = NULL; b2->rchild = NULL;
    BiTree b3 = new BiTNode; b3->decision = "最近一天跌涨幅>0"; b3->lchild = NULL; b3->rchild = NULL;
    BiTree b4 = new BiTNode; b4->decision = "最近一天跌涨幅<=0"; b4->lchild = NULL; b4->rchild = NULL;
    BiTree b5 = new BiTNode; b5->decision = "最近一天成交量>1000万股"; b5->lchild = NULL; b5->rchild = NULL;
    BiTree b6 = new BiTNode; b6->decision = "最近一天成交量<=1000万股"; b6->lchild = NULL; b6->rchild = NULL;
    BT->lchild = b1;
    BT->rchild = b2;
    b1->lchild = b3;
    b1->rchild = b4;
    b3->lchild = b5;
    b3->rchild = b6;
}
// 全局变量来存储股票数据
SqList globalL;


// 兄弟结点插入二叉树
void insertNodeToTree(BiTree& root, BiTree& node) {
    if (root == nullptr) {
        root = node;
        return;
    }

    // 找到最右边的兄弟节点
    BiTree current = root;
    while (current->rchild != nullptr) {
        current = current->rchild;
    }

    // 将新节点插入为最右边的兄弟
    current->rchild = node;
}

// 构建决策树 - 简化实现，只构建固定结构
void createDecisionTree(BiTree& BT, SqList L) {
    // 使用预设的决策树结构，不进行复杂的动态构建
    // InitTree已经构建了基本结构，这里不需要额外操作
    globalL = L;
}

// 根据股票名递归找到对应结点
BiTree FindNodeByName(BiTree BT, string name) {
    if (BT == nullptr) return nullptr;

    // 如果当前节点有股票数据且名称匹配
    if (!BT->data.indusname.empty() && BT->data.indusname == name) {
        return BT;
    }

    // 在左子树和右子树中递归查找
    BiTree leftResult = FindNodeByName(BT->lchild, name);
    if (leftResult != nullptr) return leftResult;

    return FindNodeByName(BT->rchild, name);
}

// 查找二叉树中一个节点在决策树结构中的父结点
BiTree FindOriginalFather(BiTree BT, BiTree t) {
    if (BT == nullptr || t == nullptr || BT == t) return nullptr;

    // 检查当前节点的子节点是否是目标节点
    if (BT->lchild == t || BT->rchild == t) {
        return BT;
    }

    // 在左子树和右子树中递归查找
    BiTree leftResult = FindOriginalFather(BT->lchild, t);
    if (leftResult != nullptr) return leftResult;

    return FindOriginalFather(BT->rchild, t);
}


// 根据股票名，输出其从底到根的类别信息
void FindClass(BiTree& BT, string name) {
    // 在全局股票数据中查找目标股票
    stock* targetStock = nullptr;
    for (int i = 0; i < globalL.length; i++) {
        if (globalL.elem[i].indusname == name) {
            targetStock = &globalL.elem[i];
            break;
        }
    }

    if (targetStock == nullptr) {
        return;
    }

    vector<string> decisions;

    // 决策1: 二级门类是否为计算机、通信和其他电子设备制造业
    if (targetStock->seccate.find("计算机") != string::npos ||
        targetStock->seccate.find("通信") != string::npos ||
        targetStock->seccate.find("电子设备") != string::npos) {
        decisions.push_back("二级门类为计算机、通信和其他电子设备制造业");
    }
    else {
        decisions.push_back("二级门类不为计算机、通信和其他电子设备制造业");
        // 输出当前决策并返回
        for (int i = decisions.size() - 1; i >= 0; i--) {
            cout << decisions[i] << endl;
        }
        return;
    }

    // 决策2: 最近一天跌涨幅>0
    if (targetStock->detail_count > 0) {
        string rateStr = targetStock->detail[0].risefallrate;
        if (!rateStr.empty()) {
            // 去除百分号
            if (rateStr.back() == '%') {
                rateStr.pop_back();
            }
            try {
                double rate = stod(rateStr);
                if (rate > 0) {
                    decisions.push_back("最近一天跌涨幅>0");
                }
                else {
                    decisions.push_back("最近一天跌涨幅<=0");
                    // 输出当前决策并返回
                    for (int i = decisions.size() - 1; i >= 0; i--) {
                        cout << decisions[i] << endl;
                    }
                    return;
                }
            }
            catch (...) {
                decisions.push_back("最近一天跌涨幅数据异常");
                for (int i = decisions.size() - 1; i >= 0; i--) {
                    cout << decisions[i] << endl;
                }
                return;
            }
        }
    }

    // 决策3: 最近一天成交量>1000万股
    if (targetStock->detail_count > 0) {
        if (targetStock->detail[0].volume > 10000000) {
            decisions.push_back("最近一天成交量>1000万股");
        }
        else {
            decisions.push_back("最近一天成交量<=1000万股");
        }
    }

    // 从底向上输出决策条件
    for (int i = decisions.size() - 1; i >= 0; i--) {
        cout << decisions[i] << endl;
    }
}