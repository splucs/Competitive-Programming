#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 320
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-7
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

class SegmentTree {
private:
	vector<int> st, lazy;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void push(int p, int l, int r) {
		st[p] += lazy[p]; 		    //Caso RMQ
		if (l != r) {
			lazy[right(p)] += lazy[p];
			lazy[left(p)] += lazy[p];
		}
		lazy[p] = 0;
	}
	void update(int p, int l, int r, int a, int b, int k) {
		push(p, l, r);
		if (a > r || b < l) return;
		else if (l >= a && r <= b) {
			lazy[p] = k; push(p, l, r);
		}
		else {
			update(left(p), l, (l + r) / 2, a, b, k);
			update(right(p), (l + r) / 2 + 1, r, a, b, k);
			st[p] = max(st[left(p)], st[right(p)]);
		}
	}
	int query(int p, int l, int r, int a, int b) {
		push(p, l, r);
		if (a > r || b < l) return 0;
		if (l >= a && r <= b) return st[p];
		int p1 = query(left(p), l, (l + r) / 2, a, b);
		int p2 = query(right(p), (l + r) / 2 + 1, r, a, b);
		return max(p1, p2);
	}
public:
	SegmentTree() {}
	SegmentTree(int _size) {
		size = _size;
		st.assign(4 * size, 0);
		lazy.assign(4 * size, 0);
	}
	int query(int a, int b) { return query(1, 0, size - 1, a, b); }
	void update(int a, int b, int k) { update(1, 0, size - 1, a, b, k); }
};

SegmentTree st[MAXN];
int par[MAXN], size[MAXN];
vector<int> adjList[MAXN];
int root, up[MAXN], fson[MAXN];
vector<int> chain[MAXN];
int nchs, nchain[MAXN], id[MAXN], depth[MAXN];
int eu[MAXN], ev[MAXN];
bool intree[MAXN];

inline int getother(int i, int u) {
	return eu[i] + ev[i] - u;
}

int sizedfs(int u, int p) {
	size[u] = 1; fson[u] = -1; par[u] = p;
	int msz = 0;
	for(int e : adjList[u]) {
		int v = getother(e, u);
		if (size[v] > 0) continue;
		intree[e] = true;
		size[u] += sizedfs(v, u);
		if (size[v] > msz) {
			fson[u] = v; msz = size[v];
		}
	}
	return size[u];
}

void builddfs(int u, int ch, int h){
	nchain[u] = ch; id[u] = chain[ch].size();
	chain[ch].push_back(u);
	for(int e : adjList[u]) {
		if (!intree[e]) continue;
		int v = getother(e, u);
		if (v == par[u]) continue;
		if (v == fson[u]) builddfs(v, ch, h+1);
		else {
			up[nchs] = u; depth[nchs] = h;
			chain[nchs].clear();
			builddfs(v, nchs++, h+1);
		}
	}
}

void heavylight(int _root) {
	root = _root;
	sizedfs(root, -1);
	up[nchs] = -1; depth[nchs] = 0;
	builddfs(root, nchs++, 1);
}

void increase(int u, int v) {
	int cu = nchain[u], cv = nchain[v];
	while(cu != cv) {
		if (depth[cu] > depth[cv]) {
			st[cu].update(0, id[u], 1);
			u = up[cu];
		}
		else {
			st[cv].update(0, id[v], 1);
			v = up[cv];
		}
		cu = nchain[u]; cv = nchain[v];
	}
	if (id[u] < id[v]) {
		st[cv].update(id[u]+1, id[v], 1);
	}
	if (id[v] < id[u]) {
		st[cv].update(id[v]+1, id[u], 1);
	}
}

int query(int u, int v) {
	int cu = nchain[u], cv = nchain[v];
	int ans = 0;
	while(cu != cv) {
		if (depth[cu] > depth[cv]) {
			ans = max(ans, st[cu].query(0, id[u]));
			u = up[cu];
		}
		else {
			ans = max(ans, st[cv].query(0, id[v]));
			v = up[cv];
		}
		cu = nchain[u]; cv = nchain[v];
	}
	if (id[u] < id[v]) ans = max(ans, st[cv].query(id[u]+1, id[v]));
	if (id[v] < id[u]) ans = max(ans, st[cv].query(id[v]+1, id[u]));
	return ans;
}


int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	memset(&size, 0, sizeof size);
	memset(&intree, 0, sizeof intree);
	FOR1(e, M) {
		scanf("%d %d", &eu[e], &ev[e]);
		adjList[eu[e]].pb(e);
		adjList[ev[e]].pb(e);
	}
	nchs = 0;
	FOR1(u, N) {
		if (size[u] == 0) {
			heavylight(u);
		}
	}
	FOR(i, nchs) {
		st[i] = SegmentTree(chain[i].size());
	}
	vector<int> ansarr;
	FOR1(e, M) {
		if (!intree[e]) {
			increase(eu[e], ev[e]);
		}
	}
	FOR1(e, M) {
		if (!intree[e]) {
			if (query(eu[e], ev[e]) > 1) increase(eu[e], ev[e]);
			else ansarr.push_back(e);
		}
	}
	FOR1(e, M) {
		if (intree[e]) {
			if (query(eu[e], ev[e]) == 1) ansarr.push_back(e);
		}
	}
	sort(all(ansarr));
	printf("%u\n", ansarr.size());
	for (int& i : ansarr) {
		printf("%d ", i);
	}
	printf("\n");
	return 0;
}