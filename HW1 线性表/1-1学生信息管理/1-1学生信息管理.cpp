#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<stdlib.h>
#include<cstring>
using namespace std;

struct student
{
    char no[8];
    char name[20];
};

bool ListInsert(student* &stu, int pos, char no1[8], char name1[20], int &n)
{
    if (pos<1 || pos>n + 1) {
        return false;
    }
    stu = (student*)realloc(stu, (n + 1) * sizeof(student));
    if (stu == NULL) {
        cout << "动态内存申请失败" << endl;
        exit(-1);
    }
    student* q = &stu[pos - 1];
    for (student* p = &stu[n - 1]; p >= q; p--) {
        strcpy((p + 1)->no, p->no);
        strcpy((p + 1)->name, p->name);
    }
    strcpy(q->no, no1);
    strcpy(q->name, name1);
    n++;
    return true;
}

bool ListDelete(student* &stu, int id, int &n)
{
    if (id<1 || id>n ) {
        return false;
    }
    student* p = &stu[id - 1];
    student* q = &stu[n - 1];
    for (p++; p <= q;p++) {
        strcpy((p - 1)->no, p->no);
        strcpy((p-1)->name, p->name);
    }
    stu = (student*)realloc(stu, (n - 1) * sizeof(student));
    n--;
    return true;
}

int ListSearchName(student* &stu, char name1[20], int &n)
{
    student* p = stu;
    for (int i = 1; i <= n; i++) {
        if (!strcmp(p->name, name1)) {
            return i;
        }
        else {
            p++;
        }
    }
    return 0;
}

int ListSearchNo(student* &stu, char no1[8], int &n)
{
    student* p = stu;
    for (int i = 1; i <= n; i++) {
        if (!strcmp(p->no,no1)) {
            return i;
        }
        else {
            p++;
        }
    }
    return 0;
}

int main()
{
    int n;
    scanf("%d", &n);
    student* stu = (student*)malloc(n * sizeof(student));
    if (stu == NULL) {
        cout << "动态内存申请失败" << endl;
        exit(-1);
    }
    student* p = stu;
    for (int i = 1; i <= n; i++) {
        scanf("%s%s", p->no, p->name);
        p++;
    }
    char command[20];
    while (1) {
        scanf("%s", command);
        if (!strcmp(command, "end")) {
            printf("%d", n);
            break;
        }
        else if (!strcmp(command, "insert")) {
            int pos1;
            char no1[8],name1[20];
            scanf("%d%s%s", &pos1, no1, name1);
            if (ListInsert(stu, pos1, no1, name1, n)) {
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
        else  {
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

void initial(node* p, int n)//初始装载信息
{
    for (int i = 1; i <= n; i++)
    {
        scanf("%s %s", p->num, p->name);
        p++;
    }
}

void insert(node*& Initial, int& size, int& cursize)//cursize为当前填满的位置
{
    int pos;//插入位置
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
        p += cursize - 1;//定位最后一个位置（顺序表的优点）

        for (int i = cursize; i >= pos; i--)//从cursize往前移
        {

            *(p + 1) = *p;
            if (p != Initial)//防止指针左越界
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
        p = Initial + pos;//删的下一个
        for (int i = pos; i <= cursize; i++)//往前覆盖,i显示被覆盖位置
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
    scanf("%s", nam);//名字

    node* p = Initial;
    int i = 1;//同步
    while (i <= cursize && (strcmp(nam, p->name) != 0))//不相等
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
    scanf("%s", no);//学号

    node* p = Initial;
    int i = 1;//同步
    while (i <= cursize && (strcmp(no, p->num) != 0))//不相等
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
        char order[10] = { '\0' };//若放在外面可能新输入的没覆盖掉旧输入导致错误
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
    node* Initial = (node*)malloc(sizeof(node) * (n + 2));//初始位置(多两个，防止增（1个），删（2个）的时候没东西移/越界）
    if (!Initial)
        exit(0);

    initial(Initial, n);
    size = cursize = n;

    process(Initial, size, cursize);

    return 0;
}

*/
