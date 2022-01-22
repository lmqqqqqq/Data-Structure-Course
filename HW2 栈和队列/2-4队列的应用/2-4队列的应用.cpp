#include<iostream>
using namespace std;

bool dfs(bool* map, const int row, const int col, int loc)
{
    if (map[loc] != true) {
        return false;
    }
    map[loc] = false;
    bool bo = false;

    int x = loc / col, y = loc % col, dir = 0;
    if (x > 0){
        bo |= dfs(map, row, col, loc - col);
        dir++;
    }
    if (x < row - 1){
        bo |= dfs(map, row, col, loc + col);
        dir++;
    }
    if (y > 0){
        bo |= dfs(map, row, col, loc - 1);
        dir++;
    }
    if (y < col - 1){
        bo |= dfs(map, row, col, loc + 1);
        dir++;
    }
    bo |= (dir == 4);
    return bo; 
}

int solution(bool* map, int row, int col)
{
    int ans = 0;
    for (int i = 0; i < row * col; i++) {
        if (map[i] == 1 && dfs(map, row, col, i) == true) {
            ans++;
        }
    }
    return ans;
}

int main()
{
	ios::sync_with_stdio(false), cin.tie(0), cout.tie(0);
	int n, m;
	cin >> n >> m;
	bool map[1000005];
	for (int i = 0; i < n * m; i++) {
		cin >> map[i];
	}
    int ans;
    ans=solution(map, n, m);
    cout << ans << endl;

}