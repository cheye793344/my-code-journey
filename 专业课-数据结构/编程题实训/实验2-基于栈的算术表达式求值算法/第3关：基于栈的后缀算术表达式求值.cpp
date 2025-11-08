#include <iostream>
#include <string>
#define MAXSIZE 100
#define OK 1
#define ERROR 0
#define OVERFLOW -2
using namespace std;
typedef struct
{//数字栈
	double* base;
	double* top;
	int  stacksize;
}SqStack;
int InitStack(SqStack& S)
{//数字栈初始化
	S.base = new double[MAXSIZE];
	if (!S.base) return ERROR;
	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;
}
int Push(SqStack& S, double e)
{//数字栈入栈
	if (S.top - S.base == S.stacksize) return ERROR;
	*S.top++ = e;
	return OK;
}
int Pop(SqStack& S)
{//数字栈出栈
	if (S.top == S.base) return ERROR;
	S.top--;
	return OK;
}
double GetTop(SqStack S)
{//数字栈取栈顶元素
	if (S.top == S.base) return ERROR;
	return *(S.top - 1);
}
double Calculate(double a, char op, double b)
{//算术表达式的求值		a在前， b在后
	switch (op) {
	case '+': return a + b;
	case '-': return a - b;
	case '*': return a * b;
	case '/': return a / b;
	}
}
