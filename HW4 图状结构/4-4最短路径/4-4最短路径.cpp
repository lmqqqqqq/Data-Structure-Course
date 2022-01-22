#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<limits.h>
using namespace std;

#define MAX_VERTEX_NUM 100005

struct Edge {//��
	int to;//����ĵ�
	int weight;//Ȩ��
};
vector<Edge> G[MAX_VERTEX_NUM];

struct Node {
	int no;
	int dis;//��ǰvo��no�����·��
	bool operator < (const Node& a) const {//�������ȶ������д���
		return dis > a.dis;
	}
};

int D[MAX_VERTEX_NUM];//��ŵ�ǰv0��ÿ��������·��
bool final[MAX_VERTEX_NUM];//���·���Ƿ��ҵ�

int n,m, v0;

void ShortPath_DIJ(int v0)
{
	memset(D, 0x3f, sizeof(D));
	D[v0] = 0;
	priority_queue<Node> Q;
	Q.push(Node{ v0,0 });
	while (!Q.empty()) {
		int k = Q.top().no;
		Q.pop();
		if (final[k]) {
			continue;
		}
		final[k] = true;
		for (int i = 0; i < G[k].size(); i++) {//����vector���±�����0��ʼ
			Edge e = G[k][i];
			if (D[k] + e.weight < D[e.to]) {
				D[e.to] = D[k] + e.weight;
				Q.push(Node{ e.to,D[e.to] });
			}
		}
	}
	return;
}

int main()
{
	cin >> n >> m >> v0;
	for (int i = 1; i <= m; i++) {
		int u, v, w;
		cin >> u >> v >> w;
		G[u].push_back(Edge{ v,w });
		G[v].push_back(Edge{ u,w });
	}
	ShortPath_DIJ(v0);
	for (int i = 1; i <= n; i++) {
		cout << (final[i] ? D[i] : INT_MAX) << ' ';
	}
	return 0;
}


