#pragma once
#include "EncodingUtils.h"
// ... includes
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>
using namespace std;

namespace Level_13 {
    // 第13关 (决策树分类)
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
    void run() {
        cout << "=== 功能：基于决策树的股票分类统计 ===" << endl;
        
        // ...
        SqList L;
        InitList(L);
        string infoFilename = "data/stocks.txt";
        string detailDir = "data/detail";
        ReadFile(L, infoFilename, detailDir);
        cout << "请输入股票简称: ";
        BiTree BT;
        InitTree(BT);

        createDecisionTree(BT, L);

        string stockName;
        getline(cin, stockName);

        FindClass(BT, stockName);


        FreeList(L);
    }
}

namespace Level_14 {
    // 第14关 (规则实体识别)
#define MAXSIZE 10000
    using namespace std;

    int BF(const char* S, const char* T, int pos) {
        int i = pos;
        int j = 0;
        int sLen = strlen(S);
        int tLen = strlen(T);

        while (i < sLen && j < tLen) {
            if (S[i] == T[j]) {
                i++;
                j++;
            }
            else {
                i = i - j + 1;
                j = 0;
            }
        }

        if (j >= tLen) {
            return i - tLen;
        }
        else {
            return -1;
        }
    }

    // 【修改1】适配 GBK 编码的中文字符判断
    // GBK中，汉字的首字节通常大于 0x80 (即最高位为1)
    bool isChineseStartByte(unsigned char c) {
        return c >= 0x81;
    }

    bool EntityRecognition(const char* S, const char* T) {
        bool found = false;
        string rule(T);
        string text(S);

        int starCount = 0;
        for (char c : rule) {
            if (c == '*') starCount++;
        }

        if (starCount == 0) {
            int pos = BF(S, T, 0);
            if (pos != -1) {
                cout << string(T) << endl;
                found = true;
            }
            return found;
        }

        size_t firstStar = rule.find('*');
        size_t lastStar = rule.rfind('*');

        string prefix = rule.substr(0, firstStar);
        string suffix = rule.substr(lastStar + 1);

        // 【修改2】GBK编码下，一个汉字占 2 个字节
        int entityByteLen = starCount * 2;

        int pos = 0;
        while (pos < text.length()) {
            int prefixPos = BF(text.c_str(), prefix.c_str(), pos);
            if (prefixPos == -1) break;

            int entityStart = prefixPos + prefix.length();

            bool validEntity = true;
            if (entityStart + entityByteLen <= text.length()) {
                // 【修改3】步长改为 2
                for (int i = 0; i < entityByteLen; i += 2) {
                    if (i + 1 >= entityByteLen) { // 防止越界
                        validEntity = false;
                        break;
                    }
                    // 检查是否为汉字首字节
                    if (!isChineseStartByte((unsigned char)text[entityStart + i])) {
                        validEntity = false;
                        break;
                    }
                }
            }
            else {
                validEntity = false;
            }

            if (validEntity) {
                int suffixStart = entityStart + entityByteLen;
                if (suffixStart + suffix.length() <= text.length()) {
                    bool suffixMatch = true;
                    for (int i = 0; i < suffix.length(); i++) {
                        if (text[suffixStart + i] != suffix[i]) {
                            suffixMatch = false;
                            break;
                        }
                    }

                    if (suffixMatch) {
                        string entity = text.substr(entityStart, entityByteLen);
                        cout << entity << endl;
                        found = true;
                    }
                }
            }

            pos = prefixPos + 1;
        }

        return found;
    }

    void run() {
        cout << "=== 功能：基于规则的股票实体智能识别 ===" << endl;
        // 提示：输入规则和文本，中间用回车分隔
        cout << "请输入规则(例如 *有限公司) [回车] 文本 [回车]: " << endl;

        char keyword[100];
        char text[10000];

        // 注意：如果你是在主菜单中调用 run，主菜单的 cin >> choice 会留下一个换行符
        // 这里为了保险，先清空一下缓冲区的一行，或者你可以依赖主菜单里的 getline(cin, dummy)
        // 如果发现输入直接跳过，请取消下面这行的注释：
        // cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');

        cin.getline(keyword, 100); // 读取规则
        cin.getline(text, 10000);  // 读取文本

        if (!EntityRecognition(text, keyword))
            cout << "无匹配" << endl;
    }
}


namespace Level_15 {
    // 第15关 (规则关系挖掘)
#define MAXSIZE 10000
    using namespace std;

    typedef struct {
        string relation;    //关系名称
        string rule[10];    //规则数组
    } Relation;

    int BF(string t, string s) {
        // 字符串匹配函数
        int i = 0, j = 0;
        int tLen = t.length();
        int sLen = s.length();

        while (i < tLen && j < sLen) {
            if (t[i] == s[j]) {
                i++;
                j++;
            }
            else {
                i = i - j + 1;
                j = 0;
            }
        }

        if (j >= sLen) {
            return i - sLen;
        }
        else {
            return -1;
        }
    }

    void findAllMatches(string t, string s, int positions[], int& count) {
        // 查找实体所有匹配位置
        count = 0;
        int pos = 0;

        while (pos < t.length()) {
            int matchPos = BF(t.substr(pos), s);
            if (matchPos == -1) break;

            positions[count++] = pos + matchPos;
            pos = pos + matchPos + 1;
        }
    }

    bool RelationExtraction(char* text, char* entity1, char* entity2, Relation* r) {
        // 关系抽取函数
        string strText(text);
        string strEntity1(entity1);
        string strEntity2(entity2);

        // 查找两个实体在文本中的所有位置
        int positions1[100], positions2[100];
        int count1 = 0, count2 = 0;

        findAllMatches(strText, strEntity1, positions1, count1);
        findAllMatches(strText, strEntity2, positions2, count2);

        if (count1 == 0 || count2 == 0) {
            return false;
        }

        // 遍历所有实体位置组合，寻找相邻的实体对
        for (int i = 0; i < count1; i++) {
            for (int j = 0; j < count2; j++) {
                int pos1 = positions1[i];
                int pos2 = positions2[j];

                // 确保entity1在entity2之前
                if (pos1 < pos2) {
                    // 计算两个实体之间的内容
                    int start = pos1 + strEntity1.length();
                    int end = pos2;

                    if (start <= end) {
                        string between = strText.substr(start, end - start);

                        // 构造模式：A + between + B
                        string pattern = "A" + between + "B";

                        // 与所有规则进行比较
                        for (int k = 0; k < 10 && r[k].relation != ""; k++) {
                            for (int i = 0; i < 10 && r[k].rule[i] != ""; i++) {
                                if (pattern == r[k].rule[i]) {
                                    // 输出三元组
                                    cout << strEntity1 << "-" << r[k].relation << "-" << strEntity2 << endl;
                                    return true;
                                }
                            }
                        }
                    }
                }
            }
        }

        return false;
    }

    void InitRelation(Relation* r) {
        // 关系初始化函数
        // 初始化第一个关系
        r[0].relation = "属于行业大类";
        r[0].rule[0] = "A行业类别为B";
        r[0].rule[1] = "A属于B";
        r[0].rule[2] = "";

        // 初始化第二个关系
        r[1].relation = "所属机构";
        r[1].rule[0] = "A所属机构为B";
        r[1].rule[1] = "A的公司是B";
        r[1].rule[2] = "A隶属B";
        r[1].rule[3] = "";

        // 初始化第三个关系
        r[2].relation = "具有注册地址";
        r[2].rule[0] = "A位于B";
        r[2].rule[1] = "A坐落于B";
        r[2].rule[2] = "A总部在B";
        r[2].rule[3] = "";

        // 初始化第四个关系
        r[3].relation = "主营业务为";
        r[3].rule[0] = "A包括B";
        r[3].rule[1] = "A专注于B";
        r[3].rule[2] = "A主营业务为B";
        r[3].rule[3] = "";

        // 标记结束
        r[4].relation = "";
    }
    void run() {
        cout << "=== 功能：基于规则的关系挖掘 ===" << endl;
        cout << "请输入实体1 实体2 和 文本: " << endl;
        // ...
        char entity1[100];
        char entity2[100];
        char text[10000];

        Relation r[10];
        InitRelation(r);

        cin.getline(entity1, 100);

        cin.getline(entity2, 100);

        cin.getline(text, 10000);

        if (!RelationExtraction(text, entity1, entity2, r))
            cout << "实体之间不存在关系" << endl;

    }
}

namespace Level_16 {
    // 第16关 (知识图谱构建)
    // 及其注意：需要 entity.txt 和 relation.txt，也要放在 data 目录下
#define MVNum 30000
    using namespace std;

    // 定义关系数组，用于表示边的类型
    string Relationship[] = { "所属机构","上市于","具有行业编码","属于行业大类","属于行业二级类","位于省份","位于城市","具有注册地址","主营业务为" };

    // 定义顶点数组，用于表示实体类型和内容
    string Entity[] = { "股票简称","机构","上市交易所","行业编码","行业大类","行业二级类","省份","城市","地址","主营业务" };

    // 定义边结点结构体
    typedef struct ArcNode {
        int adjvex;                     // 该边所指向顶点的位置
        int relationship;               // 表示边的类型，即关系的类型，对应为数组下标
        struct ArcNode* nextarc;        // 下一条边
    } ArcNode;

    // 定义顶点结点结构体
    typedef struct VNode {
        int entity;                     // 表示顶点的类型，即实体的类型，对应为数组下标
        string info;                    // 表示顶点的内容，即实体的内容
        ArcNode* firstarc;              // 指向第一条依附该顶点的边的指针
    } VNode, AdjList[MVNum];

    // 定义图的结构体
    typedef struct {
        AdjList vertices;               // 邻接表
        int vexnum, arcnum;             // 图的当前顶点数和边数
    } ALGraph;

    int LocateEntity(string str) {
        // 返回str在Entity数组中的位置
        for (int i = 0; i < 10; i++) {
            if (Entity[i] == str) {
                return i;
            }
        }
        return -1;
    }

    int LocateRelationship(string str) {
        // 返回str在Relationship数组中的位置
        for (int i = 0; i < 9; i++) {
            if (Relationship[i] == str) {
                return i;
            }
        }
        return -1;
    }

    void InitALGraph(ALGraph& G) {
        // InitALGraph函数，初始化邻接表 初始化顶点数和边数为0 
        G.vexnum = 0;
        G.arcnum = 0;
        for (int i = 0; i < MVNum; i++) {
            G.vertices[i].firstarc = nullptr;
            G.vertices[i].entity = -1;
            G.vertices[i].info = "";
        }
    }

    void CreateAdjList(ALGraph& G, string filename) {
        // 从filename中按顺序读取实体存入邻接表
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "无法打开文件: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            // 去除换行符
            line.erase(line.find_last_not_of("\n\r\t") + 1);

            size_t spacePos = line.find(' ');
            if (spacePos != string::npos) {
                string entityName = line.substr(0, spacePos);
                string entityType = line.substr(spacePos + 1);

                // 找到实体类型在Entity数组中的位置
                int entityIndex = LocateEntity(entityType);
                if (entityIndex != -1) {
                    // 将实体添加到邻接表
                    G.vertices[G.vexnum].info = entityName;
                    G.vertices[G.vexnum].entity = entityIndex;
                    G.vexnum++;
                }
            }
        }
        file.close();
    }

    int LocateVex(ALGraph& G, string str) {
        // 返回str在AdjList中的位置
        for (int i = 0; i < G.vexnum; i++) {
            if (G.vertices[i].info == str) {
                return i;
            }
        }
        return -1;
    }

    void CreateUDG(ALGraph& G, string filename) {
        // 从filename中按顺序三元组存入邻接表  
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "无法打开文件: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            // 去除换行符
            line.erase(line.find_last_not_of("\n\r\t") + 1);

            // 解析三元组：头实体 关系 尾实体
            size_t firstSpace = line.find(' ');
            size_t secondSpace = line.find(' ', firstSpace + 1);

            if (firstSpace != string::npos && secondSpace != string::npos) {
                string headEntity = line.substr(0, firstSpace);
                string relation = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
                string tailEntity = line.substr(secondSpace + 1);

                // 找到关系类型在Relationship数组中的位置
                int relationIndex = LocateRelationship(relation);
                if (relationIndex != -1) {
                    // 找到头实体和尾实体在邻接表中的位置
                    int headIndex = LocateVex(G, headEntity);
                    int tailIndex = LocateVex(G, tailEntity);

                    if (headIndex != -1 && tailIndex != -1) {
                        // 正向边：头实体 -> 尾实体
                        ArcNode* newArc1 = new ArcNode;
                        newArc1->adjvex = tailIndex;
                        newArc1->relationship = relationIndex;
                        newArc1->nextarc = G.vertices[headIndex].firstarc;
                        G.vertices[headIndex].firstarc = newArc1;

                        // 反向边：尾实体 -> 头实体
                        ArcNode* newArc2 = new ArcNode;
                        newArc2->adjvex = headIndex;
                        newArc2->relationship = relationIndex;
                        newArc2->nextarc = G.vertices[tailIndex].firstarc;
                        G.vertices[tailIndex].firstarc = newArc2;

                        G.arcnum += 2; // 因为添加了正向和反向两条边
                    }
                }
            }
        }
        file.close();
    }

    void PrintGraph(ALGraph& G) {
        // 股票知识图谱输出函数 
        for (int i = 0; i < G.vexnum; i++) {
            ArcNode* p = G.vertices[i].firstarc;
            while (p != nullptr) {
                // 输出格式：头实体 关系类型 尾实体
                cout << G.vertices[i].info << " " << p->relationship << " " << G.vertices[p->adjvex].info << endl;
                p = p->nextarc;
            }
        }
    }
    void run() {
        cout << "=== 功能：基于邻接表的股票知识图谱构建 ===" << endl;
        // 修改代码中的 filename 为 "data/entity.txt" 等
        // ...
        ALGraph G;
        InitALGraph(G);
        CreateAdjList(G, "data/entity.txt");
        CreateUDG(G, "data/relation.txt");
        PrintGraph(G);
    }
}

namespace Level_17 {
    // 第17关 (知识图谱推荐)
#define MVNum 30000
    using namespace std;

    // 定义关系数组，用于表示边的类型
    string Relationship[] = { "所属机构","上市于","具有行业编码","属于行业大类","属于行业二级类","位于省份","位于城市","具有注册地址","主营业务为" };

    // 定义顶点数组，用于表示实体类型和内容
    string Entity[] = { "股票简称","机构","上市交易所","行业编码","行业大类","行业二级类","省份","城市","地址","主营业务" };

    // 定义边结点结构体
    typedef struct ArcNode {
        int adjvex;                     // 该边所指向顶点的位置
        int relationship;               // 表示边的类型，即关系的类型，对应为数组下标
        struct ArcNode* nextarc;        // 下一条边
    } ArcNode;

    // 定义顶点结点结构体
    typedef struct VNode {
        int entity;                     // 表示顶点的类型，即实体的类型，对应为数组下标
        string info;                    // 表示顶点的内容，即实体的内容
        ArcNode* firstarc;              // 指向第一条依附该顶点的边的指针
    } VNode, AdjList[MVNum];

    // 定义图的结构体
    typedef struct {
        AdjList vertices;               // 邻接表
        int vexnum, arcnum;             // 图的当前顶点数和边数
    } ALGraph;

    int LocateEntity(string str) {
        // 返回str在Entity数组中的位置
        for (int i = 0; i < 10; i++) {
            if (Entity[i] == str) {
                return i;
            }
        }
        return -1;
    }

    int LocateRelationship(string str) {
        // 返回str在Relationship数组中的位置
        for (int i = 0; i < 9; i++) {
            if (Relationship[i] == str) {
                return i;
            }
        }
        return -1;
    }

    void InitALGraph(ALGraph& G) {
        // InitALGraph函数，初始化邻接表 初始化顶点数和边数为0
        G.vexnum = 0;
        G.arcnum = 0;
        for (int i = 0; i < MVNum; i++) {
            G.vertices[i].firstarc = nullptr;
            G.vertices[i].entity = -1;
            G.vertices[i].info = "";
        }
    }

    void CreateAdjList(ALGraph& G, string filename) {
        // 从filename中按顺序读取实体存入邻接表
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "无法打开文件: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            // 去除换行符
            line.erase(line.find_last_not_of("\n\r\t") + 1);

            size_t spacePos = line.find(' ');
            if (spacePos != string::npos) {
                string entityName = line.substr(0, spacePos);
                string entityType = line.substr(spacePos + 1);

                int entityIndex = LocateEntity(entityType);
                if (entityIndex != -1) {
                    G.vertices[G.vexnum].info = entityName;
                    G.vertices[G.vexnum].entity = entityIndex;
                    G.vexnum++;
                }
            }
        }
        file.close();
    }

    int LocateVex(ALGraph& G, string str) {
        // 返回str在AdjList中的位置
        for (int i = 0; i < G.vexnum; i++) {
            if (G.vertices[i].info == str) {
                return i;
            }
        }
        return -1;
    }

    void CreateUDG(ALGraph& G, string filename) {
        // 从filename中按顺序三元组存入邻接表
        ifstream file(filename);
        if (!file.is_open()) {
            cerr << "无法打开文件: " << filename << endl;
            return;
        }

        string line;
        while (getline(file, line)) {
            if (line.empty()) continue;

            // 去除换行符
            line.erase(line.find_last_not_of("\n\r\t") + 1);

            size_t firstSpace = line.find(' ');
            size_t secondSpace = line.find(' ', firstSpace + 1);

            if (firstSpace != string::npos && secondSpace != string::npos) {
                string headEntity = line.substr(0, firstSpace);
                string relation = line.substr(firstSpace + 1, secondSpace - firstSpace - 1);
                string tailEntity = line.substr(secondSpace + 1);

                int relationIndex = LocateRelationship(relation);
                if (relationIndex != -1) {
                    int headIndex = LocateVex(G, headEntity);
                    int tailIndex = LocateVex(G, tailEntity);

                    if (headIndex != -1 && tailIndex != -1) {
                        // 正向边
                        ArcNode* newArc1 = new ArcNode;
                        newArc1->adjvex = tailIndex;
                        newArc1->relationship = relationIndex;
                        newArc1->nextarc = G.vertices[headIndex].firstarc;
                        G.vertices[headIndex].firstarc = newArc1;

                        // 反向边
                        ArcNode* newArc2 = new ArcNode;
                        newArc2->adjvex = headIndex;
                        newArc2->relationship = relationIndex;
                        newArc2->nextarc = G.vertices[tailIndex].firstarc;
                        G.vertices[tailIndex].firstarc = newArc2;

                        G.arcnum += 2;
                    }
                }
            }
        }
        file.close();
    }

    void SearchByEntity(ALGraph& G, const string& entityName) {
        // 使用知识图谱进行股票推荐
        // 首先找到包含该实体信息的所有顶点
        vector<int> targetVertices;
        for (int i = 0; i < G.vexnum; i++) {
            if (G.vertices[i].info == entityName) {
                targetVertices.push_back(i);
            }
        }

        if (targetVertices.empty()) {
            return;
        }

        // 对于每个目标顶点，找到所有相关的股票简称
        set<int> stockVertices; // 存储股票简称顶点的索引

        for (int targetIdx : targetVertices) {
            // 从目标顶点出发，找到所有连接的股票简称
            ArcNode* p = G.vertices[targetIdx].firstarc;
            while (p != nullptr) {
                int connectedIdx = p->adjvex;
                // 如果连接的顶点是股票简称，则加入集合
                if (G.vertices[connectedIdx].entity == 0) { // 0对应"股票简称"
                    stockVertices.insert(connectedIdx);
                }
                p = p->nextarc;
            }
        }

        // 对于每个股票简称，输出其相关信息
        for (int stockIdx : stockVertices) {
            string stockName = G.vertices[stockIdx].info;

            // 定义需要查找的关系类型及其对应的输出名称
            vector<pair<int, string>> relationsToFind = {
                {8, "主营业务为"},  // 主营业务为
                {7, "具有注册地址"},      // 具有注册地址
                {6, "位于城市"},      // 位于城市
                {5, "位于省份"},      // 位于省份
                {4, "属于行业二级类"}, // 属于行业二级类
                {3, "属于行业大类"},  // 属于行业大类
                {2, "具有行业编码"},  // 具有行业编码
                {1, "上市于"},// 上市于
                {0, "所属机构"}   // 所属机构
            };

            // 查找股票的所有相关信息
            for (auto& rel : relationsToFind) {
                int relationType = rel.first;
                string outputName = rel.second;

                ArcNode* p = G.vertices[stockIdx].firstarc;
                while (p != nullptr) {
                    if (p->relationship == relationType) {
                        string relatedInfo = G.vertices[p->adjvex].info;
                        cout << stockName << "->" << outputName << "->" << relatedInfo << endl;
                        break; // 找到第一个匹配的就输出
                    }
                    p = p->nextarc;
                }
            }
        }
    }
    void run() {
        cout << "=== 功能：基于知识图谱的股票推荐 ===" << endl;
        
        // ...
        ALGraph G;
        InitALGraph(G);
        CreateAdjList(G, "data/entity.txt");
        CreateUDG(G, "data/relation.txt");
        string entityToSearch;
        cout << "请输入实体名称: ";
        cin >> entityToSearch;
        SearchByEntity(G, entityToSearch);

    }
}