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
    L.elem = new Book[255];
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

void SaveFile(SqList& L, string filepath) {
    //保存图书信息到文件
    ofstream outfile(filepath.c_str());
    outfile << "title" << endl;
    outfile << "title" << endl;
    for (int i = 0; i < L.length; i++) {
        outfile << L.elem[i].no << " " << L.elem[i].name << " " << L.elem[i].price << endl;
    }
    outfile.close();
}

bool DeleteBook(SqList& L, int pos) {
    //删除指定图书信息
    //如果删除成功，返回true，否则，返回false
    if (pos < 1 || pos > L.length + 1) return false;
    for (int i = pos - 1; i < L.length; ++i) {
        L.elem[i] = L.elem[i + 1];
    }
    return true;
}