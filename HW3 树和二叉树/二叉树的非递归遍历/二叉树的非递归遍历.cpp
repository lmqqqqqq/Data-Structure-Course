#include<iostream>
#include<cstring>
using namespace std;

typedef struct BiTNode {
	char data;
	BiTNode* lchild, * rchild;
}BiTNode, * BiTree;

int cnt=0;

bool CreateBiTree(BiTree& T, string preorder)
{
	if (cnt < preorder.length()) {
		char ch = preorder[cnt];
		cnt++;
		if (ch == '<') {
			T = NULL;
		}
		else {
			if (!(T = (BiTNode*)malloc(sizeof(BiTNode)))) {
				cout << "¶¯Ì¬ÄÚ´æÉêÇëÊ§°Ü" << endl;
				exit(-1);
			}
			T->data = ch;
			CreateBiTree(T->lchild, preorder);
			CreateBiTree(T->rchild, preorder);
		}
	}
	return true;
}

void PostOrderTraverse(BiTree T)
{
	if (T) {
		PostOrderTraverse(T->lchild);
		PostOrderTraverse(T->rchild);
		cout << T->data;
	}
}

int main()
{
	int n;
	cin >> n;
	string preorder="";
	for (int i = 0; i < 2 * n; i++) {
		char command[6];
		char ch;
		cin >> command;
		if (!strcmp(command, "push")) {
			cin >> ch;
			preorder += ch;
		}
		if (!strcmp(command, "pop")) {
			preorder += "<";
		}
	}
	preorder += "<";
	BiTree T;
	CreateBiTree(T, preorder);
	PostOrderTraverse(T);
	return 0;

}