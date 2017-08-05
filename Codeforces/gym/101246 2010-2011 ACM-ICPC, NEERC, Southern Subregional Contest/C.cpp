#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

vector<int> adjU[MAXN], adjV[MAXN];
int pairU[MAXN], pairV[MAXN];
bool vis[MAXN];
int m, n;
///Vértices enumerados de 1 a m em U e de 1 a n em V!!!!

bool dfs(int u)
{
    vis[u] = true;
    if (u == 0) return true;
    int v;
    for (int i=0; i!=(int)adjU[u].size(); ++i){
        v = adjU[u][i];
        if (!vis[pairV[v]] && dfs(pairV[v])){
            pairV[v] = u; pairU[u] = v;
            return true;
        }
    }
    return false;
}

//O(E*V)
int hungarian()
{
    memset(&pairU, 0, sizeof pairU);
    memset(&pairV, 0, sizeof pairV);
    int result = 0;
    for (int u = 1; u <= m; u++){
        memset(&vis, false, sizeof vis);
        if (pairU[u]==0 && dfs(u))
            result++;
    }
    return result;
}

bool visU[MAXN], visV[MAXN], elU[MAXN], elV[MAXN];

int bfs(int mm){
	memset(&visU, false, sizeof visU);
	memset(&visV, false, sizeof visV);
	memset(&elU, false, sizeof elU);
	memset(&elU, false, sizeof elU);
	for(int u=1; u<=m; u++){
		if (pairU[u] > 0 || visU[u]) continue;
		elU[u] = false;
		visU[u] = true;
		printf("u=%d\n", u);
		for(int i=0; i<(int)adjU[u].size(); i++) {
			int v = adjU[u][i];
			printf("edge %d-%d\n", u, v);
			if (visV[v]) continue;
			printf("v=%d must be bombed\n", v);
			visV[v] = true;
			elV[v] = true;
		}
	}
	for(int v=1; v<=n; v++){
		if (pairV[v] > 0 || visV[v]) continue;
		elV[v] = false;
		visV[v] = true;
		for(int i=0; i<(int)adjV[v].size(); i++) {
			int u = adjV[v][i];
			if (visU[u]) continue;
			printf("u=%d must be bombed\n", u);
			visU[u] = true;
			elU[u] = true;
		}
	}
	int ansU=0, lU=0, ansV=0, lV=0;
	for(int u=1; u<=m; u++){
		int v = pairU[u];
		if (elU[u]) ansU++;
		else if (v > 0 && !elV[v]) lU++;
		
	}
	for(int v=1; v<=n; v++){
		int u = pairV[v];
		if (elV[v]) ansV++;
		else if (u > 0 && !elU[u]) lV++;
	}
	return min(ansU, ansV) + lU;
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	char c;
	scanf("%d %d", &n, &m);
	for(int i=1; i<=n; i++){
		for(int j=1; j<=m; j++){
			scanf(" %c", &c);
			if (c == '*'){
				adjU[j].push_back(i);
				adjU[i].push_back(j);
			}
		}
	}
	int mm = hungarian();
	for(int u=1; u<=m; u++) {
		if (pairU[u] > 0) printf("pair %d-%d\n", u, pairU[u]);
	}
	printf("%d\n", bfs(mm));
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}