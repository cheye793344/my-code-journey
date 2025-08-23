#include<bits/stdc++.h>
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
    //cout << "成功调用了初始化函数！" << endl;
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
    //cout << "成功调用了读取函数！" << endl; 
}

void ReverseBook(LinkList& L) {
    //把图书信息逆序存储 
    LNode* prev = nullptr;
    LNode* curr = L->next;
    LNode* temp = nullptr;
    while (curr != nullptr) {
        temp = curr->next;  //存档
        curr->next = prev;  //转向
        prev = curr;  //移动
        curr = temp;  //移动
    }
    L->next = prev;
    //cout << "成功调用了逆序函数！" << endl;
}

void SaveFile(LinkList& L, string filepath) {
    //把逆序后的数据写入新文件"book-newinverse.txt"中 
    ofstream outfile(filepath.c_str());
    outfile << "北京林业大学图书馆计算机类图书采购列表" << endl;
    outfile << "ISBN	                  书名	                定价" << endl;
    LNode* p = L->next;
    while (p != nullptr) {
        outfile << p->data.no << " " << p->data.name << " " << p->data.price << endl;
        p = p->next;
    }
    outfile.close();
    //cout << "成功调用了保存函数！" << endl;
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
    //cout << "成功调用了析构函数！" << endl; 
}