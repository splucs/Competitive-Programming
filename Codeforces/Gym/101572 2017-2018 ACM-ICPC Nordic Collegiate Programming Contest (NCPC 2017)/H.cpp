#include <bits/stdc++.h>
using namespace std;
#define INF (1<<30)
#define MAXN 400009
#define MAXM 2000009
#define EPS 1e-15

int N, M, ned, first[MAXN], work[MAXN];
int to[MAXM], nxt[MAXM];
int cap[MAXM], dist[MAXN];

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
	int v;
	int df;
	for(int & e = work[u]; e!=-1; e = nxt[e]){
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

int dinic(int s, int t) {
	int result = 0, f;
	while (bfs(s, t)) {
		memcpy(work, first, sizeof work);
		while (f = dfs(s, INF, s, t)) result += f;
	}
	return result;
}

int id[MAXN];
int c[MAXN];
double cit[MAXN], line[MAXN];

bool compLine(int i, int j) {
	return line[i] < line[j];
}

typedef pair<int, int> ii;
ii find(double ang) {
	int lo = 0;
	int hi = M+1;
	while(hi > lo+1) {
		int mid = (hi + lo) / 2;
		if (line[id[mid]] <= ang) lo = mid;
		else hi = mid;
	}
	return ii(id[lo], id[hi]);
}

int main() {
	
	scanf("%d %d", &N, &M);
	init();
	int s = 0;
	int t = N+M+1;
	
	double x, y;
	for(int i=1; i<=N; i++) {
		scanf("%lf %lf", &x, &y);
		cit[i] = atan2(y, x);
		add(s, i, 1);
	}
	line[0] = -INF;
	line[M+1] = INF;
	id[0] = 0;
	id[M+1] = M+1;
	for(int i=1; i<=M; i++) {
		scanf("%lf %lf %d", &x, &y, &c[i]);
		line[i] = atan2(y, x);
		id[i] = i;
		add(N+i, t, c[i]);
	}
	sort(id, id+2+M, compLine);
	
	for(int i=1; i<=N; i++) {
		
		ii cur = find(cit[i]);
		if (cur.first == 0) cur.first = id[M];
		if (cur.second == M+1) cur.second = id[1];
		
		double ang1 = line[cur.second] - cit[i];
		if (ang1 < 0) ang1 += 2*acos(-1.0);
		double ang0 = cit[i] - line[cur.first];
		if (ang0 < 0) ang0 += 2*acos(-1.0);
		
		if (fabs(ang0 - ang1) < EPS) {
			add(i, N+cur.first, 1);
			add(i, N+cur.second, 1);
		}
		else if (ang0 < ang1) {
			add(i, N+cur.first, 1);
		}
		else if (ang0 > ang1) {
			add(i, N+cur.second, 1);
		}
	}
	
	int mf = dinic(s, t);
	printf("%d\n", mf);
	
	for(int u=1; u<=N; u++) {
		for(int e = first[u]; e!=-1; e = nxt[e]){
			int v = to[e];
			if (v > N && v <= N+M && cap[e] == 0) {
				printf("%d %d\n", u-1, v-N-1);
				break;
			}
		}
	}
	
	return 0;
}