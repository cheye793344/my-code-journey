#include<iostream>
using namespace std;
typedef struct LNode
{
    int data;
    struct LNode* next;
}LNode, * LinkList;
int GetMax(LinkList p)
{    //递归求解最大值
    if (p->next == nullptr) return p->data;
    int maxNum = GetMax(p->next); 
    return (maxNum > p->data) ? maxNum : p->data; 
}
