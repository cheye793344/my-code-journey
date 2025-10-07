#include<iostream>
#include<cstring>
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
void ChangeRL(BiTree& T)
{//二叉树左右孩子的交换
/**************begin************/
	if (T == NULL)
		return;

	// 交换当前结点的左右孩子
	BiTree temp = T->lchild;
	T->lchild = T->rchild;
	T->rchild = temp;

	// 递归交换左子树
	ChangeRL(T->lchild);
	// 递归交换右子树
	ChangeRL(T->rchild);
	/**************end************/
}
void PreOrderTraverse(BiTree T)
{//先序遍历
	if (T)
	{
		cout << T->data;
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
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
		ChangeRL(T);
		PreOrderTraverse(T);
		cout << endl;
	}
	return 0;
}