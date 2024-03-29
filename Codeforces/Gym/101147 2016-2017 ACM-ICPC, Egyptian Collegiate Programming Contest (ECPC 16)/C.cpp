#include <bits/stdc++.h>
using namespace std;
#define INF (1<<30)
#define MAXN 103000
#define MAXM 900000
using namespace std;

int ned, first[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];

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

int dfs(int u, int f, int s, int t) {
	if (u == t) return f;
	int v, df;
	for(int e = first[u]; e!=-1; e = nxt[e]){
        v = to[e];
		if (dist[v] == dist[u] + 1 && cap[e] > 0) {
			df = dfs(v, min(f, cap[e]), s, t);
			if (df > 0) {
				cap[e] -= df;
				cap[e^1] += df;
				return df;
			}
		}
	}
	return 0;
}

bool bfs(int s, int t){
	int u, v;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	queue<int> q; q.push(s);
	while (!q.empty()) {
		u = q.front(); q.pop();
		for(int e = first[u]; e!=-1; e = nxt[e]){
			v = to[e];
			if (dist[v] < 0 && cap[e] > 0) {
				dist[v] = dist[u] + 1;
				q.push(v);
			}
		}
	}
	return dist[t] >= 0;
}

//O(EV^2)
int dinic(int s, int t) {
	int result = 0, f;
	while (bfs(s, t)) {
		while (f = dfs(s, INF, s, t)) result += f;
	}
	return result;
}

int main() {
	freopen("wall.in", "r", stdin);
	
	int T, P, N, M;
	double x, y, r;
	scanf("%d", &T);
	while(T-->0) {
		init();
		scanf("%d %d %d", &N, &M, &P);
		r = N/2.0;
		for(int i=1; i<=N; i++) {
			add(0, i, 1);
		}
		for(int i=1; i<=M; i++) {
			add(N+i, N+M+1, 1);
		}
		while(P --> 0) {
			scanf("%lf %lf", &x, &y);
			//y = M - y;
			//printf("(x,y) = (%.3f,%.3f)\n", x, y);
			int stripe = ceil(x);
			//printf("stripe = %d\n", stripe);
			for(int pen = M-1; pen >= 0; pen--) {
				double d = hypot(x - N/2.0, y - pen);
				//if (y >= pen) printf("d(%d,%d) = %.3f\n", P, pen, d);
				if (y >= pen && d >= r && d <= r + 1.0) {
					add(stripe, N+1+pen, 1);
					break;
				}
			}
		}
		
		printf("%d\n", dinic(0, N+M+1));
	}
	
	fclose(stdin); 
	return 0;
}