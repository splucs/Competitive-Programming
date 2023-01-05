#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXLOGN 20

vector<int> adjList[MAXN];
int level[MAXN];
int P[MAXN][MAXLOGN], N;

void depthdfs(int u){
	for(int i=0; i<(int)adjList[u].size(); i++){
		int v = adjList[u][i];
		if (v == P[u][0]) continue;
		P[v][0] = u;
		level[v] = 1 + level[u];
		depthdfs(v);
	}
}
void computeP(int root){
	level[root]=0;
	P[root][0]=root;
	depthdfs(root);
	for(int j = 1; j < MAXLOGN; j++)
		for(int i = 1; i <= N; i++) {
			P[i][j] = P[P[i][j-1]][j-1];
		}
}
int LCA(int a, int b){
	if(level[a] > level[b]) swap(a, b);
	int d = level[b] - level[a];
	for(int i=0; i<MAXLOGN; i++){
		if((d & (1<<i)) != 0) b = P[b][i];
	}
	if(a == b) return a;
	for(int i = MAXLOGN-1; i>=0; i--)
		while(P[a][i] != P[b][i]){
			a=P[a][i]; b=P[b][i];
		}
	return P[a][0];
}
int dist(int u, int v){
	return level[u] + level[v] - 2*level[LCA(u, v)] + 1;
}

int solve(int u, int v, int f) {
	int uf = LCA(u, f);
	int vf = LCA(v, f);
	if (uf == vf) return dist(LCA(u, v), f);
	else return dist(uf+vf-LCA(uf, vf), f);
}

int main() {
	int Q, u, v, qy[3];
	scanf("%d %d", &N, &Q);
	for(v=2; v<=N; v++) {
		scanf("%d", &u);
		adjList[u].push_back(v);
	}
	computeP(1);
	while(Q-->0) {
		scanf("%d %d %d", &qy[0], &qy[1], &qy[2]);
		sort(qy, qy+3);
		int ans = 0;
		do {
			ans = max(ans, solve(qy[0], qy[1], qy[2]));
		} while(next_permutation(qy, qy+3));
		printf("%d\n", ans);
	}
	return 0;
}