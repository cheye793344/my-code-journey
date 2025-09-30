#include<iostream>
using namespace std;
typedef struct LNode
{
    int data;
    struct LNode* next;
}LNode, * LinkList;
int GetSum(LinkList p)
{
    //递归求解链表中所有整数的和
    if (p == nullptr) return 0;
    return p->data + GetSum(p->next);
}
