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
    LNode* p = new LNode;
    p = L->next;
    while (p != nullptr) {
        LNode* temp = p;
        p = p->next;
        delete temp;
    }
    delete L;
    L->next = nullptr;
}

void ReadFile(LinkList& L, string filePath) {
    //从文件中读取图书信息，利用尾插法构建链表
    ifstream infile(filePath.c_str());
    string line;
    getline(infile, line);
    getline(infile, line);
    Book temp;
    LNode* tail = L;
    while (infile >> temp.no >> temp.name >> temp.price) {
        LNode* newNode = new LNode;
        newNode->next = nullptr;
        newNode->data = temp;
        tail->next = newNode;
        tail = newNode;
    }
    infile.close();
}

void SaveFile(LinkList& L, string filename) {
    //保存图书信息到文件
    ofstream outfile(filename);
    outfile << "北京林业大学图书馆计算机类图书采购列表" << endl;
    outfile << "ISBN	                  书名	                定价" << endl;
    LNode* p = L->next;
    while (p != nullptr) {
        outfile << p->data.no << " " << p->data.name << " " << p->data.price << endl;
        p = p->next;
    }
    outfile.close();
}

void UpdateBook(LinkList& L) {
    //图书信息更新
    LNode* p = L->next;
    while (p != nullptr) {
        if (p->data.price < 45) {
            p->data.price *= 1.2;
        }
        else p->data.price *= 1.1;
        p = p->next;
    }
}