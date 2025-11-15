#include <bits/stdc++.h>
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

//#include "17-基于知识图谱的股票推荐.h"

int main() {
    ALGraph G;
    InitALGraph(G);
    CreateAdjList(G, "/data/workspace/myshixun/entity.txt");
    CreateUDG(G, "/data/workspace/myshixun/relation.txt");
    string entityToSearch;
    cin >> entityToSearch;
    SearchByEntity(G, entityToSearch);

    return 0;
}
