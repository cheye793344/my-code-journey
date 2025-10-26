#include<iostream>
#include<iomanip>
#include<string.h>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
using namespace std;
typedef struct
{//图书信息定义
    char no[20];    //图书ISBN
    char name[50];   //图书名字
    float price;   //图书价格
}Book;
typedef struct LNode
{//图书信息表的链式存储结构
    Book data;    	   //结点的数据域
    int length;       //链表的表长，即图书表中图书个数
    struct LNode* next; //指针域
}LNode, * LinkList;
int Input_L(LinkList& L)
{//读入数据并用后插法创建链表
    int n; cin >> n;
    LNode* tail = L;
    for (int i = 0; i < n; i++) {
        LNode* p = new LNode;
        p->next = NULL;
        cin >> p->data.no >> p->data.name >> p->data.price;
        tail->next = p;
        tail = p;
        L->length++;
    }
    return OK;
}
void Reverse_L(LinkList& L)
{//逆置带头结点的单链表L
    if (L == NULL || L->next == NULL || L->next->next == NULL) return;
    LNode* p = L->next;
    LNode* q = NULL;
    L->next = NULL;
    while (p != NULL) {
        q = p->next;
        p->next = L->next;
        L->next = p;
        p = q;
    }
}