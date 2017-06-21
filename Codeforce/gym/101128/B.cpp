#include <bits/stdc++.h>
using namespace std;
#define MAXN 60
#define ALFA ('z'-'a'+1)
#define other(x) ((x + ALFA) % (2*ALFA))

int force[MAXN], vet[MAXN];
vector<int> adj[MAXN];
bool vis[MAXN];

bool dfs(int u, int val){
	if (vet[u] == -val){
		return false;
	}
	vet[u] = val;
	if (vis[u]) return true;
	vis[u] = true;
	for(int i=0, v; i<(int)adj[u].size(); i++){
		v = adj[u][i];
		if (!dfs(v, -val)) return false;
	}
	return true;
}

bool solve(int a, int b, int c){
	if (force[a] == 1 || force[other(a)] == 1) return false;
	if (force[b] == 1 || force[other(b)] == 1) return false;
	if (force[c] == 1 || force[other(c)] == 1) return false;
	for(int i=0; i<2*ALFA; i++) vet[i] = force[i];
	vet[a] = vet[other(a)] = -1;
	vet[b] = vet[other(b)] = -1;
	vet[c] = vet[other(c)] = -1;
	for(int u=0, v; u<ALFA; u++){
		if (u != a && u != b && u != c){
			v = other(u);
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
	}
	bool possible = true;
	memset(&vis, false, sizeof vis);
	for(int i=0; i<2*ALFA && possible; i++){
		if (!vis[i] && vet[i]!=0 && !dfs(i, vet[i])) possible = false;
	}
	for(int i=0; i<2*ALFA && possible; i++){
		if (!vis[i] && vet[i]==0 && !dfs(i, 1)) possible = false;
	}
	for(int u=0, v; u<ALFA; u++){
		if (u != a && u != b && u != c){
			v = other(u);
			adj[u].pop_back();
			adj[v].pop_back();
		}
	}
	return possible;
}

int main()
{
	int i, a, N;
	char u, v;
	scanf("%d", &N);
	memset(&force, 0, sizeof force);
	while(N-->0){
		scanf(" %c %c %d %d", &u, &v, &i, &a);
		u -= 'A';
		v -= 'A';
		if (i == 2){
			u += ALFA;
			v += ALFA;
		}
		if (a == 0){
			if (force[u] == 1 || force[v] == 1){ printf("0\n"); return 0; }
			force[u] = force[v] = -1;
		}
		else if (a == 1){
			adj[u].push_back(v);
			adj[v].push_back(u);
		}
		else if (a == 2){
			if (force[u] == -1 || force[v] == -1){ printf("0\n"); return 0; }
			if (force[other(u)] == 1 || force[other(v)] == 1){ printf("0\n"); return 0; }
			force[u] = force[v] = 1;
			force[other(u)] = force[other(v)] = -1;
		}
	}
	int ans = 0;
	for(int i=0; i<ALFA; i++){
		for(int j=0; j<i; j++){
			for(int k=0; k<j; k++){
				if (solve(i, j, k)) ans++;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}