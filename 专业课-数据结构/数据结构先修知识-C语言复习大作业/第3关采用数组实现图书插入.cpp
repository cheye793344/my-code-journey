/*
    通过测试用例的关键点在于，
    原文件有两行无用表头而新文件没有，
    如果调用同样的Readfile函数，均跳过开头两行，
    在先后调用Readfile的情况下，原文件的书籍数量（L.length）为103，
    而newfile里则为L.length + 1（新增插入的一本书） - 2（去掉的两行表头，实际去掉了两本书）= 102，
    新的书本数量不符合逻辑导致插入失败，
    正确解法可以是给Readfile加判定，不要一味跳过两行
    或者在newfile开头加两行文字用于占位。
*/


#include <bits/stdc++.h>
using namespace std;

typedef struct {
    char no[20];                               //书号
    char name[100];                            //书名
    float price;                               //价格
}Book;

typedef struct {
    Book* elem;                                //指向数组的指针
    int length;                                //数组的长度
}SqList;

void InitList(SqList& L) {
    //使用动态内存分配new进行初始化
    L.elem = new Book[1000];                   //分配足够大的空间
    L.length = 0;                              //初始长度为0
}

void FreeList(SqList& L) {
    //释放内存
    delete[] L.elem;                           //释放动态分配的数组
    L.elem = nullptr;                          //指针置空
    L.length = 0;                              //长度置0
}

void ReadFile(SqList& L, string filepath) {
    //从文件中读取图书信息，将其按顺序存入L.elem指向的数组中
    ifstream infile(filepath);
    if (!infile) {
        cerr << "无法打开文件" << endl;
        return;
    }
    string line;
    getline(infile, line);
    getline(infile, line);

    while (infile >> L.elem[L.length].no >> L.elem[L.length].name >> L.elem[L.length].price) {
        L.length++;
        if (L.length >= 1000) break;           //防止超出数组范围
    }
    //cout << "读取到的书的数量：" << L.length << endl;
    infile.close();
}

void SaveFile(SqList& L, string filepath) {
    //保存图书信息到文件
    ofstream outfile(filepath);
    if (!outfile) {
        cerr << "无法创建文件" << endl;
        return;
    }
    outfile << "title" << endl;
    outfile << "title" << endl;
    for (int i = 0; i < L.length; i++) {
        outfile << L.elem[i].no << " " << L.elem[i].name << " " << L.elem[i].price << endl;
    }
    outfile.close();
}

bool InsertBook(SqList& L, int pos, Book* book) {
    //插入图书信息，输入图书的书号、书名和价格，将该图书的基本信息插入到数组中的指定位置
    //如果插入成功，返回true，否则，返回false
    //cout << "临插入前L.length: " << L.length << endl;
    //cout << "临插入前pos: " << pos << endl;
    if (pos < 1) {
        return false;                    //位置不合法
    }

    if (L.length >= 1000) {
        return false;                           //数组已满
    }
    if (pos > L.length + 1) {
        pos = L.length + 1;
    }
    //将pos-1位置及之后的元素后移
    for (int i = L.length; i >= pos; i--) {
        L.elem[i] = L.elem[i - 1];
    }

    //插入新元素
    strcpy(L.elem[pos - 1].no, book->no);
    strcpy(L.elem[pos - 1].name, book->name);
    L.elem[pos - 1].price = book->price;
    L.length++;

    return true;
}