#include<iostream>
using namespace std;

#define MAX_VERTEX_NUM 50

typedef enum{DG,DN,UDG,UDN} GraphKind;

typedef int AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	char vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum;
	int arcnum;
	GraphKind kind;
}MGraph;

typedef struct ArcNode {//�߽��
	int adjvex;//��ǰ���
	ArcNode* nextarc;//��һ���
	int info;//Ȩ��
}ArcNode;

typedef struct VNode {//��ͷ���
	char data;
	ArcNode* firstarc;
}VNode,AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;//�ڽӱ�
	int vexnum;
	int arcnum;
	GraphKind kind;
}ALGraph;

int choice;

int LocateVex(MGraph G, char v)
{
	for (int i = 0; i < G.vexnum; i++) {
		if (v == G.vexs[i]) {
			return i;
		}
	}
	return -1;
}

int LocateVex(ALGraph g, char v)
{
	for (int i = 0; i < g.vexnum; i++) {
		if (v == g.vertices[i].data) {
			return i;
		}
	}
	return -1;
}

//��������ͼG
bool CreateDG(MGraph& G, ALGraph& g)
{
	cin >> G.vexnum >> G.arcnum;
	g.vexnum = G.vexnum;
	g.arcnum = G.arcnum;
	for (int i = 0; i < G.vexnum; i++) {//���춥������
		cin >> G.vexs[i];
		g.vertices[i].data = G.vexs[i];
		g.vertices[i].firstarc = NULL;
	}
	for (int i = 0; i < G.vexnum; i++) {//��ʼ���ڽӾ���
		for (int j = 0; j < G.vexnum; j++) {
			G.arcs[i][j] = 0;
		}
	}
	for (int k = 0; k < G.arcnum; k++) {//�����ڽӾ���
		char v1, v2;
		cin >> v1 >> v2;
		int i = LocateVex(G, v1);//ȷ��v1��v2��G�е�λ��
		int j = LocateVex(G, v2);
		int I = LocateVex(g, v1);//ȷ��v1��v2��g�е�λ��
		int J = LocateVex(g, v2);
		G.arcs[i][j] = 1;
		ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = J;//ͷ�巨
		p->nextarc = g.vertices[I].firstarc;
		g.vertices[I].firstarc = p;
	}
	return true;
}

//����������G
bool CreateDN(MGraph& G, ALGraph& g)
{
	cin >> G.vexnum >> G.arcnum;
	g.vexnum = G.vexnum;
	g.arcnum = G.arcnum;
	for (int i = 0; i < G.vexnum; i++) {//���춥������
		cin >> G.vexs[i];
		g.vertices[i].data=G.vexs[i];
		g.vertices[i].firstarc = NULL;
	}
	for (int i = 0; i < G.vexnum; i++) {//��ʼ���ڽӾ���
		for (int j = 0; j < G.vexnum; j++) {
			G.arcs[i][j] = 0;
		}
	}
	for (int k = 0; k < G.arcnum; k++) {//�����ڽӾ���
		char v1, v2;
		int w;
		cin >> v1 >> v2 >>w;
		int i = LocateVex(G, v1);//ȷ��v1��v2��G�е�λ��
		int j = LocateVex(G, v2);
		int I = LocateVex(g, v1);//ȷ��v1��v2��g�е�λ��
		int J = LocateVex(g, v2);
		G.arcs[i][j] = w;
		ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = J;//ͷ�巨
		p->nextarc = g.vertices[I].firstarc;
		p->info = w;
		g.vertices[I].firstarc = p;
	}
	return true;
}

//��������ͼG
bool CreateUDG(MGraph& G, ALGraph& g)
{
	cin >> G.vexnum >> G.arcnum;
	g.vexnum = G.vexnum;
	g.arcnum = G.arcnum;
	for (int i = 0; i < G.vexnum; i++) {//���춥������
		cin >> G.vexs[i];
		g.vertices[i].data = G.vexs[i];
		g.vertices[i].firstarc = NULL;
	}
	for (int i = 0; i < G.vexnum; i++) {//��ʼ���ڽӾ���
		for (int j = 0; j < G.vexnum; j++) {
			G.arcs[i][j] = 0;
		}
	}
	for (int k = 0; k < G.arcnum; k++) {//�����ڽӾ���
		char v1, v2;
		cin >> v1 >> v2;
		int i = LocateVex(G, v1);//ȷ��v1��v2��G�е�λ��
		int j = LocateVex(G, v2);
		int I = LocateVex(g, v1);//ȷ��v1��v2��g�е�λ��
		int J = LocateVex(g, v2);
		G.arcs[i][j] = 1;
		G.arcs[j][i] = 1;//�öԳƻ�
		ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = J;//ͷ�巨
		p->nextarc = g.vertices[I].firstarc;
		g.vertices[I].firstarc = p;
		ArcNode* l = (ArcNode*)malloc(sizeof(ArcNode));
		l->adjvex = I;
		l->nextarc = g.vertices[J].firstarc;
		g.vertices[J].firstarc = l;
	}
	return true;
}

//����������G
bool CreateUDN(MGraph& G, ALGraph& g)
{
	cin >> G.vexnum >> G.arcnum;
	g.vexnum = G.vexnum;
	g.arcnum = G.arcnum;
	for (int i = 0; i < G.vexnum; i++) {//���춥������
		cin >> G.vexs[i];
		g.vertices[i].data = G.vexs[i];
		g.vertices[i].firstarc = NULL;
	}
	for (int i = 0; i < G.vexnum; i++) {//��ʼ���ڽӾ���
		for (int j = 0; j < G.vexnum; j++) {
			G.arcs[i][j] = 0;
		}
	}
	for (int k = 0; k < G.arcnum; k++) {//�����ڽӾ���
		char v1, v2;
		int w;
		cin >> v1 >> v2 >> w;
		int i = LocateVex(G, v1);//ȷ��v1��v2��G�е�λ��
		int j = LocateVex(G, v2);
		int I = LocateVex(g, v1);//ȷ��v1��v2��g�е�λ��
		int J = LocateVex(g, v2);
		G.arcs[i][j] = w;
		G.arcs[j][i] = w;//�öԳƻ�
		ArcNode* p = (ArcNode*)malloc(sizeof(ArcNode));
		p->adjvex = J;//ͷ�巨
		p->nextarc = g.vertices[I].firstarc;
		p->info = w;
		g.vertices[I].firstarc = p;
		ArcNode* l= (ArcNode*)malloc(sizeof(ArcNode));
		l->adjvex = I;
		l ->nextarc = g.vertices[J].firstarc;
		l->info = w;
		g.vertices[J].firstarc = l;
	}
	return true;
}

bool CreateGraph(MGraph& G, ALGraph& g)
{
	
	cin >> choice;
	switch (choice - 1) {
		case DG:
			CreateDG(G,g);
			break;
		case DN:
			CreateDN(G,g);
			break;
		case UDG:
			CreateUDG(G,g);
			break;
		case UDN:
			CreateUDN(G,g);
			break;
	}
	return true;
}

void printVertex(MGraph G)
{
	for (int i = 0; i < G.vexnum; i++) {
		cout << G.vexs[i] << ' ';
	}
	cout << endl;
}

void printMGraph(MGraph G)
{
	for (int i = 0; i < G.vexnum; i++) {
		for (int j = 0; j < G.vexnum; j++) {
			printf("%4d", G.arcs[i][j]);
		}
		cout << endl;
	}
	return;
}

void printAlGraph1(ALGraph g)
{
	for (int i = 0; i < g.vexnum; i++) {
		cout << g.vertices[i].data<<"-->";
		if (g.vertices[i].firstarc != NULL) {
			ArcNode* p = g.vertices[i].firstarc;
			while (p != NULL) {
				cout << p->adjvex << ' ';
				p = p->nextarc;
			}
		}
		cout << endl;
	}
	return;
}

void printAlGraph2(ALGraph g)
{
	for (int i = 0; i < g.vexnum; i++) {
		cout << g.vertices[i].data << "-->";
		if (g.vertices[i].firstarc != NULL) {
			ArcNode* p = g.vertices[i].firstarc;
			while (p != NULL) {
				cout << p->adjvex << ','<<p->info<<' ';
				p = p->nextarc;
			}
		}
		cout << endl;
	}
	return;
}

int main()
{
	MGraph G;
	ALGraph g;
	CreateGraph(G, g);
	printVertex(G);
	printMGraph(G);
	if (choice == 2 || choice == 4) {
		printAlGraph2(g);
	}
	else {
		printAlGraph1(g);
	}
	return 0;
}