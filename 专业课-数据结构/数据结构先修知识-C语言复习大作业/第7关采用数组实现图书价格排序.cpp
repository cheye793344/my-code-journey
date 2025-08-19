#include<bits/stdc++.h>			 
using namespace std;

typedef struct {
    char no[20];					//书号 
    char name[100];					//书名 
    float price;					//价格 
}Book;

typedef struct {
    Book* elem;						//指向数组的指针  
    int length;						//数组的长度 
}SqList;

void InitList(SqList& L) {
    //使用动态内存分配new进行初始化 
    L.elem = new Book[255];
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

void PriceSort(SqList& L) {
    //按图书价格升序排序，采用冒泡排序 
    for (int i = 0; i < L.length - 1; ++i) {
        bool is_swapped = false;
        for (int j = 0; j < L.length - 1 - i; ++j) {
            if (L.elem[j].price > L.elem[j + 1].price) {
                Book temp = L.elem[j];
                L.elem[j] = L.elem[j + 1];
                L.elem[j + 1] = temp;
                is_swapped = true;
            }
        }
        if (!is_swapped) break;
    }
}

void SaveFile(SqList& L, string filepath) {
    //把排序后的数据写入新文件"book-newsort.txt"中 
    ofstream outfile(filepath.c_str());
    outfile << "北京林业大学图书馆计算机类图书采购列表" << endl;
    outfile << "ISBN	                  书名	                定价" << endl;
    for (int i = 0; i < L.length; i++) {
        outfile << L.elem[i].no << " " << L.elem[i].name << " " << L.elem[i].price << endl;
    }
    outfile.close();
}

void FreeList(SqList& L) {
    //释放内存
    delete[] L.elem;
    L.elem = nullptr;
    L.length = 0;
}