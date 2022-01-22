#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<cstring>
using namespace std;

struct student
{
    char no[8];
    char name[20];
    double score;
};

student* read(int n)
{
    student* stu = (student*)malloc(n * sizeof(student));//��̬�����ڴ�
    if (stu == NULL) {
        cout << "��̬�ڴ�����ʧ��" << endl;
        exit(-1);
    }
    cout << "����������" << n << "��ѧ����Ϣ" << endl;
    student* p = stu;
    for (int i = 1; i <= n; i++) {//����ѧ����Ϣ
        scanf("%s%s%lf", p->no, p->name, &(p->score));
        p++;
    }
    return stu;
}

void dispaly(student* stu, int n)
{
    student* p = stu;
    for (int i = 1; i <= n; i++) {//���ѧ����Ϣ
        cout << "��" << i << "��ͬѧ��ѧ����" << p->no << ",������" << p->name << ",�ɼ���" << p->score << endl;
        p++;
    }
    return;
}

bool ListInsert(student*& stu, int pos, char no1[8], char name1[20], double score1, int& n)
{
    if (pos<1 || pos>n + 1) {
        cout << "λ�÷Ƿ�" << endl;
        return false;
    }
    stu = (student*)realloc(stu, (n + 1) * sizeof(student));
    if (stu == NULL) {
        cout << "��̬�ڴ�����ʧ��" << endl;
        exit(-1);
    }
    student* q = &stu[pos - 1];//�����λ��
    for (student* p = &stu[n - 1]; p >= q; p--) {//���������λ
        strcpy((p + 1)->no, p->no);
        strcpy((p + 1)->name, p->name);
        (p + 1)->score = p->score;
    }
    strcpy(q->no, no1);//�����Ԫ��
    strcpy(q->name, name1);
    q->score = score1;
    n++;
    return true;
}

bool ListDelete(student*& stu, int id, int& n)
{
    if (id<1 || id>n) {
        cout << "λ�÷Ƿ�" << endl;
        return false;
    }
    student* p = &stu[id - 1];//ɾ����λ��
    student* q = &stu[n - 1];//��β
    for (p++; p <= q; p++) {//������ǰһλ
        strcpy((p - 1)->no, p->no);
        strcpy((p - 1)->name, p->name);
        (p - 1)->score = p->score;
    }
    stu = (student*)realloc(stu, (n - 1) * sizeof(student));//��������ռ�
    n--;
    return true;
}

int ListSearchName(student*& stu, char name1[20], int& n)
{
    student* p = stu;
    for (int i = 1; i <= n; i++) {
        if (!strcmp(p->name, name1)) {//���������ֲ���
            cout << "��ѧ����ѧ����" << p->no << ",�ɼ���" << p->score << endl;
            return i;
        }
        else {
            p++;
        }
    }
    return 0;
}

void location(student*& stu, int pos)
{
    student* p = stu;
    cout << "��ѧ����ѧ����" << (p + pos - 1)->no << ",������" << (p + pos - 1)->name << ",�ɼ���" << (p + pos - 1)->score << endl;
}


int ListSearchNo(student*& stu, char no1[8], int& n)
{
    student* p = stu;
    for (int i = 1; i <= n; i++) {
        if (!strcmp(p->no, no1)) {//������ѧ�Ų���
            cout << "��ѧ����������" << p->name << ",�ɼ���" << p->score << endl;
            return i;
        }
        else {
            p++;
        }
    }
    return 0;
}

void show_num(int n)
{
    cout << "ѧ��������Ϊ" << n << endl;
}

bool Delete_by_info(student*& stu, char name1[20], char no1[8], double score1, int& n)
{
    student* p = stu;//��ͷλ��
    student* q = &stu[n - 1];//��βλ��
    bool flag = false;//�Ƿ��ҵ���ѧ��
    for (; p <= q; p++) {
        if (!strcmp(p->name, name1) && !strcmp(p->no, no1) && p->score == score1) {//��������
            for (p++; p <= q; p++) {//��ɾ��Ԫ��֮���Ԫ�ض���ǰ��һλ
                strcpy((p - 1)->no, p->no);
                strcpy((p - 1)->name, p->name);
                (p - 1)->score = p->score;
            }
            flag = true;
            break;
        }
    }
    if (flag) {
        stu = (student*)realloc(stu, (n - 1) * sizeof(student));
        n--;
        return true;
    }
    else {
        cout << "��ѧ����Ϣ����" << endl;
        return false;
    }
}

void ListUnique(student*& stu, int& n)
{
    student* p = stu;
    for (int i = 2; i <= n; i++) {//��������
        for (int j = i; j > 1; j--) {
            if (strcmp((p + j - 1)->no, (p + j - 2)->no) > 0) {
                break;
            }
            else {
                swap((p + j - 1)->no, (p + j - 2)->no);
                swap((p + j - 1)->name, (p + j - 2)->name);
                double tmp = (p + j - 1)->score;
                (p + j - 1)->score = (p + j - 2)->score;
                (p + j - 2)->score = tmp;
            }
        }
    }
    int n1 = n;//ȥ�ع�����n���仯���ȱ���n
    int samenum = 0;
    for (int i = 1; i <= n1 - 1; i++) {
        if (!strcmp((p + i - 1 - samenum)->no, (p + i - samenum)->no)) {
            student* q = p + i - 1 - samenum;//ɾ��Ԫ�غ��������ڼ���Ԫ�ص�λ��
            student* r = p + n1 - 1 - samenum;//ɾ��Ԫ�غ����һ��Ԫ��λ��
            for (q++; q <= r; q++) {//��ǰ�ƶ�һλ
                strcpy((q - 1)->no, q->no);
                strcpy((q - 1)->name, q->name);
                (q - 1)->score = q->score;
            }
            n--;
            samenum++;
        }
    }
    stu = (student*)realloc(stu, n * sizeof(student));
}

int main()
{
    int n;
    scanf("%d", &n);
    student* stu;
    stu = read(n);
    char command[20];
    while (1) {
        scanf("%s", command);
        if (!strcmp(command, "end")) {
            printf("%d", n);
            break;
        }
        else if (!strcmp(command, "insert")) {
            int pos1;
            char no1[8], name1[20];
            double score1;
            scanf("%d%s%s%lf", &pos1, no1, name1, &score1);
            if (ListInsert(stu, pos1, no1, name1, score1, n)) {
                printf("%d\n", 0);
            }
            else {
                printf("%d\n", -1);
            }

        }
        else if (!strcmp(command, "remove")) {
            int id1;
            scanf("%d", &id1);
            if (ListDelete(stu, id1, n)) {
                printf("%d\n", 0);
            }
            else {
                printf("%d\n", -1);
            }
        }
        else {
            char command2[20];
            scanf("%s", command2);
            if (!strcmp(command2, "name")) {
                char name1[20];
                scanf("%s", name1);
                int pos = ListSearchName(stu, name1, n);
                if (pos) {
                    printf("%d %s %s\n", pos, stu[pos - 1].no, stu[pos - 1].name);
                }
                else {
                    printf("%d\n", -1);
                }
            }
            else {
                char no1[8];
                scanf("%s", no1);
                int pos = ListSearchNo(stu, no1, n);
                if (pos) {
                    printf("%d %s %s\n", pos, stu[pos - 1].no, stu[pos - 1].name);
                }
                else {
                    printf("%d\n", -1);
                }
            }
        }
    }
    return 0;
}

/*
#define _CRT_SECURE_NO_WARNINGS
#include <iostream>
#include<stdlib.h>
#include<stdio.h>
#include<cstring>
#define Increase 10
using namespace std;

struct node
{
    char num[10] = { '\0' };
    char name[14] = { '\0' };
};

void initial(node* p, int n)//��ʼװ����Ϣ
{
    for (int i = 1; i <= n; i++)
    {
        scanf("%s %s", p->num, p->name);
        p++;
    }
}

void insert(node*& Initial, int& size, int& cursize)//cursizeΪ��ǰ������λ��
{
    int pos;//����λ��
    scanf("%d", &pos);
    if (pos<1 || pos>cursize + 1)
        printf("-1\n");
    else
    {
        printf("0\n");

        node* p;
        node* t = new node;
        scanf("%s %s", t->num, t->name);
        if (cursize >= size)
        {
            Initial = (node*)realloc(Initial, sizeof(node) * (size + Increase + 2));
            if (!Initial)
                exit(0);
            size += Increase;
        }

        p = Initial;
        p += cursize - 1;//��λ���һ��λ�ã�˳�����ŵ㣩

        for (int i = cursize; i >= pos; i--)//��cursize��ǰ��
        {

            *(p + 1) = *p;
            if (p != Initial)//��ָֹ����Խ��
                p--;
        }
        if (pos != 1)
            p++;

        *p = *t;
        cursize++;
        delete t;

    }

}

void remove(node*& Initial, int& cursize)
{
    int pos;
    scanf("%d", &pos);
    if (pos<1 || pos>cursize)
        printf("-1\n");
    else
    {
        printf("0\n");
        node* p;
        p = Initial + pos;//ɾ����һ��
        for (int i = pos; i <= cursize; i++)//��ǰ����,i��ʾ������λ��
        {
            *(p - 1) = *p;
            p++;
        }
        cursize--;
    }

}

void check_name(node* Initial, int cursize)
{
    char nam[14] = { '\0' };
    scanf("%s", nam);//����

    node* p = Initial;
    int i = 1;//ͬ��
    while (i <= cursize && (strcmp(nam, p->name) != 0))//�����
    {
        p++; i++;
    }
    if (i > cursize)
        printf("-1\n");
    else
        printf("%d %s %s\n", i, p->num, p->name);
}

void check_no(node* Initial, int cursize)
{
    char no[10] = { '\0' };
    scanf("%s", no);//ѧ��

    node* p = Initial;
    int i = 1;//ͬ��
    while (i <= cursize && (strcmp(no, p->num) != 0))//�����
    {
        p++; i++;
    }
    if (i > cursize)
        printf("-1\n");
    else
        printf("%d %s %s\n", i, p->num, p->name);
}


void process(node*& Initial, int& size, int& cursize)
{
    while (1)
    {
        char order[10] = { '\0' };//��������������������û���ǵ������뵼�´���
        scanf("%s", order);
        if (strcmp(order, "end") == 0)
        {
            printf("%d", cursize);
            break;
        }
        else if (strcmp(order, "insert") == 0)
            insert(Initial, size, cursize);

        else if (strcmp(order, "remove") == 0)
            remove(Initial, cursize);

        else if (strcmp(order, "check") == 0)
        {
            char op[10] = { '\0' };
            scanf("%s", op);
            if (strcmp(op, "name") == 0)
                check_name(Initial, cursize);
            else if (strcmp(op, "no") == 0)
                check_no(Initial, cursize);
        }
    }
}

int main()
{
    int n, size, cursize, dupli(0);
    scanf("%d", &n);
    node* Initial = (node*)malloc(sizeof(node) * (n + 2));//��ʼλ��(����������ֹ����1������ɾ��2������ʱ��û������/Խ�磩
    if (!Initial)
        exit(0);

    initial(Initial, n);
    size = cursize = n;

    process(Initial, size, cursize);

    return 0;
}

*/
