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
    LNode* p = L->next;     //需要一个移动的节点p从头到尾删除每一个结点，从头结点的next，即首元结点开始
    while (p != nullptr) {  //删除完毕时，p会移动至最后一个结点的next，为nullptr 
        LNode* temp = p;    //如直接对p操作，先移动p则无法delete，先delete则无法操作next指针，故使用备份temp
        p = p->next;    //这两步无先后之分
        delete temp;    //这两步无先后之分
    }
    delete L;   //最后释放头结点
    L = nullptr;    //同上
}

void ReadFile(LinkList& L, string filepath) {
    //从文件中读取图书信息，利用尾插法构建链表
    ifstream infile(filepath.c_str());
    string line;
    getline(infile, line);
    getline(infile, line);  //至此跳过两行表头至图书信息正文部分
    LNode* tail = L;    //同删除，需要一个移动的节点，从头到尾创建每一个结点
                        //由于接下来使用的是tail->next，要想从首元结点开始，直接使tail = L（头结点）即可，形象地声明为tail（尾结点）
    Book temp;  //为方便循环条件判断，创建Book类型临时变量temp
    while (infile >> temp.no >> temp.name >> temp.price) {  //当读取完一本书的信息，即进入一次循环进行结点创建
        LNode* newNode = new LNode;     
        newNode->next = nullptr;    //至此创建并初始化了一个空白结点
        newNode->data = temp;   //将进循环时读取的图书信息存入空白结点的data中，完成一本图书的读取
        tail->next = newNode;   //将新结点连接到尾结点后
        tail = newNode;     //新结点更新成为尾结点
    }
    infile.close();
}