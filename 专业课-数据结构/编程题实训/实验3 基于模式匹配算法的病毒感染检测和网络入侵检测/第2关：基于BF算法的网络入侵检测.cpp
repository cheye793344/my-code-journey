#include "iostream"
#include "cstring"
#include<stdlib.h>
using namespace std;


#define MAXLEN 10000			//串的最大长度
typedef struct {
    char* ch;			//存储串的一维数组
    int length;				//串的当前长度   
}HString;


void InputRule(HString ip[], int n)
{
    for (int i = 0; i < n; i++) {
        char line[1000];
        cin.getline(line, 1000);

        // 查找"ip:"的位置
        char* ip_start = strstr(line, "ip:");
        if (ip_start != NULL) {
            ip_start += 3; // 跳过"ip:"

            // 查找IP地址的结束位置（空格或行尾）
            char* ip_end = ip_start;
            while (*ip_end != ' ' && *ip_end != '\0') {
                ip_end++;
            }

            // 计算IP地址长度并存储
            int ip_length = ip_end - ip_start;
            ip[i].ch = new char[ip_length + 1];
            strncpy(ip[i].ch, ip_start, ip_length);
            ip[i].ch[ip_length] = '\0';
            ip[i].length = ip_length;
        }
    }
}

void InputLog(HString& log, int m)
{
    // 先分配足够大的内存
    log.ch = new char[100000]; // 分配更大的空间
    log.ch[0] = '\0';
    log.length = 0;

    for (int i = 0; i < m; i++) {
        char line[1000];
        cin.getline(line, 1000);

        // 直接将新行追加到log中
        strcat(log.ch, line);
        strcat(log.ch, " "); // 添加分隔符

        // 更新长度
        log.length = strlen(log.ch);
    }
}

int Index_BF(HString S, HString T)
{
    if (T.length == 0 || T.ch == NULL) return -1;

    for (int i = 0; i <= S.length - T.length; i++) {
        int j = 0;
        while (j < T.length && S.ch[i + j] == T.ch[j]) {
            j++;
        }
        if (j == T.length) {
            return i; // 找到匹配
        }
    }
    return -1; // 未找到
}

//#include "2-基于BF算法的网络入侵检测.h"
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
        if (Index_BF(log, ip[i]) != -1)
        {
            cout << "Intrusion." << endl;
            return 0;
        }
    }
    cout << "No Intrusion." << endl;
    return 0;

}