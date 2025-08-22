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
        newNode->next = nullptr;
        newNode->data = temp;
        tail->next = newNode;
        tail = newNode;
    }
    infile.close();
}

void SaveFile(LinkList& L, string filepath) {
    //保存图书信息到文件
    ofstream outfile(filepath.c_str());
    outfile << "北京林业大学图书馆计算机类图书采购列表" << endl;
    outfile << "ISBN	                  书名	                定价" << endl;
    LNode* p = L->next;
    while (p != nullptr) {
        outfile << p->data.no << " " << p->data.name << " " << p->data.price << endl;
        p = p->next;
    }
    outfile.close();
}

bool InsertBook(LinkList& L, int pos, Book* book) {
    //插入图书信息，输入图书的书号、书名和价格，将该图书的基本信息插入到链表中的指定位置
    //如果插入成功，返回true，否则，返回false
    LNode* newNode = new LNode;
    newNode->data = *book;
    newNode->next = nullptr;

    if (pos < 1) return false;


    if (pos == 1) {
        LNode* temp;
        temp = L->next;
        L->next = newNode;
        newNode->next = temp;
        return true;
    }


    int currentPos = 0;
    LNode* prev = L;
    while (currentPos < pos - 1) {
        prev = prev->next;
        currentPos++;
    }
    newNode->next = prev->next;
    prev->next = newNode;
    return true;

}