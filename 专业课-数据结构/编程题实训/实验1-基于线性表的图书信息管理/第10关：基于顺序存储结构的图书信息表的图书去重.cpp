#include<iostream>
#include<string.h>
#include<iomanip>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 1000    //图书表可能达到的最大长度
using namespace std;
typedef struct
{//图书信息定义
    char no[20];    //图书ISBN
    char name[50];   //图书名字
    float price;   //图书价格
}Book;
typedef struct
{//图书表的顺序存储结构类型为SqList
    Book* elem;                   //存储空间的基地址
    int length;                   //图书表中当前图书个数
}SqList;

int SearchList(SqList L, char no[20])
{//查找书号是否在图书信息表L中
    if (L.length == 0) return 0;
    for (int i = 0; i < L.length; ++i) {
        if (strcmp(no, L.elem[i].no) == 0) return 1;
    }
    return 0;
}
int DupRemoval_Sq(SqList L1, SqList& L2)
{//图书去重
    for (int i = 0; i < L1.length; i++) {
        if (SearchList(L2, L1.elem[i].no) == 1) continue;
        L2.elem[L2.length] = L1.elem[i];
        L2.length++;
    }
    cout << L2.length << endl;
    for (int i = 0; i < L2.length; i++) {
        cout << L2.elem[i].no << " " << L2.elem[i].name << " " << fixed << setprecision(2) << L2.elem[i].price << endl;
    }
    return OK;
}