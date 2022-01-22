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
    student* stu = (student*)malloc(n * sizeof(student));//动态申请内存
    if (stu == NULL) {
        cout << "动态内存申请失败" << endl;
        exit(-1);
    }
    cout << "请依次输入" << n << "个学生信息" << endl;
    student* p = stu;
    for (int i = 1; i <= n; i++) {//读入学生信息
        scanf("%s%s%lf", p->no, p->name, &(p->score));
        p++;
    }
    return stu;
}

void dispaly(student* stu, int n)
{
    student* p = stu;
    for (int i = 1; i <= n; i++) {//输出学生信息
        cout << "第" << i << "名同学的学号是" << p->no << ",姓名是" << p->name << ",成绩是" << p->score << endl;
        p++;
    }
    return;
}

bool ListInsert(student*& stu, int pos, char no1[8], char name1[20], double score1, int& n)
{
    if (pos<1 || pos>n + 1) {
        cout << "位置非法" << endl;
        return false;
    }
    stu = (student*)realloc(stu, (n + 1) * sizeof(student));
    if (stu == NULL) {
        cout << "动态内存申请失败" << endl;
        exit(-1);
    }
    student* q = &stu[pos - 1];//插入的位置
    for (student* p = &stu[n - 1]; p >= q; p--) {//依次向后移位
        strcpy((p + 1)->no, p->no);
        strcpy((p + 1)->name, p->name);
        (p + 1)->score = p->score;
    }
    strcpy(q->no, no1);//插入的元素
    strcpy(q->name, name1);
    q->score = score1;
    n++;
    return true;
}

bool ListDelete(student*& stu, int id, int& n)
{
    if (id<1 || id>n) {
        cout << "位置非法" << endl;
        return false;
    }
    student* p = &stu[id - 1];//删除的位置
    student* q = &stu[n - 1];//表尾
    for (p++; p <= q; p++) {//依次向前一位
        strcpy((p - 1)->no, p->no);
        strcpy((p - 1)->name, p->name);
        (p - 1)->score = p->score;
    }
    stu = (student*)realloc(stu, (n - 1) * sizeof(student));//重新申请空间
    n--;
    return true;
}

int ListSearchName(student*& stu, char name1[20], int& n)
{
    student* p = stu;
    for (int i = 1; i <= n; i++) {
        if (!strcmp(p->name, name1)) {//遍历按名字查找
            cout << "该学生的学号是" << p->no << ",成绩是" << p->score << endl;
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
    cout << "该学生的学号是" << (p + pos - 1)->no << ",姓名是" << (p + pos - 1)->name << ",成绩是" << (p + pos - 1)->score << endl;
}


int ListSearchNo(student*& stu, char no1[8], int& n)
{
    student* p = stu;
    for (int i = 1; i <= n; i++) {
        if (!strcmp(p->no, no1)) {//遍历按学号查找
            cout << "该学生的姓名是" << p->name << ",成绩是" << p->score << endl;
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
    cout << "学生总人数为" << n << endl;
}

bool Delete_by_info(student*& stu, char name1[20], char no1[8], double score1, int& n)
{
    student* p = stu;//表头位置
    student* q = &stu[n - 1];//表尾位置
    bool flag = false;//是否找到该学生
    for (; p <= q; p++) {
        if (!strcmp(p->name, name1) && !strcmp(p->no, no1) && p->score == score1) {//遍历查找
            for (p++; p <= q; p++) {//被删除元素之后的元素都向前移一位
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
        cout << "该学生信息错误" << endl;
        return false;
    }
}

void ListUnique(student*& stu, int& n)
{
    student* p = stu;
    for (int i = 2; i <= n; i++) {//插入排序
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
    int n1 = n;//去重过程中n将变化，先保存n
    int samenum = 0;
    for (int i = 1; i <= n1 - 1; i++) {
        if (!strcmp((p + i - 1 - samenum)->no, (p + i - samenum)->no)) {
            student* q = p + i - 1 - samenum;//删除元素后现在正在检查的元素的位置
            student* r = p + n1 - 1 - samenum;//删除元素后最后一个元素位置
            for (q++; q <= r; q++) {//向前移动一位
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
