#include <bits/stdc++.h>
#define MAXSIZE 10000
using namespace std;

typedef struct {
    string relation;    //关系名称
    string rule[10];    //规则数组
} Relation;

int BF(string t, string s) {
    // 字符串匹配函数
    int i = 0, j = 0;
    int tLen = t.length();
    int sLen = s.length();

    while (i < tLen && j < sLen) {
        if (t[i] == s[j]) {
            i++;
            j++;
        }
        else {
            i = i - j + 1;
            j = 0;
        }
    }

    if (j >= sLen) {
        return i - sLen;
    }
    else {
        return -1;
    }
}

void findAllMatches(string t, string s, int positions[], int& count) {
    // 查找实体所有匹配位置
    count = 0;
    int pos = 0;

    while (pos < t.length()) {
        int matchPos = BF(t.substr(pos), s);
        if (matchPos == -1) break;

        positions[count++] = pos + matchPos;
        pos = pos + matchPos + 1;
    }
}

bool RelationExtraction(char* text, char* entity1, char* entity2, Relation* r) {
    // 关系抽取函数
    string strText(text);
    string strEntity1(entity1);
    string strEntity2(entity2);

    // 查找两个实体在文本中的所有位置
    int positions1[100], positions2[100];
    int count1 = 0, count2 = 0;

    findAllMatches(strText, strEntity1, positions1, count1);
    findAllMatches(strText, strEntity2, positions2, count2);

    if (count1 == 0 || count2 == 0) {
        return false;
    }

    // 遍历所有实体位置组合，寻找相邻的实体对
    for (int i = 0; i < count1; i++) {
        for (int j = 0; j < count2; j++) {
            int pos1 = positions1[i];
            int pos2 = positions2[j];

            // 确保entity1在entity2之前
            if (pos1 < pos2) {
                // 计算两个实体之间的内容
                int start = pos1 + strEntity1.length();
                int end = pos2;

                if (start <= end) {
                    string between = strText.substr(start, end - start);

                    // 构造模式：A + between + B
                    string pattern = "A" + between + "B";

                    // 与所有规则进行比较
                    for (int k = 0; k < 10 && r[k].relation != ""; k++) {
                        for (int m = 0; m < 10 && r[k].rule[m] != ""; m++) {
                            if (pattern == r[k].rule[m]) {
                                // 输出三元组
                                cout << strEntity1 << "-" << r[k].relation << "-" << strEntity2 << endl;
                                return true;
                            }
                        }
                    }
                }
            }
        }
    }

    return false;
}

void InitRelation(Relation* r) {
    // 关系初始化函数
    // 初始化第一个关系
    r[0].relation = "属于行业大类";
    r[0].rule[0] = "A行业类别为B";
    r[0].rule[1] = "A属于B";
    r[0].rule[2] = "";

    // 初始化第二个关系
    r[1].relation = "所属机构";
    r[1].rule[0] = "A所属机构为B";
    r[1].rule[1] = "A的公司是B";
    r[1].rule[2] = "A隶属B";
    r[1].rule[3] = "";

    // 初始化第三个关系
    r[2].relation = "具有注册地址";
    r[2].rule[0] = "A位于B";
    r[2].rule[1] = "A坐落于B";
    r[2].rule[2] = "A总部在B";
    r[2].rule[3] = "";

    // 初始化第四个关系
    r[3].relation = "主营业务为";
    r[3].rule[0] = "A包括B";
    r[3].rule[1] = "A专注于B";
    r[3].rule[2] = "A主营业务为B";
    r[3].rule[3] = "";

    // 标记结束
    r[4].relation = "";
}

//#include "15-基于规则的关系挖掘.h" 

int main() {
    char entity1[100];
    char entity2[100];
    char text[10000];

    Relation r[10];
    InitRelation(r);

    cin.getline(entity1, 100);

    cin.getline(entity2, 100);

    cin.getline(text, 10000);

    if (!RelationExtraction(text, entity1, entity2, r))
        cout << "实体之间不存在关系" << endl;

    return 0;
}
