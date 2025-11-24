#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define MAX_TERMS 12
#define MAX_TEXT_LENGTH 20000
#define MAX_CODE_LENGTH 100

// 哈夫曼树节点结构（参考PPT中的结构）
typedef struct {
    char word[50];          // 生态术语
    int weight;             // 权值（出现频次）
    int parent, lch, rch;   // 双亲、左右孩子指针
    char code[MAX_CODE_LENGTH]; // 哈夫曼编码
} HTNode, * HuffmanTree;

// 全局变量
HuffmanTree HT; // 哈夫曼树
int m;          // 哈夫曼树节点总数

// 预定义的生态术语
const char* ecological_terms[MAX_TERMS] = {
    "biodiversity", "ecosystems", "conservation", "animals",
    "species", "forests", "habitats", "pollution",
    "climate", "change", "energy", "renewable"
};

// 函数声明
void initializeTerms(HuffmanTree terms[]);
int findTermIndex(const char* word, HuffmanTree terms[]);
void countFrequencies(const char* text, HuffmanTree terms[]);
void buildHuffmanTree(int n, HuffmanTree terms[]);
void selectTwoMin(int range, int* s1, int* s2);
void generateHuffmanCodes(int n);
void sortTermsByFrequency(HuffmanTree terms[]);
double calculateCompressionRatio(const char* text, HuffmanTree terms[]);
void compressText(const char* text, char* compressed, HuffmanTree terms[]);
void decompressText(const char* compressed, char* decompressed);

// 初始化术语数组
void initializeTerms(HuffmanTree terms[]) {
    for (int i = 0; i < MAX_TERMS; i++) {
        terms[i] = (HTNode*)malloc(sizeof(HTNode));
        strcpy(terms[i]->word, ecological_terms[i]);
        terms[i]->weight = 0;
        terms[i]->parent = terms[i]->lch = terms[i]->rch = 0;
        terms[i]->code[0] = '\0';
    }
}

// 查找术语索引
int findTermIndex(const char* word, HuffmanTree terms[]) {
    char lowerWord[50];
    strcpy(lowerWord, word);
    for (int i = 0; lowerWord[i]; i++) {
        lowerWord[i] = tolower(lowerWord[i]);
    }

    for (int i = 0; i < MAX_TERMS; i++) {
        if (strcmp(lowerWord, terms[i]->word) == 0) {
            return i;
        }
    }
    return -1;
}

// 统计频次
void countFrequencies(const char* text, HuffmanTree terms[]) {
    char* textCopy = strdup(text);
    char* token = strtok(textCopy, " ");

    while (token != NULL) {
        int index = findTermIndex(token, terms);
        if (index != -1) {
            terms[index]->weight++;
        }
        token = strtok(NULL, " ");
    }

    free(textCopy);
}

// 选择两个权值最小且parent为0的节点
void selectTwoMin(int range, int* s1, int* s2) {
    int min1 = 1e9, min2 = 1e9;
    *s1 = *s2 = -1;
    for (int i = 1; i <= range; i++) {
        if (HT[i].parent == 0 && HT[i].weight < min1) {
            min2 = min1; *s2 = *s1;
            min1 = HT[i].weight; *s1 = i;
        }
        else if (HT[i].parent == 0 && HT[i].weight < min2) {
            min2 = HT[i].weight; *s2 = i;
        }
    }
}


// 构建哈夫曼树
void buildHuffmanTree(int n, HuffmanTree terms[]) {
    if (n <= 1) return;
    m = 2 * n - 1;
    HT = (HTNode*)malloc((m + 1) * sizeof(HTNode));

    // 初始化前 n 个结点
    for (int i = 1; i <= n; i++) {
        strcpy(HT[i].word, terms[i - 1]->word);
        HT[i].weight = terms[i - 1]->weight;
        HT[i].parent = HT[i].lch = HT[i].rch = 0;
        HT[i].code[0] = '\0';
    }
    for (int i = n + 1; i <= m; i++) {
        HT[i].weight = 0;
        HT[i].parent = HT[i].lch = HT[i].rch = 0;
    }

    // 构造哈夫曼树
    for (int i = n + 1; i <= m; i++) {
        int s1, s2;
        selectTwoMin(i - 1, &s1, &s2);
        HT[s1].parent = HT[s2].parent = i;
        HT[i].lch = s1; HT[i].rch = s2;
        HT[i].weight = HT[s1].weight + HT[s2].weight;
    }
}

// 生成哈夫曼编码
void generateHuffmanCodes(int n) {
    char cd[MAX_CODE_LENGTH];
    int start, c, f;
    cd[n - 1] = '\0';
    for (int i = 1; i <= n; i++) {
        start = n - 1;
        c = i; f = HT[i].parent;
        while (f != 0) {
            if (HT[f].lch == c) cd[--start] = '0';
            else cd[--start] = '1';
            c = f; f = HT[f].parent;
        }
        strcpy(HT[i].code, &cd[start]);
    }
}

// 按频次排序术语
void sortTermsByFrequency(HuffmanTree terms[]) {
    for (int i = 0; i < MAX_TERMS - 1; i++) {
        for (int j = 0; j < MAX_TERMS - i - 1; j++) {
            if (terms[j]->weight < terms[j + 1]->weight) {
                HTNode* temp = terms[j];
                terms[j] = terms[j + 1];
                terms[j + 1] = temp;
            }
        }
    }
}

// 计算压缩率
double calculateCompressionRatio(const char* text, HuffmanTree terms[]) {
    int original_bits = strlen(text) * 8; // 原始大小按字节算
    int compressed_bits = 0;
    for (int i = 0; i < MAX_TERMS; i++) {
        compressed_bits += terms[i]->weight * strlen(terms[i]->code);
    }
    if (original_bits == 0) return 0;
    return 100.0 * (1.0 - (double)compressed_bits / original_bits);
}

// 压缩文本
void compressText(const char* text, char* compressed, HuffmanTree terms[]) {
    compressed
        [0] = '\0';
    char* textCopy = strdup(text);
    char* token = strtok(textCopy, " ");
    while (token != NULL) {
        int index = findTermIndex(token, terms);
        if (index != -1) strcat(compressed, terms[index]->code);
        token
            = strtok(NULL, " ");
    }
    free(textCopy);
}


// 解压文本
void decompressText(const char* compressed, char* decompressed) {
    decompressed[0] = '\0';
    int n = MAX_TERMS;
    int root = m;
    int p = root;
    for (int i = 0; compressed[i] != '\0'; i++) {
        if (compressed[i] == '0') p = HT[p].lch;
        else p = HT[p].rch;
        if (HT[p].lch == 0 && HT[p].rch == 0) {
            strcat(decompressed, HT[p].word);
            strcat(decompressed, " ");
            p = root;
        }
    }
    // 去掉末尾空格
    int len = strlen(decompressed);
    if (len > 0 && decompressed[len - 1] == ' ') decompressed[len - 1] = '\0';
}
//#include "1-基于哈夫曼树的生态科普文本压缩和解压.h"

// 主函数
int main() {
    char text[MAX_TEXT_LENGTH];
    char compressed[MAX_TEXT_LENGTH * 10];
    char decompressed[MAX_TEXT_LENGTH];

    HuffmanTree terms[MAX_TERMS];

    // 读取输入文本
    if (fgets(text, sizeof(text), stdin) == NULL) {
        return 1;
    }

    // 移除换行符
    text[strcspn(text, "\n")] = 0;

    // 初始化术语
    initializeTerms(terms);

    // 统计频次
    countFrequencies(text, terms);

    // 构建哈夫曼树
    buildHuffmanTree(MAX_TERMS, terms);

    // 生成编码
    generateHuffmanCodes(MAX_TERMS);

    // 将编码复制回terms数组
    for (int i = 0; i < MAX_TERMS; i++) {
        strcpy(terms[i]->code, HT[i + 1].code);
    }

    // 按频次排序
    sortTermsByFrequency(terms);

    // 输出术语频次和编码
    for (int i = 0; i < MAX_TERMS; i++) {
        printf("%s:%d %s\n", terms[i]->word, terms[i]->weight, terms[i]->code);
    }

    // 计算并输出压缩率
    double ratio = calculateCompressionRatio(text, terms);
    printf("%.2f%%\n", 100 - ratio);

    // 压缩并输出压缩文本
    compressText(text, compressed, terms);
    printf("%s\n", compressed);

    // 解压并输出解压文本
    decompressText(compressed, decompressed);
    printf("%s\n", decompressed);

    // 释放内存
    free(HT);
    for (int i = 0; i < MAX_TERMS; i++) {
        free(terms[i]);
    }

    return 0;
}
