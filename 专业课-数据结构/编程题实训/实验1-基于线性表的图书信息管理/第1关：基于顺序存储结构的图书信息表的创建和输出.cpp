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
int InitList_Sq(SqList& L)
{//构造一个空的顺序表L
    L.elem = new Book[MAXSIZE];
    if (!L.elem) return -2;
    L.length = 0;
    return 1;
}
int Input_Sq(SqList& L)
{//顺序表的输入
    char no[16], name[64];
    float price;
    while (cin >> no >> name >> price) {
        if (strcmp(no, "0") == 0 && strcmp(name, "0") == 0 && price == 0) break;
        if (L.length >= MAXSIZE) break;
        strcpy(L.elem[L.length].no, no);
        strcpy(L.elem[L.length].name, name);
        L.elem[L.length].price = price;
        L.length++;
    }
    return 1;
}
int Output_Sq(SqList L)
{//顺序表的输出
    cout << L.length << endl;
    for (int i = 0; i < L.length; ++i) {
        cout << L.elem[i].no << " " << L.elem[i].name << " " << fixed << setprecision(2) << L.elem[i].price << endl;
    }
    return 1;
}