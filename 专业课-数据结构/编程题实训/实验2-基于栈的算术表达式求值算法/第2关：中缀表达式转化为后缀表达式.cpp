#include<iostream>
using namespace std;
#define  MAXSIZE  100
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
typedef struct
{
    char* base;
    char* top;
    int stacksize;
}SqStack;
Status InitStack(SqStack& S)
{//初始化栈
    S.base = new char[MAXSIZE];
    if (!S.base) return ERROR;
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}
Status Push(SqStack& S, char e)
{//入栈
    if (S.top - S.base == S.stacksize) return ERROR;
    *S.top++ = e;
    return OK;
}
Status Pop(SqStack& S)
{//出栈
    if (S.top == S.base) return ERROR;
    S.top--;
    return OK;
}
char GetTop(SqStack S)
{//取栈顶元素
    if (S.top == S.base) return ERROR;
    return *(S.top - 1);
}
char Precede(char a, char b)
{//比较运算符a和b的优先级
    if (a == '+' || a == '-') {
        if (b == '+' || b == '-' || b == ')' || b == '=') return '>';
        else return '<';
    }
    else if (a == '*' || a == '/') {
        if (b == '(') return '<';
        else return '>';
    }
    else if (a == '(') {
        if (b == ')') return '=';
        else return '<';
    }
    else if (a == ')') {
        return '>';
    }
    else if (a == '=') {
        if (b == '=') return '=';
        else return '<';
    }
}
void InfixToSuffix(SqStack OPTR, char s[])
{//将中缀表达式转化为后缀表达式并输出 
    InitStack(OPTR);
    Push(OPTR, '=');

    int i = 0;
    char ch = s[i];
    while (ch != '=' || GetTop(OPTR) != '=') {
        if (ch >= '0' && ch <= '9') {
            cout << ch;
            ch = s[++i];
        }
        else {
            char op;
            switch (Precede(GetTop(OPTR), ch)) {
            case '>':
                op = GetTop(OPTR);
                Pop(OPTR);
                cout << op;
                break;

            case '<':
                Push(OPTR, ch);
                ch = s[++i];
                break;

            case '=':
                Pop(OPTR);
                ch = s[++i];
                break;
            }
        }
    }
    while (GetTop(OPTR) != '=') {
        cout << GetTop(OPTR);
        Pop(OPTR);
    }
    if (GetTop(OPTR) == '=') cout << endl;
}
