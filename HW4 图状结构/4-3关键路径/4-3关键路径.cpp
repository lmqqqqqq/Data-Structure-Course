#include<iostream>
#include<stack>
using namespace std;
#define MAX_VERTEX_NUM 100000
typedef enum { DG, DN, UDG, UDN } GraphKind;

typedef struct ArcNode {//�߽��
	int adjvex;//��ǰ���
	ArcNode* nextarc;//��һ���
	int info=-1;//Ȩ��
}ArcNode;

typedef struct VNode {//��ͷ���
	int data;
	int indegree;//���
	ArcNode* firstarc;
}VNode, AdjList[MAX_VERTEX_NUM];

typedef struct {
	AdjList vertices;//�ڽӱ�
	int vexnum;
	int arcnum;
	GraphKind kind;
}ALGraph;

int ve[MAX_VERTEX_NUM];
int vl[MAX_VERTEX_NUM];


bool CreateDN(ALGraph& g)
{
	cin >> g.vexnum >> g.arcnum;
	for (int i = 1; i <= g.vexnum; i++) {
		g.vertices[i].data = i;
		g.vertices[i].firstarc = NULL;
		g.vertices[i].indegree = 0;
	}
	for (int k = 0; k < g.arcnum; k++) {//�����ڽӱ�
		int u,v,w;
		cin >> u >> v >> w;
		g.vertices[v].indegree++;
		ArcNode* p = NULL;
		if (g.vertices[u].firstarc == NULL) {
			p = (ArcNode*)malloc(sizeof(ArcNode));
			g.vertices[u].firstarc = p;
			p->adjvex = v;
			p->info = w;
			p->nextarc = NULL;
		}
		else {
			p = g.vertices[u].firstarc;
			while (p->nextarc) {
				p = p->nextarc;
			}
			if (p->adjvex == v) {
				if (w > p->info) {
					p->info = w;
				}
				g.vertices[v].indegree--;
			}
			else {
				p->nextarc = (ArcNode*)malloc(sizeof(ArcNode));
				p->nextarc->adjvex = v;
				p->nextarc->info = w;
				p->nextarc->nextarc = NULL;
			}
		}
	}
	return true;
}

bool TopologiclaOrder(ALGraph& g, stack<VNode>& T)
{
	int count = 1;
	stack<VNode> S;
	for (int i = 1; i <= g.vexnum; i++) {
		if (g.vertices[i].indegree == 0) {
			S.push(g.vertices[i]);
		}
	}
	while (!S.empty()) {
		VNode tmp = S.top();
		S.pop();
		T.push(tmp);
		count++;
		for (ArcNode* p = tmp.firstarc; p; p = p->nextarc) {
			int k = p->adjvex;//��tmp�����ÿ���ڽӵ���ȼ�1
			if (--g.vertices[k].indegree == 0) {
				S.push(g.vertices[k]);//����ȼ�Ϊ0������ջ
			}
			if (ve[tmp.data] + p->info > ve[k]) {
				ve[k] = ve[tmp.data] + p->info;
			}
		}
	}
	if (count < g.vexnum) {
		return false;//���������л�·
	}
	else {
		return true;
	}
}

bool CriticalPath(ALGraph& g, stack<VNode>& T)
{
	if (!TopologiclaOrder(g, T)) {
		return false;
	}
	int max = 0;
	for (int i = 1; i <= g.vexnum; i++) {
		if (ve[i] >= max) {
			max = ve[i];
		}
	}
	for (int i = 1; i <= g.vexnum; i++) {
		vl[i] = max;//��ʼ�������¼�����ٷ���ʱ��
	}
	cout << max << endl;
	while (!T.empty()) {//������������������vlֵ
		VNode tmp = T.top();
		T.pop();
		for (ArcNode* p = tmp.firstarc; p; p = p->nextarc) {
			int k = p->adjvex;
			if (vl[k] - p->info < vl[tmp.data]) {
				vl[tmp.data] = vl[k] - p->info;
			}
		}
	}
	for (int i = 1; i <= g.vexnum; i++) {//��ؼ�·��
		for (ArcNode* p = g.vertices[i].firstarc; p; p = p->nextarc) {
			int k = p->adjvex;
			int ee = ve[i];
			int el = vl[k] - p->info;
			if (ee == el) {
				cout << i << "->" << k << endl;
			}
		}
	}
	return true;
}

int main()
{
	ALGraph g;
	stack<VNode> T;
	CreateDN(g);
	if (!TopologiclaOrder(g, T)) {
		cout << 0<<endl;
	}
	else {
		CriticalPath(g, T);
	}
	return 0;
}