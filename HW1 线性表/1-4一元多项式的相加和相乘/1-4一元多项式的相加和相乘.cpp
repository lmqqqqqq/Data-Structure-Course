#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct node {
	int coef; //系数
	int expn; //指数
	node* next;
};

node* creat_list(int n) { //读入链表并排序
	node* head, * pre ,*q;
	head = new node;
	head->next = NULL;	
	int coef, expn;
	while (n--) {
		pre = head;
		q = head->next;
		scanf("%d%d", &coef, &expn);
		node* tmp = new node; //创建临时结点
		tmp->coef = coef;
		tmp->expn = expn;
		while (q && q->expn < tmp->expn) {
			pre = q;
			q = q->next;
		}
		tmp->next = q;
		pre->next = tmp;		
	}
	return head;
}

node* add_list(node* a, node* b) {
	node* fans, * ans;
	node* ha, * hb; //为了防止修改指针本身的值，使用代理指针来完成操作，也就是游标。
	fans = new node;
	ans = fans; //ans 作为fans 的游标
	ha = a->next;
	hb = b->next;
	while (ha && hb) {
		node* tmp = new node; 
		if (ha->expn < hb->expn) { //每次把指数	较小的加入链表fans
			tmp->coef = ha->coef;
			tmp->expn = ha->expn;
			ans->next = tmp;
			ans = tmp;
			ha = ha->next;
		}
		else if (ha->expn > hb->expn) {
			tmp->coef = hb->coef;
			tmp->expn = hb->expn;
			ans->next = tmp;
			ans = tmp;
			hb = hb->next;
		}
		else {
			int mulOfcoef = (ha->coef) + (hb->coef); //如果指数相同，就把系数求和。
			if (mulOfcoef != 0) {
				tmp->coef = mulOfcoef;
				tmp->expn = ha->expn;
				ans->next = tmp;
				ans = tmp;
			}
			ha = ha->next; //移动“游标”
			hb = hb->next;
		}
	}
	while (ha) {
		node* tmp = new node;
		tmp->coef = ha->coef;
		tmp->expn = ha->expn;
		ans->next = tmp;
		ans = tmp;
		ha = ha->next;
	}
	while (hb) {
		node* tmp = new node;
		tmp->coef = hb->coef;
		tmp->expn = hb->expn;
		ans->next = tmp;
		ans = tmp;
		hb = hb->next;
	}
	ans->next = NULL; 
	return fans;
}

node* multi_list(node* a, node* b) {
	node* ha, * hb;
	node* ans, * fans;
	ha = a->next;
	hb = b->next;
	fans = new node;
	if (ha == NULL || hb == NULL) {
		return fans;
	}
	node* tmp;
	while (ha != NULL) {
		tmp = new node;
		ans = tmp;
		hb = b->next; //从 b 的第一项开始乘；
		while (hb != NULL) {
			node* ltmp = new node;
			ltmp->expn = ha->expn + hb->expn; //指数相加，系数相乘
			ltmp->coef = ha->coef * hb->coef;
			hb = hb->next;
			ans->next = ltmp;
			ans = ltmp;
		}
		ans->next = NULL;
		fans = add_list(fans, tmp); //将乘法分解成一次次的加法
		ha = ha->next;
	}
	return fans;
}

void print_list(node* l) {
	node* hc;
	hc = l->next; 
	if (hc == NULL) {
		return;
	}
	while (hc != NULL) {
		printf("%d %d ", hc->coef, hc->expn);
		hc = hc->next;
	}
}

int main() {
	int m;
	scanf("%d", &m);
	node* a = creat_list(m);
	int n;
	scanf("%d", &n);
	node* b = creat_list(n);
	node* c = add_list(a, b);
	node* d = multi_list(a, b);
	int choice;
	scanf("%d", &choice);
	if (choice == 0) {
		print_list(c);
	}
	else if (choice == 1) {
		print_list(d);
	}
	else {
		print_list(c);
		printf("\n");
		print_list(d);
	}
	return 0;
}
