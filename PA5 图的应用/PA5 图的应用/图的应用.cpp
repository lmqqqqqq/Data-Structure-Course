#include<iostream>
using namespace std;

#define MAX_VERTEX_NUM 100

typedef enum { DG, DN, UDG, UDN } GraphKind;

typedef int AdjMatrix[MAX_VERTEX_NUM][MAX_VERTEX_NUM];

typedef struct {
	int vexs[MAX_VERTEX_NUM];
	AdjMatrix arcs;
	int vexnum;
	int arcnum;
	GraphKind kind;
}MGraph;

int num, no=1;

void DFS_draw(MGraph G, int* s, int i)
{
	if (no == 1 && i != 1) {//递归终止条件
		return;
	}
	s[no] = i;//保存路径
	no++;//开始寻找下一段路径
	for (int k = 1; k <= G.vexnum; k++) {
		if (G.arcs[i][k] != 0) {
			G.arcs[i][k] = 0;
			G.arcs[k][i] = 0;
			DFS_draw(G, s, k);//搜索下一个点
			G.arcs[i][k] = 1;//回退
			G.arcs[k][i] = 1;
		}
	}
	if (no == G.arcnum + 1) {//输出路径
		cout << "第" << ++num << "种走法" << endl;
		for (int k = 1; k <= G.arcnum; k++) {
			cout << k << ':' << s[k] << "->" << s[k + 1] << endl;
		}
		cout << endl;
	}
	no--;//回退
	return;
}

int main()
{
	MGraph G;
	cout << "请输入顶点数和边数" << endl;
	cin >> G.vexnum >> G.arcnum;
	cout << "请输入边之间的连接" << endl;
	for (int i = 1; i <= G.vexnum; i++) {
		for (int j = 1; j <= G.vexnum; j++) {
			G.arcs[i][j] = 0;
		}
	}
	for (int i = 1; i <= G.arcnum; i++) {
		int m, n;
		cin >> m >> n;
		G.arcs[m][n] = 1;
		G.arcs[n][m] = 1;
	}
	int s[MAX_VERTEX_NUM] = { 0 };
	for (int i = 1; i <= G.vexnum; i++) {
		DFS_draw(G, s, i);
	}
	return 0;
}