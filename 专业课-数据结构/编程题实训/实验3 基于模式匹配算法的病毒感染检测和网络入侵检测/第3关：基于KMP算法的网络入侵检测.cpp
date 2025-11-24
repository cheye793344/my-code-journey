#include "iostream"
#include "cstring"
#include <stdlib.h>
using namespace std;

#define MAXLEN 5000 // 串的最大长度

typedef struct {
    char* ch; // 存储串的一维数组
    int length; // 串的当前长度
} HString;

// 输入规则，提取IP地址
void InputRule(HString ip[], int n)
{
    for (int i = 0; i < n; i++) {
        char line[200];
        cin.getline(line, 200);

        // 提取 ip: 后面的字段
        char* pos = strstr(line, "ip:");
        if (pos) {
            pos += 3; // 跳过"ip:"
            char* space = strchr(pos, ' ');
            int len;
            if (space)
                len = space - pos;
            else
                len = strlen(pos);

            ip[i].ch = (char*)malloc(sizeof(char) * (len + 1));
            strncpy(ip[i].ch, pos, len);
            ip[i].ch[len] = '\0';
            ip[i].length = len;
        }
        else {
            ip[i].ch = (char*)malloc(sizeof(char));
            ip[i].ch[0] = '\0';
            ip[i].length = 0;
        }
    }
}

// 输入日志并合并存放
void InputLog(HString& log, int m)
{
    // 先分配足够大的内存
    log.ch = new char[100000]; // 分配更大的空间
    log.ch[0] = '\0';
    log.length = 0;
    for (int i = 0; i < m; i++) {
        char line[200];
        cin.getline(line, 200);
        strcat(log.ch, line);
        strcat(log.ch, "\n");
    }
    log.length = strlen(log.ch);
}

// 求模式串pattern的next数组
void GetNext(HString pattern, int* next)
{
    int i = 0, j = -1;
    next[0] = -1;
    while (i < pattern.length - 1) {
        if (j == -1 || pattern.ch[i] == pattern.ch[j]) {
            i++;
            j++;
            next[i] = j;
        }
        else {
            j = next[j];
        }
    }
}

// KMP匹配算法
int Index_KMP(HString target, HString pattern, int* next)
{
    GetNext(pattern, next);
    int i = 0, j = 0;
    while (i < target.length && j < pattern.length) {
        if (j == -1 || target.ch[i] == pattern.ch[j]) {
            i++;
            j++;
        }
        else {
            j = next[j];
        }
    }
    if (j >= pattern.length)
        return i - pattern.length;
    else
        return -1;
}

//#include "3-基于KMP算法的网络入侵检测.h"
int main()
{
    int n, m;
    cin >> n >> m;
    getchar();

    HString ip[5000];//ip数组存放n个ip地址 
    InputRule(ip, n);

    HString log;
    log.ch = (char*)malloc(sizeof(char) * 5000);
    strcpy(log.ch, "");
    log.length = 0;
    InputLog(log, m);

    for (int i = 0; i < n; i++)
    {
        int* next = new int[ip[i].length];
        if (Index_KMP(log, ip[i], next) != -1)
        {
            cout << "Intrusion." << endl;
            return 0;
        }
    }
    cout << "No Intrusion." << endl;
    return 0;

}