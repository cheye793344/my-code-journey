#include<iostream>
using namespace std;
typedef struct LNode
{
    int data;
    struct LNode* next;
}LNode, * LinkList;
void CreatList(LinkList& p)
{    //µÝ¹é´´½¨Á´±í
    int x;
    cin >> x;
    if (x == 0) {
        p = nullptr;
        return;
    }
    p = new LNode;
    p->data = x;
    CreatList(p->next);
}
