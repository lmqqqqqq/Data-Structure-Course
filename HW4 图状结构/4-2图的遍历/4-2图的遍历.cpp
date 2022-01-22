#include<iostream>
#include<queue>
using namespace std;

#define MAX_VERTEX_NUM 10000

typedef enum { DG, DN, UDG, UDN } GraphKind;

typedef struct ArcNode {//边结点
	int adjvex;//当前结点
	ArcNode* nextarc;//下一结点
	int info;//权重
}ArcNode;

typedef struct VNode {//表头结点
	int data;
	ArcNode* firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;//邻接表
	int vexnum;
	int arcnum;
	GraphKind kind;
}ALGraph;

bool visited[MAX_VERTEX_NUM];

bool CreateUDG(ALGraph& g)
{
	cin >> g.vexnum >> g.arcnum;
	for (int i = 0; i < g.vexnum; i++) {//构造顶点向量
		g.vertices[i].data = i;
		g.vertices[i].firstarc = NULL;
	}
	for (int k = 0; k < g.arcnum; k++) {//构造邻接矩阵
		int v1, v2;
		cin >> v1 >> v2;
		ArcNode* p=NULL;
		if (g.vertices[v1].firstarc == NULL) {
			p = (ArcNode*)malloc(sizeof(ArcNode));
			g.vertices[v1].firstarc = p;
			p->adjvex = v2;
			p->nextarc = NULL;
		}
		else {
			p = g.vertices[v1].firstarc;
			while (p->nextarc) {
				p = p->nextarc;
			}
			p->nextarc = (ArcNode*)malloc(sizeof(ArcNode));
			p->nextarc->adjvex = v2;
			p->nextarc->nextarc = NULL;
		}
		ArcNode* q = NULL;
		if (g.vertices[v2].firstarc == NULL) {
			q = (ArcNode*)malloc(sizeof(ArcNode));
			g.vertices[v2].firstarc = q;
			q->adjvex = v1;
			q->nextarc = NULL;
		}
		else {
			q = g.vertices[v2].firstarc;
			while (q->nextarc) {
				q = q->nextarc;
			}
			q->nextarc= (ArcNode*)malloc(sizeof(ArcNode));
			q->nextarc->adjvex = v1;
			q->nextarc->nextarc = NULL;
		}	
	}
	return true;
}

void DFS(ALGraph g, int v)
{
	cout << g.vertices[v].data;
	visited[v] = true;
	ArcNode* p = g.vertices[v].firstarc;
	while (p) {
		if (!visited[p->adjvex]) {
			cout << ' ';
			DFS(g, p->adjvex);
		}
		p = p->nextarc;
	}
}

void DFSTraverse(ALGraph g)
{
	for (int i = 0; i < g.vexnum; i++) {
		visited[i] = 0;
	}
	for (int i = 0; i < g.vexnum; i++) {
		if (!visited[i]) {
			cout << '{';
			DFS(g, i);
			cout << '}';
		}
	}
}

void BFS(ALGraph g, int v)
{
	queue<int> Q;
	cout << g.vertices[v].data;
	visited[v] = true;
	Q.push(v);
	while (!Q.empty()) {
		int k = Q.front();
		Q.pop();
		ArcNode* p = g.vertices[k].firstarc;
		while (p) {
			if (!visited[p->adjvex]) {
				cout << ' ' << g.vertices[p->adjvex].data;
				visited[p->adjvex] = true;
				Q.push(p->adjvex);
			}
			p = p->nextarc;
		}
	}
}

void BFSTraverse(ALGraph g)
{
	for (int i = 0; i < g.vexnum; i++) {
		visited[i] = 0;
	}
	for (int i = 0; i < g.vexnum; i++) {
		if (!visited[i]) {
			cout << '{';
			BFS(g, i);
			cout << '}';
		}
	}
}

int main()
{
	ALGraph g;
	CreateUDG(g);
	DFSTraverse(g);
	cout << endl;
	BFSTraverse(g);
	return 0;
}