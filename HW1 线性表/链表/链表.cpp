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
    //����β�巨����һ������
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
    cout << "�����е�Ԫ��Ϊ";
    while (p) {
        cout << p->data << ' ';
        p = p->next;
    }
    cout << endl;
}

bool ListInsert(Node* head, int i, int data)
{
    //�ڴ�ͷ���ĵ������Ա��е�i��λ��֮ǰ����Ԫ��data
    Node* p = head;
    int j = 0;
    while (p && j < i - 1) {//Ѱ�ҵ�i-1�����
        p = p->next;
        j++;
    }
    if (p == NULL || j >= i - 1) {//iС��1���ߴ��ڱ���1
        cout << "����ʧ��" << endl;
        return false;
    }
    Node* s = new Node;//�����½��
    s->data = data;//����������
    s->next = p->next;
    p->next = s;
    return true;
}

bool ListDelete(Node* head, int i, int& data)
{
    //�ڴ�ͷ���ĵ������Ա���ɾ����i��Ԫ��,����data������ֵ
    Node* p = head;
    int j = 0;
    while (p->next && j < i - 1) {//Ѱ�ҵ�i����㣬����pָ����ǰ��
        p = p->next;
        j++;
    }
    if (p->next == NULL || j >= i - 1) {
        cout << "ɾ��λ�ò�����" << endl;
        return false;
    }
    Node* q = p->next;//ɾ�����ͷŽ��
    p->next = q->next;
    data = q->data;
    free(q);
    return true;
}

bool ListGetElem(Node* head, int i, int& data)
{
    //����i��Ԫ�ش���ʱ����ֵ����data
    Node* p = head->next;//��ʼ����pָ���һ�����
    int j = 1;//������
    while (p && j < i) {//˳ָ�������ң�ֱ��pָ���i��Ԫ�ػ�pΪ��
        p = p->next;
        j++;
    }
    if (p == NULL || j >= i) {
        cout << "��" << i << "��Ԫ�ز�����" << endl;
        return false;
    }
    data = p->data;//ȡ��i��Ԫ��
    return true;
}

void ListReverse(Node* head)
{
    Node* p;
    p = head->next;
    head->next = NULL;
    while (p)
    {//ͷ�巨
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
    while (NULL != cur) {//���ÿһ��Ԫ�ز�����������ֵ��ȵ�Ԫ��
        pre = cur;
        next = cur->next;
        while (NULL != next) {
            if (cur->data == next->data) {
                pre->next = next->next;
                free(next);//�ͷ��ظ�Ԫ�ؿռ�
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
    //�������Ա�La��Lb��Ԫ�ذ�ֵ�ǵݼ����У��鲢�õ����µ������Ա�Lc��Ԫ��Ҳ��ֵ�ǵݼ�����
    Node* pa = La->next;
    Node* pb = Lb->next;
    Node* pc = La;
    Lc = pc;//��La��ͷ�����ΪLc��ͷ���
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
    pc->next = pa ? pa : pb;//����ʣ���
    free(Lb);//�ͷ�Lb��ͷ���
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