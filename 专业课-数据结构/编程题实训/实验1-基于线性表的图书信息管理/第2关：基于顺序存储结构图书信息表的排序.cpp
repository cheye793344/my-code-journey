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
    char name[60];   //图书名字
    float price;   //图书价格
}Book;
typedef struct
{//图书表的顺序存储结构类型为SqList
    Book* elem;                   //存储空间的基地址
    int length;                   //图书表中当前图书个数
}SqList;

int BubbleSort_Sq(SqList L)
{//图书顺序表按照价格降序冒泡排序
    int lastSwappedIndex = L.length - 1;
    for (int i = 0; i < L.length - 1; ++i) {
        bool swapped = false;
        int currentLast = 0;
        for (int j = 0; j < lastSwappedIndex; ++j) {
            if (L.elem[j].price < L.elem[j + 1].price) {
                Book temp;
                //strcpy(temp.no, L.elem[j + 1].no); 
                //strcpy(temp.name, L.elem[j + 1].name); 
                //temp.price = L.elem[j + 1].price; 
                temp = L.elem[j + 1];
                L.elem[j + 1] = L.elem[j];
                L.elem[j] = temp;
                swapped = true;
                currentLast = j;
            }
        }
        if (!swapped) break;
        lastSwappedIndex = currentLast;
    }
}
