#include<iostream>
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

int HighestPrice_Sq(SqList L)
{//查找价格最高的图书并输出相应图书的信息
    //自己写的不够优雅
    float highestPrice = 0;
    for (int i = 0; i < L.length; ++i) {
        if (L.elem[i].price >= highestPrice) {
            highestPrice = L.elem[i].price;
        }
    }

    int count = 0;
    for (int i = 0; i < L.length; ++i) {
        if (L.elem[i].price == highestPrice) count++;
    }
    cout << count << endl;
    for (int i = 0; i < L.length; ++i) {
        if (L.elem[i].price == highestPrice) {
            cout << L.elem[i].no << " " << L.elem[i].name << " " << fixed << setprecision(2) << L.elem[i].price << endl;
        }
    }
}

/*
    ai优雅写法

int HighestPrice_Sq(const SqList& L)
{
    if (L.length == 0) return 0;

    const Book* ptrs[MAXSIZE];   // 存指针，空间已足够
    int cnt = 0;                 // 当前已收集的个数
    float maxPrice = L.elem[0].price;

    for (int i = 0; i < L.length; ++i)
    {
        const Book& b = L.elem[i];
        if (b.price > maxPrice)
        {
            maxPrice = b.price;
            cnt = 0;             // 清空旧队列
            ptrs[cnt++] = &b;
        }
        else if (b.price == maxPrice)
        {
            ptrs[cnt++] = &b;
        }
    }

    std::cout << cnt << '\n';
    for (int i = 0; i < cnt; ++i)
        std::cout << ptrs[i]->no << ' ' << ptrs[i]->name << ' '
                  << std::fixed << std::setprecision(2) << ptrs[i]->price << '\n';

    return cnt;
}
*/