#include<bits/stdc++.h>
using namespace std;

typedef struct {
    char no[20];					//书号 
    char name[100];					//书名 
    float price;					//价格 
}Book;

typedef struct LNode {
    Book data;                      //图书信息
    struct LNode* next;             //指向下一结点
}LNode, * LinkList;

void InitList(LinkList& L) {
    //使用动态内存分配new进行初始化 
    L = new LNode;
    L->next = nullptr;
}

void ReadFile(LinkList& L, string filepath) {
    //从文件中读取图书信息，利用尾插法构建链表
    ifstream infile(filepath.c_str());
    string line;
    getline(infile, line);
    getline(infile, line);
    Book temp;
    LNode* tail = L;
    while (infile >> temp.no >> temp.name >> temp.price) {
        LNode* newNode = new LNode;
        newNode->next = nullptr;
        newNode->data = temp;
        tail->next = newNode;
        tail = newNode;
    }
    infile.close();
}

int CountBook(LinkList& L) {
    //求链表L的长度	
    int count = 0;
    LNode* p = L->next;
    while (p != nullptr) {
        p = p->next;
        count++;
    }
    return count;
}

void PriceSort(LinkList& L) {
    //按图书价格升序排序，采用冒泡排序
    bool swapped;
    LNode* end = nullptr;  // 每次排序的结束位置

    do {
        swapped = false;
        LNode* current = L->next;
        LNode* prev = L; 

        while (current->next != end) {
            if (current->data.price > current->next->data.price) {
                // 交换数据域
                Book temp = current->data;
                current->data = current->next->data;
                current->next->data = temp;
                swapped = true;
            }
            prev = current; 
            current = current->next;
        }
        end = current;  // 更新结束位置

    } while (swapped);
}

void SaveFile(LinkList& L, string filepath) {
    //排序后的数据写入新文件"book-newsort.txt"中
    ofstream outfile(filepath.c_str());
    outfile << "北京林业大学图书馆计算机类图书采购列表" << endl;
    outfile << "ISBN	                  书名	                定价" << endl;
    LNode* p = L->next;
    while (p != nullptr) {
        outfile << p->data.no << " " << p->data.name << " " << p->data.price << endl;
        p = p->next;
    }
    outfile.close();
}

void FreeList(LinkList& L) {
    //释放内存
    LNode* p = new LNode;
    p = L->next;
    while (p != nullptr) {
        LNode* temp = p;
        p = p->next;
        delete temp;
    }
    delete L;
    L->next = nullptr;
}