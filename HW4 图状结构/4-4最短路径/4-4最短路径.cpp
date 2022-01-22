#include<iostream>
#include<queue>
#include<vector>
#include<cstring>
#include<limits.h>
using namespace std;

#define MAX_VERTEX_NUM 100005

struct Edge {//边
	int to;//到达的点
	int weight;//权重
};
vector<Edge> G[MAX_VERTEX_NUM];

struct Node {
	int no;
	int dis;//当前vo到no的最短路径
	bool operator < (const Node& a) const {//定义优先队列排列次序
		return dis > a.dis;
	}
};

int D[MAX_VERTEX_NUM];//存放当前v0到每个点的最短路径
bool final[MAX_VERTEX_NUM];//最短路径是否找到

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
		for (int i = 0; i < G[k].size(); i++) {//用了vector，下标必须从0开始
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


