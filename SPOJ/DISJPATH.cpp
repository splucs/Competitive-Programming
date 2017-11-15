#include <bits/stdc++.h>
#define INF (1<<30)
#define MAXN 5009
#define MAXM 900000
using namespace std;

/*
 * Edmonds-Karp's Algorithm - O(VE^2)
 */

int ned, prv[MAXN], first[MAXN];
int cap[MAXM], backup[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];

void init(){
   memset(first, -1, sizeof first);
   ned = 0;
}

void add(int u, int v, int f){
    to[ned] = v, cap[ned] = f;
    nxt[ned] = first[u];
    first[u] = ned++;
    
    to[ned] = u, cap[ned] = 0;
    nxt[ned] = first[v];
    first[v] = ned++;
}

int augment(int v, int minEdge, int s) {
	int e = prv[v];
	if (e == -1) return minEdge;
	int f = augment(to[e^1], min(minEdge, cap[e]), s);
	cap[e] -= f;
	cap[e^1] += f;
	return f;
}

bool bfs(int s, int t){
	int u, v;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	queue<int> q; q.push(s);
	memset(&prv, -1, sizeof prv);
	while (!q.empty()) {
		u = q.front(); q.pop();
		if (u == t) break;
		for(int e = first[u]; e!=-1; e = nxt[e]){
			v = to[e];
			if (dist[v] < 0 && cap[e] > 0) {
				dist[v] = dist[u] + 1;
				q.push(v);
				prv[v] = e;
			}
		}
	}
	return dist[t] >= 0;
}

int edmondskarp(int s, int t){
	int result = 0;
	while (bfs(s, t)) {
		result += augment(t, INF, s);
	}
	return result;
}

int in[MAXN], out[MAXN], val[MAXN];
char buffer[MAXN];

bool isNumber(char c) {
	return c >= '0' && c <= '9';
}

int main() {
	int K, N, caseNo = 0;
	while(scanf(" %d %d", &K, &N), N || K) {
		caseNo++;
		init();
		int k = 0;
		for(int i=1; i<=N; i++) {
			in[i] = k++;
			out[i] = k++;
			val[in[i]] = val[out[i]] = i;
			if (i!=1 && i!=2) add(in[i], out[i], 1);
		}
		for(int u=1, v; u<=N; u++) {
			scanf(" "); gets(buffer); scanf(" ");
			int len = strlen(buffer);
			for(int i=0; i<len; i++) {
				if (i == 0 || (isNumber(buffer[i]) && !isNumber(buffer[i-1]))) {
					sscanf(buffer+i, "%d", &v);
					add(out[u], in[v], 1);
					add(out[v], in[u], 1);
				}
			}
		}
		
		for(int e = 0; e<ned; e++) backup[e] = cap[e];
		int mf = edmondskarp(out[1], in[2]);
		printf("Case %d:\n", caseNo);
		if (mf < K) printf("Impossible\n");
		else {
			for(int i=1; i<=K; i++) {
				int u = in[1];
				while(u != in[2]) {
					u = out[val[u]];
					printf("%d ", val[u]);
					for(int e = first[u]; e!=-1; e = nxt[e]) {
						if (cap[e] != backup[e]) {
							cap[e] = backup[e];
							u = to[e];
							break;
						}
					}
				}
				printf("2\n");
			}
		}
		
		printf("\n");
	}
	
	return 0;
}