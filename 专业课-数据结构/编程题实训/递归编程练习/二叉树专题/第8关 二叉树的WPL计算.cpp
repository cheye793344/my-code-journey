#include<iostream>
using namespace std;
typedef struct BiTNode
{
	int weight;
	struct BiTNode* left, * right;
}BiTNode, * BiTree;
void CreateBiTree(BiTree& T)
{//先序建立二叉树
	int x;
	cin >> x;
	if (x == 0) T = NULL;
	else
	{
		T = new BiTNode;
		T->weight = x;
		CreateBiTree(T->left);
		CreateBiTree(T->right);
	}
}
int WPL(BiTree& T, int d)
{//求二叉树T的带权路径长度
/**************begin************/
	if (T == NULL) return 0;
	// 如果是叶子结点，返回权重乘以深度
	if (T->left == NULL && T->right == NULL)
		return T->weight * d;
	// 递归计算左右子树的WPL
	return WPL(T->left, d + 1) + WPL(T->right, d + 1);
	/**************end************/
}
int main()
{
	while (1)
	{
		BiTree T;
		CreateBiTree(T);
		if (!T) break;
		int d = 0;          //调用时T指向二叉树的根结点，d为0
		cout << WPL(T, d) << endl;
	}
	return 0;
}