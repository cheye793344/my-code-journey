#include<iostream>
#include<string.h>
using namespace std;
int a, b, c;//a、b、c分别表示度为0、1、2的结点个数
typedef struct BiTNode
{
	char data;
	struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;
void CreateBiTree(BiTree& T, char S[], int& i)
{//先序建立二叉树
	if (S[i] == '0')
		T = NULL;
	else
	{
		T = new BiTNode;
		T->data = S[i];
		CreateBiTree(T->lchild, S, ++i);
		CreateBiTree(T->rchild, S, ++i);
	}
}
void Count(BiTree T)
{//二叉树结点个数的统计
/**************begin************/
	if (T == NULL) return;
	if (T->lchild == NULL && T->rchild == NULL) a++;
	else if (T->lchild != NULL && T->rchild != NULL) c++;
	else b++;
	Count(T->lchild);
	Count(T->rchild);
	/**************end************/
}
int main()
{
	char S[100];
	while (cin >> S)
	{
		if (strcmp(S, "0") == 0) break;
		a = b = c = 0;
		int i = -1;
		BiTree T;
		CreateBiTree(T, S, ++i);
		Count(T);
		cout << a << " " << b << " " << c << endl;
	}
	return 0;
}