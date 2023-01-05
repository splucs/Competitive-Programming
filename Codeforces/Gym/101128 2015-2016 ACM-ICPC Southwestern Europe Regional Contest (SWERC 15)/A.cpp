#include <bits/stdc++.h>
using namespace std;
#define MAXN 5009

vector<int> adj[MAXN];
bool Dsum[MAXN][MAXN];
int dep[MAXN], totdep[MAXN], Nsum[MAXN], E;

void BFS(){
	memset(&Dsum, false, sizeof Dsum);
	queue<int> bfs;
	for(int i=0; i<E; i++){
		if (dep[i] == 0){
			bfs.push(i);
		}
	}
	while(!bfs.empty()){
		int u = bfs.front();
		bfs.pop();
		dep[u]--;
		Dsum[u][u] = true;
		for(int i=0; i<(int)adj[u].size(); i++){
			int v = adj[u][i];
			dep[v]--;
			if (dep[v] == 0) bfs.push(v);
			for(int j=0; j<E; j++) Dsum[v][j] = (Dsum[v][j] || Dsum[u][j]);
		}
	}
	memset(&Nsum, 0, sizeof Nsum);
	memset(&totdep, 0, sizeof totdep);
	for(int i=0; i<E; i++){
		for(int j=0; j<E; j++){
			if (Dsum[i][j]){
				Nsum[j]++;
				totdep[i]++;
			}
		}
	}
}

int prom(int K){
	int ans = 0;
	for(int i=0; i<E; i++){
		if (E-Nsum[i] < K) ans++;
	}
	return ans;
}

int notprom(int K){
	int ans = 0;
	for(int i=0; i<E; i++){
		if (totdep[i] > K) ans++;
	}
	return ans;
}

int main()
{
	int A, B, P, u, v;
	scanf("%d %d %d %d", &A, &B, &E, &P);
	memset(&dep, 0, sizeof dep);
	while(P--){
		scanf("%d %d", &u, &v);
		adj[u].push_back(v);
		dep[v]++;
	}
	BFS();
	printf("%d\n", prom(A));
	printf("%d\n", prom(B));
	printf("%d\n", notprom(B));
	return 0;
}