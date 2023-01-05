#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

typedef int ll;

class FenwickTree {
	vector<ll> ft;
public:
	FenwickTree() {}
	FenwickTree(int n) {
		ft.assign(n+9, 0);
	}
	ll rsq(int i) {
		i++;
		ll sum = 0;
		while(i > 0) {
			sum += ft[i];
			i -= (i&-i);
		}
		return sum;
	}
	ll rsq(int i, int j) {
		return rsq(j) - rsq(i-1);
	}
	void update(int i, ll v) {
		i++;
		while(i < (int)ft.size()) {
			ft[i] += v;
			i += (i&-i);
		}
	}
};

typedef pair<int, ll> ii;
int par[MAXN], size[MAXN];
ll wei[MAXN];
vector<ii> adjList[MAXN];
int root, N, up[MAXN], fson[MAXN];
vector<int> chain[MAXN];
int nchs, nchain[MAXN], id[MAXN], depth[MAXN];
FenwickTree bit[MAXN];

int sizedfs(int u, int p) {
	size[u] = 1; fson[u] = -1; par[u] = p;
	int msz = 0;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].first;
		if (v == p) continue;
		wei[v] = adjList[u][i].second;
		size[u] += sizedfs(v, u);
		if (size[v] > msz) {
			msz = size[v];
			fson[u] = v;
		}
	}
	return size[u];
}

void builddfs(int u, int ch, int h) {
	nchain[u] = ch;
	id[u] = chain[ch].size();
	chain[ch].push_back(u);
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].first;
		if (v == par[u]) continue;
		if (v == fson[u]) builddfs(v, ch, h+1);
		else {
			up[nchs] = u;
			depth[nchs] = h;
			chain[nchs].clear();
			builddfs(v, nchs++, h+1);
		}
	}
}

void heavylight(int _root) {
	root = _root;
	sizedfs(root, -1);
	nchs = 0;
	wei[root] = 0;
	chain[0].clear();
	up[nchs] = -1;
	depth[nchs] = 0;
	builddfs(root, nchs++, 1);
	for(int c=0; c<nchs; c++) {
		bit[c] = FenwickTree((int)chain[c].size());
		for(int i=0; i<(int)chain[c].size(); i++) {
			int u = chain[c][i];
			bit[c].update(i, wei[u]);
		}
	}
}

int LCA(int u, int v) {
	int cu = nchain[u], cv = nchain[v];
	while(cu != cv) {
		if (depth[cu] > depth[cv]) u = up[cu];
		else v = up[cv];
		cu = nchain[u]; cv = nchain[v];
	}
	if (id[u] < id[v]) return u;
	else return v;
}

int eu[MAXN], ev[MAXN];

void update(int e, ll w) {
	int u = eu[e];
	int v = ev[e];
	if (par[v] == u) swap(v, u);
	int c = nchain[u];
	bit[c].update(id[u], w - bit[c].rsq(id[u], id[u]));
}

ll dep(int u) {
	ll d = 0;
	int v = u;
	while(u != -1) {
		int c = nchain[u];
		d += bit[c].rsq(id[u]);
		u = up[c];
	}
	return d;
}

ll dist(int u, int v) {
	return dep(u) + dep(v) - 2*dep(LCA(u, v));
}

int main() {
	int u, v;
	ll w;
	scanf("%d", &N);
	for(int j=1; j<N; j++) {
		scanf("%d %d %d", &u, &v, &w);
		eu[j] = u;
		ev[j] = v;
		adjList[u].push_back(ii(v, w));
		adjList[v].push_back(ii(u, w));
	}
	heavylight(1);
	int Q, t;
	scanf("%d", &Q);
	while(Q--) {
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d %d", &u, &v);
			printf("%d\n", dist(u, v));
		}
		else {
			scanf("%d %d", &u, &w);
			update(u, w);
		}
	}
	return 0;
}