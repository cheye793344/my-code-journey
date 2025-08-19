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
    ifstream infile(filepath.c_str());
    //从文件中读取图书信息，将其按顺序存入L.elem指向的数组中
    string line;
    getline(infile, line);
    getline(infile, line);
    while (infile >> L.elem[L.length].no >> L.elem[L.length].name >> L.elem[L.length].price) { L.length++; }
    infile.close();
}

void SaveFile(SqList& L, string filepath) {
    //保存图书信息到文件
    ofstream outfile(filepath.c_str());
    outfile << "北京林业大学图书馆计算机类图书采购列表" << endl;
    outfile << "ISBN	                  书名	                定价" << endl;
    for (int i = 0; i < L.length; i++) {
        outfile << L.elem[i].no << " " << L.elem[i].name << " " << L.elem[i].price << endl;
    }
    outfile.close();
}

void UpdateBook(SqList& L) {
    //图书信息更新
    for (int i = 0; i < L.length + 1; ++i) {
        if (L.elem[i].price < 45) L.elem[i].price *= 1.2;
        else L.elem[i].price *= 1.1;
    }
}