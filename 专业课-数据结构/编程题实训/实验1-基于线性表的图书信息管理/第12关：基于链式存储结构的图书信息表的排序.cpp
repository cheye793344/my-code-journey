#include<iostream>
#include<string.h>
#include<iomanip>
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

int Sort_L(LinkList& L)
{//将图书按照价格降序排序
    if (L == NULL || L->next == NULL) return ERROR;

    int swapped;
    LNode* ptr1;
    LNode* lptr = NULL;

    do {
        ptr1 = L->next;
        swapped = 0;
        while (ptr1->next != lptr) {
            if (ptr1->data.price < ptr1->next->data.price) {
                Book temp = ptr1->data;
                ptr1->data = ptr1->next->data;
                ptr1->next->data = temp;
                swapped = 1;
            }
            ptr1 = ptr1->next;
        }
        lptr = ptr1;
    } while (swapped);

    return OK;
}