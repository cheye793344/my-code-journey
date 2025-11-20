#include "StockSearch.h"
#include "MenuSystem.h"
#include <iostream>
#include <string>
#include<limits>
using namespace std;

typedef struct {
    string relation;
    string rule[10];
} Relation;

// 复用第15关的BF算法
int BF(string t, string s) {
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
    count = 0;
    int pos = 0;

    while (pos < t.length()) {
        int matchPos = BF(t.substr(pos), s);
        if (matchPos == -1) break;

        positions[count++] = pos + matchPos;
        pos = pos + matchPos + 1;
    }
}

void InitRelation(Relation* r) {
    r[0].relation = "属于行业大类";
    r[0].rule[0] = "A行业类别为B";
    r[0].rule[1] = "A属于B";
    r[0].rule[2] = "";

    r[1].relation = "所属机构";
    r[1].rule[0] = "A所属机构为B";
    r[1].rule[1] = "A的公司是B";
    r[1].rule[2] = "A隶属B";
    r[1].rule[3] = "";

    r[2].relation = "具有注册地址";
    r[2].rule[0] = "A位于B";
    r[2].rule[1] = "A坐落于B";
    r[2].rule[2] = "A总部在B";
    r[2].rule[3] = "";

    r[3].relation = "主营业务为";
    r[3].rule[0] = "A包括B";
    r[3].rule[1] = "A专注于B";
    r[3].rule[2] = "A主营业务为B";
    r[3].rule[3] = "";

    r[4].relation = "";
}

bool RelationExtraction(char* text, char* entity1, char* entity2, Relation* r) {
    string strText(text);
    string strEntity1(entity1);
    string strEntity2(entity2);

    int positions1[100], positions2[100];
    int count1 = 0, count2 = 0;

    findAllMatches(strText, strEntity1, positions1, count1);
    findAllMatches(strText, strEntity2, positions2, count2);

    if (count1 == 0 || count2 == 0) {
        return false;
    }

    for (int i = 0; i < count1; i++) {
        for (int j = 0; j < count2; j++) {
            int pos1 = positions1[i];
            int pos2 = positions2[j];

            if (pos1 < pos2) {
                int start = pos1 + strEntity1.length();
                int end = pos2;

                if (start <= end) {
                    string between = strText.substr(start, end - start);
                    string pattern = "A" + between + "B";

                    for (int k = 0; k < 10 && r[k].relation != ""; k++) {
                        for (int m = 0; m < 10 && r[k].rule[m] != ""; m++) {
                            if (pattern == r[k].rule[m]) {
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

namespace StockFunctions {
    void relationExtraction() {
        MenuSystem menu;
        system("cls");
        cout << "==========================================" << endl;
        cout << "   基于规则的股票信息关系抽取" << endl;
        cout << "==========================================" << endl;

        char entity1[100];
        char entity2[100];
        char text[10000];

        Relation r[10];
        InitRelation(r);

        cout << "请输入第一个实体: ";
        cin.ignore();
        cin.getline(entity1, 100);

        cout << "请输入第二个实体: ";
        cin.getline(entity2, 100);

        cout << "请输入待分析的文本: ";
        cin.getline(text, 10000);

        cout << endl << "抽取的关系：" << endl;
        cout << "------------------------------------------" << endl;

        if (!RelationExtraction(text, entity1, entity2, r)) {
            cout << "实体之间不存在关系" << endl;
        }

        menu.showMessage("");
    }
}