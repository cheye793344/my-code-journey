#include<iostream>
#include<iomanip>
#define OK 1
#define ERROR 0
#define OVERFLOW -2
#define MAXSIZE 1000                                  //图书表可能达到的最大长度
using namespace std;
typedef struct
{//图书信息定义
    char no[20];                                        //图书ISBN
    char name[60];                                     //图书名字
    float price;                                       //图书价格
}Book;
typedef struct
{//图书表的顺序存储结构类型为SqList
    Book* elem;                                         //存储空间的基地址
    int length;                                        //图书表中当前图书个数
}SqList;

int Input_Sq(SqList& L)
{//顺序表的输入
    cin >> L.length;
    for (int i = L.length - 1; i >= 0; --i) {
        cin >> L.elem[i].no >> L.elem[i].name >> L.elem[i].price;
    }
}
