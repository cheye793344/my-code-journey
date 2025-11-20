// KnowledgeGraphBuild.cpp
#include "StockSearch.h"
#include "MenuSystem.h"
#include "KnowledgeGraph.h"  // 包含共享头文件
#include <iostream>
#include <fstream>
#include <string>

using namespace std;

void PrintGraph(ALGraph& G) {
    for (int i = 0; i < G.vexnum; i++) {
        ArcNode* p = G.vertices[i].firstarc;
        while (p != nullptr) {
            cout << G.vertices[i].info << " " << Relationship[p->relationship] << " " << G.vertices[p->adjvex].info << endl;
            p = p->nextarc;
        }
    }
}

namespace StockFunctions {
    void buildKnowledgeGraph() {
        MenuSystem menu;
        system("cls");
        cout << "==========================================" << endl;
        cout << "   基于邻接表的股票知识图谱构建" << endl;
        cout << "==========================================" << endl;

        ALGraph G;
        InitALGraph(G);

        cout << "正在构建知识图谱..." << endl;
        CreateAdjList(G, "data/entity.txt");
        CreateUDG(G, "data/relation.txt");

        cout << "知识图谱构建完成！" << endl;
        cout << "顶点数: " << G.vexnum << ", 边数: " << G.arcnum << endl;

        cout << endl << "知识图谱内容：" << endl;
        cout << "------------------------------------------" << endl;
        PrintGraph(G);

        menu.showMessage("");
    }
}