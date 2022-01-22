#include<iostream>
#include<cstring>
#include <stdlib.h>
#include<vector>
using namespace std;

struct TreeNode
{
	char data;
	int lchild;
	int rchild;
}T1[10105],T2[10105];

int BuildTree(TreeNode* T)
{
	int n;
	cin >> n;
	int check[10105];
	int root = -1;
	if (n) {
		for (int i = 0; i < n; i++) {
			check[i] = 0;
		}
		for (int i = 0; i < n; i++) {
			char clchild[10], crchild[10];
			cin >> T[i].data >> clchild >> crchild;
			if (strcmp(clchild,"-")) {
				T[i].lchild = atoi(clchild);
			}
			else {
				T[i].lchild = -1;
			}
			if (strcmp(crchild, "-")) {
				T[i].rchild = atoi(crchild);
			}
			else {
				T[i].rchild = -1;
			}
		}
		for (int i = 0; i < n; i++) {
			if (T[i].lchild != -1) {
				check[T[i].lchild] = 1;//编号为clchild的结点为某节点的左子树，一定不是根节点
			}
			if (T[i].rchild != -1) {
				check[T[i].rchild] = 1;//编号为clchild的结点为某节点的左子树，一定不是根节点
			}
		}
		for (int i = 0; i < n; i++) {//判断是不是根节点
			if (check[i] == 0) {
			    root=i;
				break;
			}
		}
	}
	return root;
}

bool Isomorphic(int R1, int R2)
{
	if ((R1 ==-1) && (R2 == -1)) {
		return true;
	}
	//对应一个树存在某个节点，而另一个树没有该节点
	else if ((R1 == -1 && R2 != -1) || (R2 == -1 && R1 != -1)) {
		return false;
	}
	else if (T1[R1].data != T2[R2].data)
	{
		return false;
	}
	else if (Isomorphic(T1[R1].lchild, T2[R2].lchild) && Isomorphic(T1[R1].rchild, T2[R2].rchild)) {
		return true;
	}
	else if (Isomorphic(T1[R1].lchild, T2[R2].rchild) && Isomorphic(T1[R1].rchild, T2[R2].lchild)) {
		return true;
	}
	return  false;
}

int Depth(TreeNode* T, int root)
{
	int depl, depr;
	if (root >= 0) {
		depl = Depth(T, T[root].lchild);
		depr = Depth(T, T[root].rchild);
		if (depl >= depr) {
			return depl + 1;
		}
		else {
			return depr + 1;
		}
	}
	return 0;
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int root1, root2;
	int dep1, dep2;
	root1 = BuildTree(T1);
	root2 = BuildTree(T2);
	dep1 = Depth(T1, root1);
	dep2 = Depth(T2, root2);
	if (Isomorphic(root1, root2)) {
		cout << "Yes" << endl;
		cout << dep1 << endl;
		cout << dep2 << endl;
	}
	else {
		cout << "No" << endl;
		cout << dep1 << endl;
		cout << dep2 << endl;
	}
	return 0;
}