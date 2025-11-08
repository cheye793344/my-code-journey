#include <iostream>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2
using namespace std;
typedef struct
{//符号栈
    char* base;
    char* top;
    int stacksize;
}SqStack1;
int InitStack1(SqStack1& S)
{//符号栈初始化
    S.base = new char[MAXSIZE];
    if (!S.base) return OVERFLOW;
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}
int Push1(SqStack1& S, char e)
{//符号栈入栈
    if (S.top - S.base == S.stacksize) return ERROR;
    *S.top++ = e;
    return OK;
}
int Pop1(SqStack1& S)
{//符号栈出栈
    if (S.top == S.base) return ERROR;
    S.top--;
    return OK;
}
char GetTop1(SqStack1 S)
{//符号栈取栈顶元素
    if (S.top == S.base) return ERROR;
    return *(S.top - 1);
}
typedef struct
{//数字栈
    double* base;
    double* top;
    int  stacksize;
}SqStack2;
int InitStack2(SqStack2& S)
{//数字栈初始化
    S.base = new double[MAXSIZE];
    if (!S.base) return ERROR;
    S.top = S.base;
    S.stacksize = MAXSIZE;
    return OK;
}
int Push2(SqStack2& S, double e)
{//数字栈入栈
    if (S.top - S.base == S.stacksize) return ERROR;
    *S.top++ = e;
    return OK;
}
int Pop2(SqStack2& S)
{//数字栈出栈
    if (S.top == S.base) return ERROR;
    S.top--;
    return OK;
}
double GetTop2(SqStack2 S)
{//数字栈取栈顶元素
    if (S.top == S.base) return ERROR;
    return *(S.top - 1);
}
double Calculate(double a, char op, double b)
{//算术表达式的求值		a在前，b在后
    switch (op) {
    case '+': return a + b;
    case '-': return a - b;
    case '*': return a * b;
    case '/': return a / b;
    }
}
char Precede(char a, char b)
{//比较符号优先级+,-,*,/,(,),=
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