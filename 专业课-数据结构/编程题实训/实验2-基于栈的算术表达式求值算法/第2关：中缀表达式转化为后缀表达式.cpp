#include<iostream>
using namespace std;
#define  MAXSIZE  100
#define OK 1
#define ERROR 0
#define OVERFLOW -2
typedef struct
{
	char* base;
	char* top;
	int stacksize;
}SqStack;
int InitStack(SqStack& S)
{//初始化栈
	S.base = new char[MAXSIZE];
	if (!S.base) return ERROR;
	S.top = S.base;
	S.stacksize = MAXSIZE;
	return OK;
}
int Push(SqStack& S, char e)
{//入栈
	if (S.top - S.base == S.stacksize) return ERROR;
	*S.top++ = e;
	return OK;
}
int Pop(SqStack& S)
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
{//比较符号优先级
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