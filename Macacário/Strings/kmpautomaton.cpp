#include <vector>
#include <algorithm>
using namespace std;
#define MAXN 400009

#include <cstdio>

/*
 * Heavy-Light Decomposition
 */

vector<int> adjList[MAXN];
int in[MAXN], out[MAXN], up[MAXN];
int par[MAXN], pre[MAXN], sz[MAXN];

void dfssize(int u) {
	int s = sz[u] = 0;
	for(int i = 0; i < (int)adjList[u].size(); i++) {
		int &v = adjList[u][i]; //don't forget &
		if (v == par[u]) continue;
		par[v] = u;
		dfssize(v);
		s += sz[v];
		if(sz[v] > sz[adjList[u][0]])
			swap(v, adjList[u][0]);
	}
	sz[u] = 1 + s;
}

void dfshld(int u, int &t) {
	pre[t] = u;
	in[u] = t++;
	for(int i = 0; i < (int)adjList[u].size(); i++) {
		int v = adjList[u][i];
		if (v == par[u]) continue;
		up[v] = (i == 0 ? up[u] : v);
		dfshld(v, t);
	}
	out[u] = t-1;
}

void hld(int root) {
	par[root] = -1;
	dfssize(root);
	int t = 0;
	up[root] = root;
	dfshld(root, t);
	//create DS over values sorted by array pre
}

int LCA(int u, int v) {
	while(up[u] != up[v]) {
		if (in[u] > in[v]) u = par[up[u]];
		//query DS for subarray [in[up[u]], in[u]] 
		else v = par[up[v]];
		//query DS for subarray [in[up[v]], in[v]]
	}
	return in[u] > in[v] ? v : u;
	//query DS for subarray [in[v], in[u]] or [in[u], in[v]]
}

/*
 * KMP Automaton
 */

#include <cstring>
#define MAXM 109

struct trans {
	int m, to[MAXM], match[MAXM];
	trans(int _m = -1) : m(_m) {}
};

trans operator +(trans a, trans b) {
	if (b.m < 0) return a;
	if (a.m < 0) return b;
	//assert(a.m == b.m);
	trans c(a.m);
	for(int i = 0; i < c.m; i++) {
		c.to[i] = b.to[a.to[i]];
		c.match[i] = a.match[i] + b.match[a.to[i]];
	}
	return c;
}

struct KMP {
	char P[MAXM];
	int b[MAXM], m;
	void build(const char* _P) {
		m = strlen(_P);
		strcpy(P, _P);
		memset(&b, -1, sizeof b);
		for(int i = 0, j = -1; i < m;) {
			while (j >= 0 && P[i] != P[j]) j = b[j];
			b[++i] = ++j;
		}
	}
	trans get(char c) {
		trans ans(m);
		for(int i = 0, j, cnt; i < m; i++) {
			j = i; cnt = 0;
			while(j >= 0 && c != P[j]) j = b[j];
			j++;
			if (j == m) cnt++, j = b[j];
			ans.to[i] = j;
			ans.match[i] = cnt;
		}
		return ans;
	}
};

/*
 * Codeforces 101908H
 */

char P[MAXN];
KMP kmp;
char col[MAXN];

class SegmentTree {
	trans st[2][MAXN];
	int n;
	trans query(int u, int l, int r, int a, int b, int t) {
		if (l > b || r < a) return trans(-1);
		if (a <= l && r <= b) return st[t][u];
		int m = (l + r) / 2;
		trans p1 = query(2*u, l, m, a, b, t);
		trans p2 = query(2*u+1, m+1, r, a, b, t);
		return t == 0 ? p1 + p2 : p2 + p1;
	}
public:
	SegmentTree() {}
	void build(int sz) {
		for (n = 1; n < sz; n <<= 1);
		for(int i=0; i<sz; i++) {
			st[0][i+n] = st[1][i+n] = kmp.get(col[pre[i]]);
		}
		for(int i=n-1; i; i--) {
			st[0][i] = st[0][2*i] + st[0][2*i+1];
			st[1][i] = st[1][2*i+1] + st[1][2*i];
		}
	}
	void update(int i, char c) {
		st[0][i+n] = st[1][i+n] = kmp.get(c);
		for (i += n, i >>= 1; i; i >>= 1) {
			st[0][i] = st[0][2*i] + st[0][2*i+1];
			st[1][i] = st[1][2*i+1] + st[1][2*i];
		}
	}
	trans query(int l, int r, int t) {
		return query(1, 0, n-1, l, r, t);
	}
};

SegmentTree st;

trans get(int u, int v) {
	trans left, mid, right;
	while(up[u] != up[v]) {
		if (in[u] > in[v]) {
			trans cur = st.query(in[up[u]], in[u], 1);
			left = left + cur;
			u = par[up[u]];
		}
		else {
			trans cur = st.query(in[up[v]], in[v], 0);
			right = cur + right;
			v = par[up[v]];
		}
	}
	if (in[u] > in[v]) mid = st.query(in[v], in[u], 1);
	else mid = st.query(in[u], in[v], 0);
	return (left + mid) + right;
}

int main() {
	int n, q;
	scanf("%d %d", &n, &q);
	scanf(" %s %s", P, col+1);
	for(int i = 0; i < n-1; i++) {
		int u, v;
		scanf("%d %d", &u, &v);
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	hld(1);
	kmp.build(P);
	st.build(n);
	while(q --> 0) {
		int op;
		scanf("%d", &op);
		if (op == 1) {
			int u, v;
			scanf("%d %d", &u, &v);
			trans ans = get(u, v);
			printf("%d\n", ans.match[0]);
		}
		else {
			int u;
			char x;
			scanf("%d %c", &u, &x);
			col[u] = x;
			st.update(in[u], x);
		}
	}
	return 0;
}