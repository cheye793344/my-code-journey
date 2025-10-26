#include<iostream>
#include<iomanip>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
using namespace std;
typedef struct
{//图书信息定义
    char no[20];     //图书ISBN
    char name[50];   //图书名字
    float price;     //图书价格
}Book;
typedef struct LNode
{//图书信息表的链式存储结构
    Book data;    	   //结点的数据域
    int length;       //链表的表长，即图书表中图书个数
    struct LNode* next; //指针域
}LNode, * LinkList;
int HighestPrice_L(LinkList L)
{//查找价格最高的图书
    const Book* ptrs[128];
    int cnt = 0;
    float maxPrice = L->next->data.price;
    LNode* p = L->next;
    while (p != NULL) {
        const Book& b = p->data;
        if (b.price > maxPrice) {
            maxPrice = b.price;
            cnt = 0;
            ptrs[cnt++] = &p->data;
        }
        else if (b.price == maxPrice) {
            ptrs[cnt++] = &p->data;
        }
        p = p->next;
    }
    cout << cnt << endl;
    for (int i = 0; i < cnt; i++) {
        cout << ptrs[i]->no << " " << ptrs[i]->name << " " << fixed << setprecision(2) << ptrs[i]->price << endl;
    }
}