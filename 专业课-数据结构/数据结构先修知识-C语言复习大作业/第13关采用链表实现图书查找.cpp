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
        LNode* temp;
        temp = p;
        p = p->next;
        delete temp;
    }
    delete L;
    L = nullptr;
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
    infile.close();
}

LinkList SearchBook(LinkList& L, int type) {
    //图书信息查找，返回包含查找图书信息的链表，如果查找失败，返回nullptr
    LinkList resultList = new LNode;
    resultList->next = nullptr;
    LNode* resultTail = resultList;

    if (type == 1) {
        int pos;
        cin >> pos;
        if (pos < 1) return nullptr;
        int currentPos = 1;
        LNode* p = L->next;
        while (p != nullptr && currentPos < pos) {
            p = p->next;
            currentPos++;
        }
        if (p != nullptr) {
            LNode* result = new LNode;
            result->data = p->data;
            resultList->next = result;
            return resultList;
        }
        return nullptr;
    }
    if (type == 2) {
        char name[50];
        cin >> name;
        LNode* p = L->next;
        bool found = false;
        while (p != nullptr) {
            if (strcmp(p->data.name, name) == 0) {
                LNode* result = new LNode;
                result->data = p->data;
                resultTail->next = result;
                resultTail = resultTail->next;
                resultTail->next = nullptr;
                found = true;
            }
            p = p->next;
        }
        return found ? resultList : nullptr;
    }
}