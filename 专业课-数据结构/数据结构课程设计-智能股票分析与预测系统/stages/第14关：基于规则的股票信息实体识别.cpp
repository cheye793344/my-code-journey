#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;

int BF(const char* S, const char* T, int pos) {
    // 基于BF算法将输入的模式串与文本进行匹配
    int i = pos;  // 主串指针
    int j = 0;    // 模式串指针
    int sLen = strlen(S);
    int tLen = strlen(T);

    while (i < sLen && j < tLen) {
        if (S[i] == T[j]) {
            i++;
            j++;
        }
        else {
            i = i - j + 1;  // 主串回溯到下一个位置
            j = 0;          // 模式串回到开头
        }
    }

    if (j >= tLen) {
        return i - tLen;    // 返回匹配的起始位置
    }
    else {
        return -1;          // 匹配失败
    }
}

// 判断是否为UTF-8中文字符的起始字节
bool isChineseStartByte(unsigned char c) {
    return (c & 0xE0) == 0xE0;  // UTF-8中文字符以1110xxxx开头
}

bool EntityRecognition(const char* S, const char* T) {
    // 实体识别函数 
    bool found = false;
    string rule(T);
    string text(S);

    // 计算规则中*的个数（即实体包含的中文字符个数）
    int starCount = 0;
    for (char c : rule) {
        if (c == '*') starCount++;
    }

    if (starCount == 0) {
        // 如果没有*，直接进行普通匹配
        int pos = BF(S, T, 0);
        if (pos != -1) {
            cout << string(T) << endl;
            found = true;
        }
        return found;
    }

    // 解析规则，将规则分割为前缀和后缀部分
    size_t firstStar = rule.find('*');
    size_t lastStar = rule.rfind('*');

    string prefix = rule.substr(0, firstStar);  // *之前的部分
    string suffix = rule.substr(lastStar + 1);  // *之后的部分

    // 计算实体在UTF-8中的字节长度（每个中文字符3字节）
    int entityByteLen = starCount * 3;

    int pos = 0;
    while (pos < text.length()) {
        // 首先匹配前缀
        int prefixPos = BF(text.c_str(), prefix.c_str(), pos);
        if (prefixPos == -1) break;

        // 前缀匹配成功后，计算实体开始位置
        int entityStart = prefixPos + prefix.length();

        // 检查实体部分是否都是中文字符
        bool validEntity = true;
        if (entityStart + entityByteLen <= text.length()) {
            for (int i = 0; i < entityByteLen; i += 3) {
                if (i + 2 >= entityByteLen) {
                    validEntity = false;
                    break;
                }
                if (!isChineseStartByte((unsigned char)text[entityStart + i])) {
                    validEntity = false;
                    break;
                }
            }
        }
        else {
            validEntity = false;
        }

        // 如果实体部分有效，继续匹配后缀
        if (validEntity) {
            int suffixStart = entityStart + entityByteLen;
            if (suffixStart + suffix.length() <= text.length()) {
                // 检查后缀是否匹配
                bool suffixMatch = true;
                for (int i = 0; i < suffix.length(); i++) {
                    if (text[suffixStart + i] != suffix[i]) {
                        suffixMatch = false;
                        break;
                    }
                }

                if (suffixMatch) {
                    // 提取并输出实体
                    string entity = text.substr(entityStart, entityByteLen);
                    cout << entity << endl;
                    found = true;
                }
            }
        }

        pos = prefixPos + 1;
    }

    return found;
}

//#include "14-基于规则的股票实体智能识别.h"

int main() {
    char keyword[100];
    char text[10000];

    // 使用getline来读取包含空格的文本
    cin.getline(keyword, 100);
    cin.getline(text, 10000);

    if (!EntityRecognition(text, keyword))
        cout << "无匹配" << endl;
    return 0;
}

