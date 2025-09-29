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

int FindFavorite_Sq(SqList L)
{//最爱图书的查找并输出数据
    int m;
    cin >> m;
    for (int i = 0; i < m; ++i) {
        char name[50];
        cin >> name;
        Book results[MAXSIZE];
        int count = 0;
        for (int j = 0; j < L.length - 1; j++) {
            if (strcmp(L.elem[j].name, name) == 0) {
                results[count++] = L.elem[j];
            }
        }
        if (count == 0) {
            cout << "Sorry，there is no your favourite!" << endl;
            continue;
        }
        cout << count << endl;
        for (int i = 0; i < count; ++i) {
            cout << results[i].no << " " << results[i].name << " "
                << fixed << setprecision(2) << results[i].price << endl;
        }
    }
}