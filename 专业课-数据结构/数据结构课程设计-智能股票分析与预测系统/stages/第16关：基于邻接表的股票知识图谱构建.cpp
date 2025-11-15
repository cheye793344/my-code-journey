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

//#include "16-基于邻接表的股票知识图谱构建.h" 

int main() {
    ALGraph G;
    InitALGraph(G);
    CreateAdjList(G, "/data/workspace/myshixun/entity.txt");
    CreateUDG(G, "/data/workspace/myshixun/relation.txt");
    PrintGraph(G);
    return 0;
}

