#include <iostream>
#include <cstring>
#include <vector>
#include<iomanip>
#include <queue>
using namespace std;

#define MAXN 2005
#define MAXM  MAXN * 33

vector<int> net[MAXN];
bool vis[MAXN];
int dist[MAXN];
int n, m;

double BFS(int i)
{
    queue<int>q;
    q.push(i);
    int count = 0;
    memset(vis, 0, sizeof(vis));
    vis[i] = true;
    for (int j = 1; j <= n; j++) {
        dist[j] = MAXN;
    }
    dist[i] = 0;
    while (!q.empty())
    {
        int cur = q.front();
        q.pop();
        for (int i = 0; i < net[cur].size(); i++)
        {
            int next = net[cur][i];
            if (!vis[next]){
                q.push(next);
                vis[next] = true;
                dist[next] = dist[cur] + 1;
            }
        }
    }
    for (int i = 1; i <= n; i++) {
        if (vis[i] && dist[i] <= 6) {
            count++;
        }
    }
    return count * 100.0 / n;
}

int main()
{
    cin >> n >> m;
    for (int i = 1; i <= m; i++){
        int u, v;
        cin >> u >> v;
        net[u].push_back(v);
        net[v].push_back(u);
    }
    for (int i = 1; i <= n; i++) {
        cout << i << ": " <<setiosflags(ios::fixed)<< setprecision(2) << BFS(i) << "%" << endl;
    }
    return 0;
}