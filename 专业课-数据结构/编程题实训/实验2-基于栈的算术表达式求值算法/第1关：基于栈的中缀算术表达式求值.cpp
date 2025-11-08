#include <iostream>
#include<iomanip>
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

double EvaluateExpression(SqStack1 OPTR, SqStack2 OPND, char s[])
{//算术表达式求值的算符优先算法
 //设OPTR和OPND分别为运算符栈和操作数栈
 //表达式求值算法调用Precede函数和Calculate函数 
    InitStack1(OPTR);
    InitStack2(OPND);
    Push1(OPTR, '=');

    int i = 0;
    char ch = s[i];
    while (ch != '=' || GetTop1(OPTR) != '=') { //未遇到结束符进入循环
        if ((ch >= '0' && ch <= '9') || ch == '.') { //如果读到的是数字
        //设置并初始化一些变量辅助处理浮点数和整数混合的数据
            double num = 0;
            double decimal = 0;
            double factor = 1; //小数部分数量级
            bool hasDecimal = false; //是否有小数部分

            while ((ch >= '0' && ch <= '9') || ch == '.') {
                if (ch == '.') { //读到小数点
                    hasDecimal = true; //记录为浮点数
                    ch = s[++i]; //小数点不做处理，跳过
                    continue;
                }

                if (!hasDecimal) { //计算整数部分
                    num = num * 10 + (ch - '0'); //在结尾加上这轮读到的数字
                }
                else {
                    factor *= 0.1;
                    decimal = decimal + (ch - '0') * factor; //累计小数部分
                }
                ch = s[++i];
            }
            num += decimal; //合计这个数的整数和小数部分
            Push2(OPND, num);
        }
        else { //如果读到运算符
            char topOp = GetTop1(OPTR); //栈顶元素
            char theta;
            double result = 0.00;
            double a, b = 0.00;
            switch (Precede(topOp, ch)) {
            case '>':
                theta = GetTop1(OPTR);
                Pop1(OPTR); //栈顶弹出
                b = GetTop2(OPND);
                Pop2(OPND);
                a = GetTop2(OPND);
                Pop2(OPND); //弹出两个数进行运算
                result = Calculate(a, theta, b);
                Push2(OPND, result);
                break;
            case '<':
                Push1(OPTR, ch);
                ch = s[++i];
                break;
            case '=':
                Pop1(OPTR);
                ch = s[++i];
                break;
            }
        }
    }
    return GetTop2(OPND);
}
