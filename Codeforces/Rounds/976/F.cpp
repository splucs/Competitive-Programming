#include <bits/stdc++.h>
using namespace std;
#define INF (1<<30)
#define MAXN 103000
#define MAXM 900000
#define MOD 1000000007
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int ned, prv[MAXN], first[MAXN];
int cap[MAXM], to[MAXM], nxt[MAXM], dist[MAXN];

void init() {
   memset(first, -1, sizeof first);
   ned = 0;
}

void add(int u, int v, int f) {
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

bool bfs(int s, int t) {
	int u, v;
	memset(&dist, -1, sizeof dist);
	dist[s] = 0;
	queue<int> q; q.push(s);
	memset(&prv, -1, sizeof prv);
	while (!q.empty()) {
		u = q.front(); q.pop();
		if (u == t) break;
		for(int e = first[u]; e!=-1; e = nxt[e]) {
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

int edmondskarp(int s, int t) {
	int result = 0;
	while (bfs(s, t)) {
		result += augment(t, INF, s);
	}
	return result;
}

int degu[MAXN], degv[MAXN], mindeg;
int n1, n2, m, eu[MAXN], ev[MAXN], edu[MAXN], edv[MAXN], edt[MAXN];
vector< vector<int> > ans;

void solve() {
	int s = 0;
	int t = n1+n2+1;
	init();
	memset(&degu, 0, sizeof degu);
	memset(&degv, 0, sizeof degv);
	FOR1(j, m) {
		add(eu[j], ev[j]+n1, 1);
		edt[j] = ned-2;
		degu[eu[j]]++;
		degv[ev[j]]++;
	}
	mindeg = INF;
	FOR1(u, n1) mindeg = min(mindeg, degu[u]);
	FOR1(v, n2) mindeg = min(mindeg, degv[v]);
	FOR1(u, n1) {
		add(s, u, degu[u] - mindeg);
		edu[u] = ned-2;
	}
	FOR1(v, n2) {
		add(n1+v, t, degv[v] - mindeg);
		edv[v] = ned-2;
	}
	ans.resize(mindeg+1);
	for(int k = mindeg; k >= 0; k--) {
		edmondskarp(s, t);
		FOR1(j, m) {
			if (cap[edt[j]]) ans[k].pb(j);
		}
		sort(all(ans[k]));
		FOR1(u, n1) {
			cap[edu[u]]++;
		}
		FOR1(v, n2) {
			cap[edv[v]]++;
		}
	}
}

void print() {
	for(auto v : ans) {
		printf("%u", v.size());
		for(int j : v) {
			printf(" %d", j);
		}
		printf("\n");
	}
}

void read() {
	scanf("%d %d %d", &n1, &n2, &m);
	FOR1(j, m) {
		scanf("%d %d", &eu[j], &ev[j]);
	}
}

int main() {
	read();
	solve();
	print();
	return 0;
}