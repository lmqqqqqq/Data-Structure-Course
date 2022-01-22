#include<iostream>
using namespace std;

bool tag1 = false;

typedef enum { Link, Threead }PointerTag;
typedef struct BiThrNode {
    char data;
    struct BiThrNode* lchild, * rchild;
    PointerTag LTag, RTag;
}BiThrNode, * BiThrTree;

BiThrTree T;
BiThrNode* pre = NULL;


//遍历中序线索二叉树（不带头结点）
void inorder1_Thr(BiThrTree T)
{
    BiThrTree p = T;
    while (p->LTag == Link) {
        p = p->lchild;
    }
    printf("%c", p->data);
    while (p->rchild) {
        if (p->RTag == Link)
        {
            p = p->rchild;
            while (p->LTag == Link) p = p->lchild;
        }
        else p = p->rchild;
        printf("%c", p->data);
    }
}


//先序建立二叉树
bool createBiThrTree(BiThrTree& t)
{
    char ch;
    cin >> ch;
    if (ch == '#') {
        t = NULL;
    }
    else {
        if (!(t = (BiThrNode*)malloc(sizeof(BiThrNode))))
            return false;
        t->data = ch;
        t->LTag = Link;
        t->RTag = Link;
        createBiThrTree(t->lchild);
        createBiThrTree(t->rchild);
    }
    return true;
}


//中序线索化
void InThreeading(BiThrTree P)
{
    if (P) {
        InThreeading(P->lchild);
        if (!P->lchild)
        {
            P->LTag = Threead;
            P->lchild = pre;
        }
        if (!P->rchild) {
            P->RTag = Threead;
        }
        if (pre && pre->RTag == Threead) {
            pre->rchild = P;
        }
        pre = P;
        InThreeading(P->rchild);
    }
}

//查找结点字符的前驱和后继结点元素
void searchBiThrTree(BiThrTree T, char k)
{
    BiThrTree a;
    BiThrTree p = T;
    while (p->LTag == Link) {
        p = p->lchild;
    }
    if (p->data == k) {
        tag1 = true;
        cout << "succ is ";
        if (p->rchild == NULL) {
            cout << "NULL" << endl;
        }
        else if (p->RTag == 1) {
            cout << p->rchild->data << p->rchild->RTag << endl;
        }
        else {
            a = p;
            a = a->rchild;
            while (a->LTag == 0) {
                a = a->lchild;
            }
            cout << a->data << a->RTag << endl;
        }
        cout << "prev is ";
        if (p->lchild == NULL) {
            cout << "NULL" << endl;
        }
        else if (p->LTag == 1) {
            cout << p->lchild->data << p->lchild->LTag << endl;
        }
        else {
            a = p;
            a = a->lchild;
            while (a->RTag == 0) {
                a = a->rchild;
            }
            cout << a->data << a->LTag << endl;
        }
    }
    while (p->rchild) {
        if (p->RTag == Link) {
            p = p->rchild;
            while (p->LTag == Link) {
                p = p->lchild;
            }
        }
        else {
            p = p->rchild;
        }
        if (p->data == k) {
            tag1 = true;
            cout << "succ is ";
            if (p->rchild == NULL) {
                cout << "NULL" << endl;
            }
            else if (p->RTag == 1) {
                cout << p->rchild->data << p->rchild->RTag << endl;
            }
            else {
                a = p;
                a = a->rchild;
                while (a->LTag == 0) {
                    a = a->lchild;
                }
                cout << a->data << a->RTag << endl;
            }
            cout << "prev is ";
            if (p->lchild == NULL) {
                cout << "NULL" << endl;
            }
            else if (p->LTag == 1) {
                cout << p->lchild->data << p->lchild->LTag << endl;
            }
            else {
                a = p;
                a = a->lchild;
                while (a->RTag == 0) {
                    a = a->rchild;
                }
                cout << a->data << a->LTag << endl;
            }
        }
    }
}

int main()
{
    BiThrTree t;
    t = (BiThrTree)malloc(sizeof(BiThrNode));
    createBiThrTree(t);
    InThreeading(t);
    char k;
    inorder1_Thr(t);
    cout << endl;
    cin >> k;
    searchBiThrTree(t, k);
    if (tag1 == false) {
        cout << "Not found" << endl;
    }
    return 0;
}