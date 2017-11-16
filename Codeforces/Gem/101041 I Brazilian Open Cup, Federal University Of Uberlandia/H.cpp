#include <stdio.h>
#include <vector>
#include <string.h>
using namespace std;

int bi, bj;
vector<vector<int> > viz;
bool visited[1000];

bool dfs(int ori, int dest) {
	visited[ori] = true;
	if (ori == dest) return true;
	for (int i = 0; i < viz[ori].size(); i++) {
		if (ori == bi && i == bj) continue;
		int v = viz[ori][i];
		
		if (visited[v]) continue;
		if (dfs(v, dest)) return true;
	}
	
	return false;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	viz.resize(n+5);
	for (int i = 0; i < m; i++) {
		int a, b;
		scanf("%d %d", &a, &b);
		a--; b--;
		viz[a].push_back(b);
	}
	
	int ori, dest;
	scanf("%d %d", &ori, &dest);
	ori--;
	dest--;
	
	bool ok = true;
	for (int i = 0; i < n && ok; i++) {
		for (int j = 0; j < (int)viz[i].size(); j++) {
			bi = i; bj = j;
			memset(visited, 0, sizeof(visited));
			if(!dfs(ori, dest)) {
				ok = false;
				break;
			}
		}
	}
	
	if (ok) printf("0\n");
	else printf("1\n");
}