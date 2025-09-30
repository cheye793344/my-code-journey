#include<iostream>
using namespace std;
typedef struct LNode
{
    int data;
    struct LNode* next;
}LNode, * LinkList;
void Output(LinkList p)
{    //递归从前向后输出链表
    if (p == nullptr) return;
    if (p->next == nullptr) {
        cout << p->data;
    }
    else cout << p->data << " ";
    Output(p->next);
}
