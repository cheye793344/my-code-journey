#include<iostream>
using namespace std;
typedef struct LNode
{
    int data;
    struct LNode* next;
}LNode, * LinkList;
double GetAverage(LinkList p, int n)
{
    //递归求解链表中所有整数的平均值，n表示链表的结点个数
    if (n == 0) return 0.0; 
    if (n == 1) return p->data; 
    double sum = p->data + GetAverage(p->next, n - 1) * (n - 1);
    return sum / n; 
}
