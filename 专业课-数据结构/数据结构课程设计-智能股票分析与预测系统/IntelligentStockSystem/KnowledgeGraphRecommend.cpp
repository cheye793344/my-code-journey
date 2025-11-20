// KnowledgeGraphRecommend.cpp
#include "StockSearch.h"
#include "MenuSystem.h"
#include "KnowledgeGraph.h"  // 包含共享头文件
#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <set>

using namespace std;

void SearchByEntity(ALGraph& G, const string& entityName) {
    vector<int> targetVertices;
    for (int i = 0; i < G.vexnum; i++) {
        if (G.vertices[i].info == entityName) {
            targetVertices.push_back(i);
        }
    }

    if (targetVertices.empty()) {
        cout << "未找到实体: " << entityName << endl;
        return;
    }

    set<int> stockVertices;

    for (int targetIdx : targetVertices) {
        ArcNode* p = G.vertices[targetIdx].firstarc;
        while (p != nullptr) {
            int connectedIdx = p->adjvex;
            if (G.vertices[connectedIdx].entity == 0) {
                stockVertices.insert(connectedIdx);
            }
            p = p->nextarc;
        }
    }

    if (stockVertices.empty()) {
        cout << "未找到与实体 '" << entityName << "' 相关的股票" << endl;
        return;
    }

    cout << "与实体 '" << entityName << "' 相关的股票推荐：" << endl;
    cout << "------------------------------------------" << endl;

    for (int stockIdx : stockVertices) {
        string stockName = G.vertices[stockIdx].info;

        vector<pair<int, string>> relationsToFind = {
            {8, "主营业务为"},
            {7, "具有注册地址"},
            {6, "位于城市"},
            {5, "位于省份"},
            {4, "属于行业二级类"},
            {3, "属于行业大类"},
            {2, "具有行业编码"},
            {1, "上市于"},
            {0, "所属机构"}
        };

        for (auto& rel : relationsToFind) {
            int relationType = rel.first;
            string outputName = rel.second;

            ArcNode* p = G.vertices[stockIdx].firstarc;
            while (p != nullptr) {
                if (p->relationship == relationType) {
                    string relatedInfo = G.vertices[p->adjvex].info;
                    cout << stockName << "->" << outputName << "->" << relatedInfo << endl;
                    break;
                }
                p = p->nextarc;
            }
        }
        cout << "------------------------------------------" << endl;
    }
}

namespace StockFunctions {
    void knowledgeGraphRecommendation() {
        MenuSystem menu;
        system("cls");
        cout << "==========================================" << endl;
        cout << "   基于知识图谱的股票推荐" << endl;
        cout << "==========================================" << endl;

        ALGraph G;
        InitALGraph(G);

        cout << "正在加载知识图谱..." << endl;
        CreateAdjList(G, "data/entity.txt");
        CreateUDG(G, "data/relation.txt");

        cout << "知识图谱加载完成！" << endl;
        cout << "顶点数: " << G.vexnum << ", 边数: " << G.arcnum << endl;

        string entityToSearch = menu.getInput("请输入要查询的实体名称: ");

        cout << endl;
        SearchByEntity(G, entityToSearch);

        menu.showMessage("");
    }
}