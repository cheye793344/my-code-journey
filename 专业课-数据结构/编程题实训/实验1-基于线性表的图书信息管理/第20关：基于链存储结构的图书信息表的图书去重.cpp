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
int DupRemoval_L(LinkList& L)
{//图书去重
    LNode* current = L->next;
    int removedCount = 0;
    while (current != NULL && current->next != NULL) {
        LNode* prev = current;
        LNode* runner = current->next;
        while (runner != NULL) {
            if (strcmp(current->data.no, runner->data.no) == 0) {
                prev->next = runner->next;
                delete runner;
                runner = prev->next;
                removedCount++;
                L->length--;
            }
            else {
                prev = runner;
                runner = runner->next;
            }
        }
        current = current->next;
    }
    return OK;
}