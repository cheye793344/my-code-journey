#include <bits/stdc++.h>
using namespace std;

typedef struct {
    char no[20];    // 书号
    char name[100]; // 书名
    float price;    // 价格
} Book;

typedef struct {
    Book* elem;     // 指向数组的指针
    int length;     // 数组的长度
} SqList;

void InitList(SqList& L) {
    // 初始化顺序表
    L.elem = new Book[100]; // 假设最多存储100本书
    L.length = 0;
}

void FreeList(SqList& L) {
    // 释放动态分配的内存
    delete[] L.elem;
    L.length = 0;
}

void ReadFile(SqList& L, string filepath) {
    ifstream infile(filepath.c_str());
    if (!infile) {
        cerr << "无法打开文件: " << filepath << endl;
        return;
    }

    string line;
    // 读取前两行标题信息
    for (int i = 0; i < 2; i++) {
        getline(infile, line);
    }

    // 读取图书信息
    while (infile >> L.elem[L.length].no >> L.elem[L.length].name >> L.elem[L.length].price) {
        L.length++;
    }
    infile.close();
}