#include <bits/stdc++.h>
#define INF (1<<30)
#define MAXN 1009
using namespace std;

vector<int> adjU[MAXN];
int pairU[MAXN], pairV[MAXN], dist[MAXN];
int m, n;

//Vértices enumerados de 1 a m em U e de 1 a n em V!!!!
bool bfs() {
    queue<int> q;
    for (int u=1; u<=m; u++) {
        if (pairU[u]==0) {
            dist[u] = 0;
            q.push(u);
        }
        else dist[u] = INF;
    }
    dist[0] = INF;
    int u, v;
    while (!q.empty()) {
        u = q.front(); q.pop();
        if (dist[u] < dist[0]) {
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

bool dfs(int u) {
    if (u == 0) return true;
    int v;
    for (int i=0; i!=(int)adjU[u].size(); ++i) {
        v = adjU[u][i];
        if (dist[pairV[v]] == dist[u]+1) {
            if (dfs(pairV[v])) {
                pairV[v] = u; pairU[u] = v;
                return true;
            }
        }
    }
    dist[u] = INF;
    return false;
}

//O(E*sqrt(V))
int hopcroftKarp() {
    memset(&pairU, 0, sizeof pairU);
    memset(&pairV, 0, sizeof pairV);
    int result = 0;
    while (bfs()) {
        for (int u=1; u<=m; u++) {
            if (pairU[u]==0 && dfs(u))
                result++;
        }
    }
    return result;
}

vector<int> paths[MAXN];
int used[MAXN];

int main() {
	int N;
	set<int> pres;
	vector<int> arr;
	scanf("%d", &N);
	for(int i=0, v; i<N; i++) {
		scanf("%d", &v);
		if (!pres.count(v)) {
			pres.insert(v);
			arr.push_back(v);
		}
	}
	sort(arr.begin(), arr.end());
	N = m = n = (int)arr.size();
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			if (arr[j] > arr[i] && arr[j] % arr[i] == 0) adjU[i+1].push_back(j+1);
		}
	}
	int npaths = N-hopcroftKarp();
	int k = 0;
	memset(&used, 0, sizeof used);
	for(int i=1; i<=m; i++) {
		if (!used[i]) {
			int u = i;
			used[u] = 1;
			paths[k].push_back(arr[u-1]);
			//printf("%d", arr[u-1]);
			while(pairU[u] != 0) {
				u = pairU[u];
				used[u] = 1;
				paths[k].push_back(arr[u-1]);
				//printf(" %d", arr[u-1]);
			}
			//printf("\n");
			k++;
		}
	}
	bool relax = true;
	while(relax) {
		relax = false;
		for(int i=0; i<npaths; i++) {
			for(int j=0; j<npaths; j++) {
				if (paths[j].back() > paths[i].back() && paths[j].back() % paths[i].back() == 0) {
					relax = true;
					paths[j].pop_back();
				}
			}
		}
	}
	
	printf("%d\n", npaths);
	for(int i=0; i<npaths; i++) {
		printf("%d ", paths[i].back());
	}
	printf("\n");
	return 0;
}