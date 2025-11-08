#include <iostream>
#include<iomanip>
#include <string>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef int Status;
using namespace std;
typedef struct
{//操作数栈
    double* base;
    double* top;
    int  stacksize;
}SqStack;
Status InitStack(SqStack& S) {
    //操作数栈初始化
    S.base = new double[MAXSIZE];
    if (!S.base) return OVERFLOW;
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}
Status Push(SqStack& S, double e) {//操作数栈入栈
    if (S.top - S.base == S.stacksize) return ERROR;
    *S.top++ = e;
    return OK;
}
Status Pop(SqStack& S) {//操作数栈出栈
    if (S.top == S.base) return ERROR;
    S.top--;
    return OK;
}
double GetTop(SqStack S) {//操作数栈取栈顶元素
    if (S.top == S.base) return ERROR;
    return *(S.top - 1);
}
double Calculate(double a, char op, double b)
{//计算表达式“a op b”的值
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    }
}
double EvaluateExpression(SqStack OPND, char s[]) {
    //后缀算术表达式求值
    //设OPND为操作数栈
    //表达式求值算法调用Calculate函数 
    InitStack(OPND);
    int i = 0;
    char ch = s[i];

    while (ch != '=' && ch != '\0') { //??
        //while (ch == ' ') ch = s[++i];
        if (ch == ' ') { ch = s[++i]; continue; }
        if (ch == '=') break;

        if (ch == '+' || ch == '-' || ch == '*' || ch == '/') {
            double b = GetTop(OPND);
            Pop(OPND);
            double a = GetTop(OPND);
            Pop(OPND);
            double result = Calculate(a, ch, b);
            Push(OPND, result);
            ch = s[++i];
        }
        else {
            double num = ch - '0';
            Push(OPND, num);
            ch = s[++i];
        }
    }
    return GetTop(OPND);
}