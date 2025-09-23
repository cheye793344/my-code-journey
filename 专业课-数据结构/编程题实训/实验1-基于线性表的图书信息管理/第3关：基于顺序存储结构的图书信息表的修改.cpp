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

int RevisePrice_Sq(SqList& L)
{//修改价格
    float sum = 0;
    float avePrice = 0;
    for (int i = 0; i < L.length; ++i) {
        sum += L.elem[i].price;
    }
    avePrice = sum / L.length;
    cout << fixed << setprecision(2) << avePrice << endl;
    for (int i = 0; i < L.length; ++i) {
        if (L.elem[i].price < avePrice) L.elem[i].price *= 1.20;
        else L.elem[i].price *= 1.10;
    }
    return 1;
}
