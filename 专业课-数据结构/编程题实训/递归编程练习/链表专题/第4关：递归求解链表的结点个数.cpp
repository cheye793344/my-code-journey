#include<iostream>
using namespace std;
typedef struct LNode
{
    int data;
    struct LNode* next;
}LNode, * LinkList;
int GetLength(LinkList p)
{	//递归求解链表的结点个数
    if (p == nullptr) return 0;
    return 1 + GetLength(p->next);
}
