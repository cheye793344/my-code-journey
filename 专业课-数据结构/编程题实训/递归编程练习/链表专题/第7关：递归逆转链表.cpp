#include<iostream>
using namespace std;
typedef struct LNode
{
    int data;
    struct LNode* next;
}LNode, * LinkList;
LinkList Reverse(LinkList p)
{
    //µÝ¹éÄæ×ªÁ´±í
    if (p == nullptr || p->next == nullptr) return p;
    LinkList newHead = Reverse(p->next);
    p->next->next = p;
    p->next = nullptr;
    return newHead;
}
