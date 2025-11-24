// KnowledgeGraph.h
#pragma once


#include <string>

//#define MVNum 30000
#define MVNum 30000
// 声明全局变量为 extern
extern std::string Relationship[];
extern std::string Entity[];

// 图结构定义
typedef struct ArcNode {
    int adjvex;
    int relationship;
    struct ArcNode* nextarc;
} ArcNode;

typedef struct VNode {
    int entity;
    std::string info;
    ArcNode* firstarc;
} VNode, AdjList[MVNum];

typedef struct {
    AdjList vertices;
    int vexnum, arcnum;
} ALGraph;

// 函数声明
int LocateEntity(std::string str);
int LocateRelationship(std::string str);
void InitALGraph(ALGraph& G);
void CreateAdjList(ALGraph& G, std::string filename);
int LocateVex(ALGraph& G, std::string str);
void CreateUDG(ALGraph& G, std::string filename);