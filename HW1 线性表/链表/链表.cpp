#include<iostream>
using namespace std;

struct Node
{
    int data;
    Node* next;
};

Node* ListCreate(int n)
{
    Node* head = new Node;
    Node* p = head;
    //利用尾插法创建一个链表
    for (int i = 1; i <= n; i++) {
        Node* q = new Node;
        p->next = q;
        cin >> q->data;
        p = p->next;
    }
    p->next = NULL;
    return head;
}

void ListDisplay(Node* head)
{
    Node* p = head;
    p = p->next;
    cout << "链表中的元素为";
    while (p) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

bool ListInsert(Node* head, int i, int data)
{
    //在带头结点的单链线性表中第i个位置之前插入元素data
    Node* p = head;
    int j = 0;
    while (p && j < i - 1) {//寻找第i-1个结点
        p = p->next;
        j++;
    }
    if (p == NULL || j >= i - 1) {//i小于1或者大于表长加1
        cout << "插入失败" << endl;
        return false;
    }
    Node* s = new Node;//生成新结点
    s->data = data;//插入链表中
    s->next = p->next;
    p->next = s;
    return true;
}

bool ListDelete(Node* head, int i, int& data)
{
    //在带头结点的单链线性表中删除第i个元素,并由data返回其值
    Node* p = head;
    int j = 0;
    while (p->next && j < i - 1) {//寻找第i个结点，并令p指向其前驱
        p = p->next;
        j++;
    }
    if (p->next == NULL || j >= i - 1) {
        cout << "删除位置不合理" << endl;
        return false;
    }
    Node* q = p->next;//删除并释放结点
    p->next = q->next;
    data = q->data;
    free(q);
    return true;
}

bool ListGetElem(Node* head, int i, int& data)
{
    //当第i个元素存在时，其值赋给data
    Node* p = head->next;//初始化，p指向第一个结点
    int j = 1;//计数器
    while (p && j < i) {//顺指针向后查找，直到p指向第i个元素或p为空
        p = p->next;
        j++;
    }
    if (p == NULL || j >= i) {
        cout << "第" << i << "个元素不存在" << endl;
        return false;
    }
    data = p->data;//取第i个元素
    return true;
}

void ListReverse(Node* head)
{
    Node* p;
    p = head->next;
    head->next = NULL;
    while (p)
    {//头插法
        Node* q = p;
        p = p->next;
        q->next = head->next;
        head->next = q;
    }
}

void ListDeleteDuplication(Node* head)
{

    Node* cur = head;
    Node* pre = NULL;
    Node* next = NULL;
    while (NULL != cur) {//针对每一个元素查找所有与其值相等的元素
        pre = cur;
        next = cur->next;
        while (NULL != next) {
            if (cur->data == next->data) {
                pre->next = next->next;
                free(next);//释放重复元素空间
            }
            else {
                pre = next;
            }
            next = next->next;
        }
        cur = cur->next;
    }
}



void ListMerge(Node*& La, Node*& Lb, Node*& Lc)
{
    //单链线性表La和Lb的元素按值非递减排列，归并得到的新单链线性表Lc的元素也按值非递减排列
    Node* pa = La->next;
    Node* pb = Lb->next;
    Node* pc = La;
    Lc = pc;//用La的头结点作为Lc的头结点
    while (pa && pb) {
        if (pa->data <= pb->data) {
            pc->next = pa;
            pc = pa;
            pa = pa->next;
        }
        else {
            pc->next = pb;
            pc = pb;
            pb = pb->next;
        }
    }
    pc->next = pa ? pa : pb;//插入剩余段
    free(Lb);//释放Lb的头结点
}

int main()
{
    int n;
    cin >> n;
    Node* head;
    head = ListCreate(n);
    ListReverse(head);
    //ListDeleteDuplication(head);
    ListDisplay(head);
    return 0;
}