#include <bits/stdc++.h>
using namespace std;

typedef struct {
    char no[20];					//书号 
    char name[100];					//书名 
    float price;					//价格 
}Book;

typedef struct LNode {
    Book data;                      //图书信息
    struct LNode* next;             //指向下一结点
}LNode, * LinkList;

void InitList(LinkList& L) {
    //使用动态内存分配new进行初始化 
    L = new LNode;
    L->next = nullptr;
}

void FreeList(LinkList& L) {
    //释放内存
    LNode* p = L->next;
    while (p != nullptr) {
        LNode* temp = p;
        p = p->next;
        delete temp;
    }
    delete L;
    L->next = nullptr;
}

void ReadFile(LinkList& L, string filepath) {
    //从文件中读取图书信息，利用尾插法构建链表
    ifstream infile(filepath.c_str());
    string line;
    getline(infile, line);
    getline(infile, line);
    Book temp;
    LNode* tail = L;
    while (infile >> temp.no >> temp.name >> temp.price) {
        LNode* newNode = new LNode;
        newNode->data = temp;
        newNode->next = nullptr;
        tail->next = newNode;
        tail = newNode;
    }
}

int CountBook(LinkList& L) {
    //返回图书总数
    int count = 0;
    LNode* p = L->next;
    while (p != nullptr) {
        p = p->next;
        count++;
    }
    return count;
}