#include <bits/stdc++.h>
using namespace std;

typedef struct {
    char no[20];   								//书号
    char name[100]; 							//书名
    float price;   								//价格
}Book;

typedef struct {
    Book* elem; 								//指向数组的指针
    int length; 								//数组的长度
}SqList;

void InitList(SqList& L) {
    //使用动态内存分配new进行初始化
    L.elem = new Book[1000];
    L.length = 0;
}

void FreeList(SqList& L) {
    //释放内存
    delete[] L.elem;
    L.elem = nullptr;
    L.length = 0;
}

void ReadFile(SqList& L, string filepath) {
    //从文件中读取图书信息，将其按顺序存入L.elem指向的数组中
    ifstream infile(filepath.c_str());
    string line;
    getline(infile, line);
    getline(infile, line);
    while (infile >> L.elem[L.length].no >> L.elem[L.length].name >> L.elem[L.length].price) { L.length++; }
    infile.close();
}

SqList SearchBook(SqList& L, int type) {
    //图书信息查找，返回包含查找图书信息的数组和数组的长度，如果不存在，则令长度为0
    SqList result;
    InitList(result);

    if (type == 1) {
        int pos;
        cin >> pos;
        if (pos >= 1 && pos <= L.length + 1) {
            strcpy(result.elem[result.length].no, L.elem[pos - 1].no);
            strcpy(result.elem[result.length].name, L.elem[pos - 1].name);
            result.elem[result.length].price = L.elem[pos - 1].price;
            result.length++;
        }
    }
    if (type == 2) {
        char name[50];
        cin >> name;
        for (int i = 0; i < L.length + 1; ++i) {
            if (strcmp(L.elem[i].name, name) == 0) {
                strcpy(result.elem[result.length].no, L.elem[i].no);
                strcpy(result.elem[result.length].name, L.elem[i].name);
                result.elem[result.length].price = L.elem[i].price;
                result.length++;
            }
        }
    }
    return result;
}