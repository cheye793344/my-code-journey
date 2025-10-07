#include<iostream>
using namespace std;
typedef struct BiTNode
{
    char data;
    struct BiTNode* lchild, * rchild;
}BiTNode, * BiTree;
void CreateBiTree(BiTree& T, char S[], int& i)
{////先序建立二叉树
/**************begin************/
    if (S[i] == '0' || S[i] == '\0')
    {
        T = NULL;
        i++;
        return;
    }
    T = new BiTNode();
    T->data = S[i];
    T->lchild = T->rchild = NULL;
    i++;
    CreateBiTree(T->lchild, S, i);
    CreateBiTree(T->rchild, S, i);
    /**************end************/
}
int Compare(BiTree T1, BiTree T2)
{//判断两棵二叉树是否相等，不相等返回0，相等返回1
/**************begin************/
    // 两个都为空
    if (T1 == NULL && T2 == NULL)
        return 1;

    // 一个为空一个不为空
    if (T1 == NULL || T2 == NULL)
        return 0;

    // 当前结点值不相等
    if (T1->data != T2->data)
        return 0;

    // 递归比较左右子树
    int leftEqual = Compare(T1->lchild, T2->lchild);
    int rightEqual = Compare(T1->rchild, T2->rchild);

    return leftEqual && rightEqual;
    /**************end************/
}
int main()
{
    char S1[100], S2[100];
    while (cin >> S1 && S1[0] != '0')
    {
        cin >> S2;
        int i = -1, j = -1;
        BiTree T1, T2;
        CreateBiTree(T1, S1, ++i);
        CreateBiTree(T2, S2, ++j);
        if (!Compare(T1, T2))
            cout << "NO" << endl;
        else
            cout << "YES" << endl;
    }
    return 0;
}