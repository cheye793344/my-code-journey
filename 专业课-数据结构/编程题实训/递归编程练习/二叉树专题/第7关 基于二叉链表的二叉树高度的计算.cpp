#include<iostream>
#include <string.h>
using namespace std;
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
int Depth(BiTree T)
{//二叉树高度的计算
/**************begin************/
	if (T == NULL) return 0;
	int leftDepth = Depth(T->lchild);
	int rightDepth = Depth(T->rchild);
	return (leftDepth > rightDepth ? leftDepth : rightDepth) + 1;
	/**************end************/
}
int main()
{
	char S[100];
	while (cin >> S)
	{
		if (strcmp(S, "0") == 0) break;
		int i = -1;
		BiTree T;
		CreateBiTree(T, S, ++i);
		cout << Depth(T) << endl;
	}
	return 0;
}