#include<iostream>
using namespace std;

typedef struct BiTNode {
	int key;
	int count;
	BiTNode* lchild;
	BiTNode* rchild;
}BiTNode,*BiTree;

bool InsertBST(BiTree& T,int key)
{
	if (!T) {
		T = (BiTree)malloc(sizeof(BiTNode));
		T->key = key;
		T->count = 1;
		T->lchild = NULL;
		T->rchild = NULL;
	}
	else {
		if (T->key > key) {
			InsertBST(T->lchild, key);
		}
		else if (T->key < key) {
			InsertBST(T->rchild, key);
		}
		else {
			T->count++;
		}
	}
	return true;
}

bool Delete(BiTree& T)
{
	if (!T->rchild) {//右子树空则只需重连它的左子树
		if (T->count != 1) {
			T->count--;
		}
		else {
			BiTree q = T;
			T = T->lchild;
			free(q);
		}
	}
	else if (!T->lchild) {//左子树空则只需重连它的右子树
		if (T->count != 1) {
			T->count--;
		}
		else {
			BiTree q = T;
			T = T->rchild;
			free(q);
		}
	}
	else {//左右子树均不空
		if (T->count != 1) {
			T->count--;
		}
		else {
			BiTree q = T;
			BiTree s = T->lchild;
			while (s->rchild) {//转左，然后向右到尽头
				q = s;
				s = s->rchild;
			}
			T->key = s->key;
			T->count = s->count;
			if (q != T) {
				q->rchild = s->lchild;//重连q的右子树
			}
			else {
				q->lchild = s->lchild;//重连q的左子树
			}
			free(s);
		}
	}
	return true;
}

bool DeleteBST(BiTree& T, int key) 
{
	if (!T) {
		return false;
	}
	else {
		if (T->key == key) {
			return Delete(T);
		}
		else if (T->key > key) {
			return DeleteBST(T->lchild,key);
		}
		else {
			return DeleteBST(T->rchild,key);
		}
	}
}

int Getnum(BiTree T, int key)
{
	if (!T) {
		return 0;
	}
	if (T->key == key) {
		return T->count;
	}
	else if (T->key < key) {
		return Getnum(T->rchild, key);
	}
	else {
		return Getnum(T->lchild, key);
	}
}

int Getmin(BiTree T)
{
	BiTree p = T;
	while (p->lchild) {
		p = p->lchild;
	}
	return p->key;
}

BiTree Getpri(BiTree T, int key)
{
	if (!T) {
		return NULL;
	}
	if (T->key >= key) {
		return Getpri(T->lchild, key);
	}
	else {
		BiTree p=Getpri(T->rchild , key);
		if (p) {
			return p;
		}
		else{
			return T;
		}
	}
}

int main()
{
	BiTree T = NULL;
	int n;
	cin >> n;
	for (int i = 0; i < n; i++) {
		int op,x;
		cin >> op;
		if (op == 1) {
			cin >> x;
			InsertBST(T, x);
		}
		else if (op == 2) {
			cin >> x;
			if (!DeleteBST(T, x)) {
				cout << "None" << endl;
			}
		}
		else if (op == 3) {
			cin >> x;
			int ans = Getnum(T, x);
			cout << ans << endl;
		}
		else if (op == 4) {
			int ans = Getmin(T);
			cout << ans << endl;
		}
		else {
			cin >> x;
			BiTree ans = Getpri(T, x);
			if (ans) {
				cout << ans->key << endl;
			}
			else {
				cout << "None" << endl;
			}
		}
	}
	return 0;
}