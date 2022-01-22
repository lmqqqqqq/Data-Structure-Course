#include<iostream>
#include<queue>
using namespace std;

typedef struct BiTNode {
	char data;
	BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

//按先序次序输入二叉树中结点的值（一个字符），空格字符表示空树
bool CreateBiTree(BiTree& T)
{
	char ch;
	cin >> ch;
	if (ch == '#') {
		T = NULL;
	}
	else {
		if (!(T = (BiTNode*)malloc(sizeof(BiTNode)))) {
			cout << "动态内存申请失败" << endl;
			exit(-1);
		}
		T->data = ch;
		CreateBiTree(T->lchild);
		CreateBiTree(T->rchild);
	}
	return true;
}

//先序遍历二叉树
void PreOrderTraverse(BiTree T)
{
	if (T) {
		cout << T->data;
		PreOrderTraverse(T->lchild);
		PreOrderTraverse(T->rchild);
	}
}

//中序遍历二叉树
void InOrderTraverse(BiTree T)
{
	if (T) {
		InOrderTraverse(T->lchild);
		cout << T->data;
		InOrderTraverse(T->rchild);
	}
}

//后序遍历二叉树
void PostOrderTraverse(BiTree T)
{
	if (T) {
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		cout << T->data;
	}
}

//层次遍历二叉树
void LayerOrderTraverse(BiTree T)
{
	queue<BiTree> Q;
	Q.push(T);
	while (!Q.empty()) {
		BiTree p = Q.front();
		if (p != NULL) {
			cout << p->data;
			Q.push(p->lchild);
			Q.push(p->rchild);
		}
		Q.pop();
	}
}

//输出二叉树的树形图（逆时针旋转90度）
void display(BiTree T, int n)
{
	if (T) {
		display(T->rchild, n + 1);
		for (int i = 1; i <= n; i++) {
			cout << "     ";
		}
		cout << T->data << endl;
		display(T->lchild, n + 1);
	}
}

int main()
{
	BiTree T;
	CreateBiTree(T);
	PreOrderTraverse(T);
	cout << endl;
	InOrderTraverse(T);
	cout << endl;
	PostOrderTraverse(T);
	cout << endl;
	LayerOrderTraverse(T);
	cout << endl;
	display(T, 0);
	return 0;
}

