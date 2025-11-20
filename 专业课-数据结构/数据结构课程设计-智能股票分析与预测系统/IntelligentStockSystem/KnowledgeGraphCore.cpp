// KnowledgeGraphCore.cpp
#include "KnowledgeGraph.h"
#include <iostream>
#include <fstream>

using namespace std;

// 定义全局变量
string Relationship[] = { "所属机构","上市于","具有行业编码","属于行业大类","属于行业二级类","位于省份","位于城市","具有注册地址","主营业务为" };
string Entity[] = { "股票简称","机构","上市交易所","行业编码","行业大类","行业二级类","省份","城市","地址","主营业务" };

int LocateEntity(string str) {
    for (int i = 0; i < 10; i++) {
        if (Entity[i] == str) {
            return i;
        }
    }
    return -1;
}

int LocateRelationship(string str) {
    for (int i = 0; i < 9; i++) {
        if (Relationship[i] == str) {
            return i;
        }
    }
    return -1;
}

void InitALGraph(ALGraph& G) {
    G.vexnum = 0;
    G.arcnum = 0;
    for (int i = 0; i < MVNum; i++) {
        G.vertices[i].firstarc = nullptr;
        G.vertices[i].entity = -1;
        G.vertices[i].info = "";
    }
}

void CreateAdjList(ALGraph& G, string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开文件: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
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
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].info == str) {
            return i;
        }
    }
    return -1;
}

void CreateUDG(ALGraph& G, string filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cerr << "无法打开文件: " << filename << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        if (line.empty()) continue;
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
                    ArcNode* newArc1 = new ArcNode;
                    newArc1->adjvex = tailIndex;
                    newArc1->relationship = relationIndex;
                    newArc1->nextarc = G.vertices[headIndex].firstarc;
                    G.vertices[headIndex].firstarc = newArc1;

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