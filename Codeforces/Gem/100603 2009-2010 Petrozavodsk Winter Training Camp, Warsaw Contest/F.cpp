#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009

typedef pair<int, int> ii;
map<int, vector<ii> > pdiag, sdiag;
int N, x[MAXN], y[MAXN], sz;
map<ii, int> p2id;
bool vis[MAXN];
int corner[MAXN];
vector<int> adjList[MAXN];

int dfs(int u) {
	vis[u] = true;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (!vis[v]) return dfs(v);
	}
	return u;
}

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%d %d", &x[i], &y[i]);
	}
	sz = 0;
	memset(&corner, 0, sizeof corner);
	for(int i=0; i<N; i++) {
		int j = (i+1)%N;
		int p = (i-1+N)%N;
		if (x[i] == x[j]) {
			if (y[j] > y[i] && x[i] > x[p]) sdiag[x[i]+y[i]].push_back(ii(x[i], sz));
			if (y[j] > y[i] && x[i] < x[p]) pdiag[x[i]-y[i]].push_back(ii(x[i], sz));
			if (y[j] < y[i] && x[i] < x[p]) sdiag[x[i]+y[i]].push_back(ii(x[i], sz));
			if (y[j] < y[i] && x[i] > x[p]) pdiag[x[i]-y[i]].push_back(ii(x[i], sz));
			corner[sz] = i+1;
			p2id[ii(x[i], y[i])] = sz++;
			for(int k = min(y[i], y[j])+1; k < max(y[i], y[j]); k++) {
				pdiag[x[i]-k].push_back(ii(x[i], sz));
				sdiag[x[i]+k].push_back(ii(x[i], sz));
				p2id[ii(x[i], k)] = sz++;
			}
		}
		if (y[i] == y[j]) {
			if (x[j] > x[i] && y[i] > y[p]) sdiag[x[i]+y[i]].push_back(ii(x[i], sz));
			if (x[j] > x[i] && y[i] < y[p]) pdiag[x[i]-y[i]].push_back(ii(x[i], sz));
			if (x[j] < x[i] && y[i] < y[p]) sdiag[x[i]+y[i]].push_back(ii(x[i], sz));
			if (x[j] < x[i] && y[i] > y[p]) pdiag[x[i]-y[i]].push_back(ii(x[i], sz));
			corner[sz] = i+1;
			p2id[ii(x[i], y[i])] = sz++;
			for(int k = min(x[i], x[j])+1; k < max(x[i], x[j]); k++) {
				pdiag[k-y[i]].push_back(ii(k, sz));
				sdiag[k+y[i]].push_back(ii(k, sz));
				p2id[ii(k, y[i])] = sz++;
			}
		}
	}
	for(map<int, vector<ii> >::iterator it = pdiag.begin(); it != pdiag.end(); it++) {
		vector<ii> & v = it->second;
		sort(v.begin(), v.end());
		for(int i=0; i<(int)v.size(); i+=2) {
			int j = i+1;
			adjList[v[i].second].push_back(v[j].second);
			adjList[v[j].second].push_back(v[i].second);
		}
	}
	for(map<int, vector<ii> >::iterator it = sdiag.begin(); it != sdiag.end(); it++) {
		vector<ii> & v = it->second;
		sort(v.begin(), v.end());
		for(int i=0; i<(int)v.size(); i+=2) {
			int j = i+1;
			adjList[v[i].second].push_back(v[j].second);
			adjList[v[j].second].push_back(v[i].second);
		}
	}
	memset(&vis, false, sizeof vis);
	printf("%d\n", N/2);
	for(int i=0, u, v; i<N; i++) {
		u = p2id[ii(x[i], y[i])];
		if (!vis[u]) {
			v = dfs(u);
			printf("%d %d\n", corner[u], corner[v]);
		}
	}
	return 0;
}