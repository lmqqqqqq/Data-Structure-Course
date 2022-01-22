#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstdio>
#include<algorithm>
using namespace std;

struct node {
	int coef; //ϵ��
	int expn; //ָ��
	node* next;
};

node* creat_list(int n) { //������������
	node* head, * pre ,*q;
	head = new node;
	head->next = NULL;	
	int coef, expn;
	while (n--) {
		pre = head;
		q = head->next;
		scanf("%d%d", &coef, &expn);
		node* tmp = new node; //������ʱ���
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
	node* ha, * hb; //Ϊ�˷�ֹ�޸�ָ�뱾���ֵ��ʹ�ô���ָ������ɲ�����Ҳ�����αꡣ
	fans = new node;
	ans = fans; //ans ��Ϊfans ���α�
	ha = a->next;
	hb = b->next;
	while (ha && hb) {
		node* tmp = new node; 
		if (ha->expn < hb->expn) { //ÿ�ΰ�ָ��	��С�ļ�������fans
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
			int mulOfcoef = (ha->coef) + (hb->coef); //���ָ����ͬ���Ͱ�ϵ����͡�
			if (mulOfcoef != 0) {
				tmp->coef = mulOfcoef;
				tmp->expn = ha->expn;
				ans->next = tmp;
				ans = tmp;
			}
			ha = ha->next; //�ƶ����αꡱ
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
		hb = b->next; //�� b �ĵ�һ�ʼ�ˣ�
		while (hb != NULL) {
			node* ltmp = new node;
			ltmp->expn = ha->expn + hb->expn; //ָ����ӣ�ϵ�����
			ltmp->coef = ha->coef * hb->coef;
			hb = hb->next;
			ans->next = ltmp;
			ans = ltmp;
		}
		ans->next = NULL;
		fans = add_list(fans, tmp); //���˷��ֽ��һ�δεļӷ�
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
