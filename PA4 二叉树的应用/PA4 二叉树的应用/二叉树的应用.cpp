#define _CRT_SECURE_NO_WARNINGS
#include<iostream>
#include<cstring>
#include<string>
using namespace std;
#define char_num 127

typedef struct {
	char itself;
	unsigned int weight;
	unsigned int parent, lchild, rchild;
} HTNode, * HuffmanTree;
typedef char** HuffmanCode;
typedef struct
{
	char itself;
	int weight;
}node;

int char_weight[char_num];

//������Ҫ����ѹ�����ַ�
int input(char a)
{
	char_weight[a]++;
	if (char_weight[a] == 1) {//�ж�a�ǲ��ǵ�һ�γ��֣��������
		return 1;
	}
	else {
		return 0;
	}
}

//ѡ������������Һ��ӽ��
void Select(HuffmanTree a, int b, int& c, int& d)
{
	int k = 1;
	HuffmanTree e = a;
	int num1 = 0;
	while (num1 != 2){
		if (e->parent == 0){
			if (num1 == 0){
				c = e - a;
			}
			else{
				d = e - a;
			}
			num1++;
		}
		e++;
	}
	while ((e - a) <= b){
		if (e->parent == 0){
			if (e->weight < (a + c)->weight || e->weight < (a + d)->weight) {
				if ((a + c)->weight <= (a + d)->weight){
					d = e - a;
				}
				else{
					c = d;
					d = e - a;
				}
			}
		}
		e++;
	}
}

//������������
void HuffmanCoding(HuffmanTree& HT, HuffmanCode& HC, node* w, int n)
{
	HuffmanTree p;
	char* cd;
	int i, s1, s2, start;
	unsigned int c, f;
	if (n <= 1) {
		return;
	}     // nΪ�ַ���Ŀ��mΪ�����Ŀ
	int m = 2 * n - 1;
	HT = (HuffmanTree)malloc((m + 1) * sizeof(HTNode));//0�ŵ�Ԫδ��
	p = HT;
	p->weight = -1;
	p->parent = -1;
	p->lchild = -1;
	p->rchild = -1;
	for (p = HT + 1, i = 1; i <= n; ++i, ++p, ++w){
		p->weight = w->weight;
		p->itself = w->itself;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	for (; i <= m; ++i, ++p){
		p->weight = 0;
		p->parent = 0;
		p->lchild = 0;
		p->rchild = 0;
	}
	for (i = n + 1; i <= m; ++i){    //  ���շ�����
		//��HT[1,i-1]��ѡ��parentΪ0��weight��С��������㣬�����Ϊs1��s2
		Select(HT, i - 1, s1, s2); //�ѱ�ѡ����Ľڵ㲻����ѡ
		HT[s1].parent = i;
		HT[s2].parent = i;
		HT[i].lchild = s1;
		HT[i].rchild = s2;
		HT[i].weight = HT[s1].weight + HT[s2].weight;
	}
	HC = (HuffmanCode)malloc((n + 1) * sizeof(char*));//  0�ŵ�Ԫδ��
	cd = (char*)malloc(n * sizeof(char));
	cd[n - 1] = '\0';
	for (i = 1; i <= n; ++i){
		start = n - 1;
		for (c = i, f = HT[c].parent; f != 0; c = f, f = HT[f].parent) {
			if (HT[f].lchild == c) {
				cd[--start] = '0';
			}
			else {
				cd[--start] = '1';
			}
		}
		HC[i] = (char*)malloc((n - start) * sizeof(char));
		strcpy(HC[i], &cd[start]);
	}
	free(cd);
}

int main()
{
	HuffmanTree a = (HuffmanTree)malloc(sizeof(HTNode));
	HuffmanCode c;
	cout << "��������Ҫ������ַ�������$������������1000���ַ���" << endl;
	char k[1000];
	char code_1[1000] = { 0 };
	int num_k = 0;
	int num_l = 0;
	while (num_k < 1000){
		cin >> k[num_k];
		if (k[num_k] == '$') {
			break;
		}
		if (input(k[num_k]) == 1) {
			num_l++;
		}
		num_k++;
	}
	node* w;
	w = (node*)malloc((num_l) * sizeof(node));
	int count1 = 0;//������1
	int count2 = 0;//������2
	while (count1 != num_l){
		if (char_weight[count2] != 0){
			w[count1].itself = count2;
			w[count1].weight = char_weight[count2];
			count1++;
		}
		count2++;
	}
	HuffmanCoding(a, c, w, num_l);
	count1 = 0;
	while (count1 < num_k){
		count2 = 0;
		while (k[count1] != a[count2].itself){
			count2++;
		}
		cout << c[count2] << ' ';//������ѹ����
		strcat(code_1, c[count2]);
		count1++;
	}
	cout << code_1;
	cout << endl;

	cout << "����������" << endl;
	//����
	count2 = 0;
	HuffmanTree temp;
	HuffmanTree temp2;
	temp = &a[2 * num_l - 1];
	temp2 = temp;
	while (code_1[count2] != 0){//�Ƿ������β0
		if (temp2->lchild == 0 && temp2->rchild == 0){
			cout << temp2->itself;
			temp2 = temp;
		}
		else{
			if (code_1[count2] == '0'){
				temp2 = (a + temp2->lchild);
				count2++;
			}
			else if (code_1[count2] == '1'){
				temp2 = (a + temp2->rchild);
				count2++;
			}
		}
	}
	cout << temp2->itself;
	return 0;
}