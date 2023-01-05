#include <bits/stdc++.h>
#define INF (1<<30)
#define MAXN 1009
using namespace std;

vector<int> adjU[MAXN];
int pairU[MAXN], pairV[MAXN], dist[MAXN];
int m, n;
///Vértices enumerados de 1 a m em U e de 1 a n em V!!!!
bool bfs()
{
    queue<int> q;
    for (int u=1; u<=m; u++){
        if (pairU[u]==0) {
            dist[u] = 0;
            q.push(u);
        }
        else dist[u] = INF;
    }
    dist[0] = INF;
    int u, v;
    while (!q.empty()){
        u = q.front(); q.pop();
        if (dist[u] < dist[0]){
            for (int i=0; i<(int)adjU[u].size(); ++i) {
                v = adjU[u][i];
                if (dist[pairV[v]] == INF){
                    dist[pairV[v]] = dist[u] + 1;
                    q.push(pairV[v]);
                }
            }
        }
    }
    return (dist[0] != INF);
}

bool dfs(int u)
{
    if (u == 0) return true;
    int v;
    for (int i=0; i!=(int)adjU[u].size(); ++i){
        v = adjU[u][i];
        if (dist[pairV[v]] == dist[u]+1){
            if (dfs(pairV[v])){
                pairV[v] = u; pairU[u] = v;
                return true;
            }
        }
    }
    dist[u] = INF;
    return false;
}

//O(E*sqrt(V))
int hopcroftKarp()
{
    memset(&pairU, 0, sizeof pairU);
    memset(&pairV, 0, sizeof pairV);
    int result = 0;
    while (bfs()){
        for (int u=1; u<=m; u++){
            if (pairU[u]==0 && dfs(u))
                result++;
        }
    }
    return result;
}

int main()
{
	int T, N, ans;
	string strA, strB;
	map<string, int> mpA, mpB;
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <= T; caseNo++) {
		scanf("%d", &N);
		mpA.clear(); mpB.clear();
		m = n = 0;
		for(int i=0; i<N; i++){
			cin >> strA >> strB;
			if (!mpA.count(strA)){
				mpA[strA] = ++m;
				adjU[m].clear();
			}
			if (!mpB.count(strB)){
				mpB[strB] = ++n;
			}
			adjU[mpA[strA]].push_back(mpB[strB]);
		}
		int mf = hopcroftKarp();
		for(int i=1; i<=m; i++){
			if (pairU[i] == 0) mf++;
		}
		for(int i=1; i<=n; i++){
			if (pairV[i] == 0) mf++;
		}
		ans = N - mf;
		printf("Case #%d: %d\n", caseNo, ans);
	}
	return 0;
}