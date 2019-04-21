#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int parw[MAXN];
typedef int ll;
typedef const int* vit;

const ll neutral = -1e+9;
ll comp(ll a, ll b) {
	return max(a, b);
}

class SegmentTree {
private:
	vector<long long> st, pos;
	int size;
#define parent(p) (p >> 1)
#define left(p) (p << 1)
#define right(p) ((p << 1) + 1)
	void build(int p, int l, int r, vit A) {
		if (l == r) {
			st[p] = parw[A[l]];
			pos[l] = p;
		}
		else {
			build(left(p), l, (l+r)/2, A);
			build(right(p), (l+r)/2+1, r, A);
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	ll find(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		
		ll p1 = find(left(p), l, (l+r)/2, a, b);
		ll p2 = find(right(p), (l+r)/2+1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree() {}
	SegmentTree(vit begin, vit end) {
		size = (int)(end-begin);
		st.assign(4*size, neutral);
		pos.assign(size + 9, 0);
		build(1, 0, size-1, begin);
	}
	ll query (int a, int b) { return find(1, 0, size-1, a, b); }
	
	void update(int n, ll num) {
		st[pos[n]] = num;
		n = parent(pos[n]);
		while(n > 0) {
			st[n] = comp(st[left(n)], st[right(n)]);
			n = parent(n);
		}
	}
};

typedef pair<int, int> ii;
int par[MAXN], size[MAXN];
vector<ii> adjList[MAXN];
int root, up[MAXN], fson[MAXN];
vector<int> chain[MAXN];
int nchs, nchain[MAXN], id[MAXN], depth[MAXN];

int sizedfs(int u, int p) {
	size[u] = 1;
	fson[u] = -1;
	par[u] = p;
	int msz = 0;
	for(int i=0; i<(int)adjList[u].size(); i++) {
		int v = adjList[u][i].first;
		int w = adjList[u][i].second;
		if (v == p) continue;
		parw[v] = w;
		size[u] += sizedfs(v, u);
		if (size[v] > msz) {
			fson[u] = v;
			msz = size[v];
		}
	}
	return size[u];
}

void builddfs(int u, int ch, int h) {
	nchain[u] = ch;
	id[u] = chain[ch].size();
	chain[ch].push_back(u);
	//printf("node %d id %d on chain %d\n", u, id[u], ch);
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

SegmentTree st[MAXN];

void hld(int _root) {
	root = _root;
	sizedfs(root, -1);
	
	nchs = 0;
	chain[0].clear();
	up[0] = -1;
	depth[0] = 0;
	builddfs(root, nchs++, 1);
	parw[root] = neutral;
	
	int aux[MAXN];
	
	for(int i=0; i<nchs; i++) {
		for(int j=0; j<(int)chain[i].size(); j++) {
			aux[j] = chain[i][j];
		}
		st[i] = SegmentTree(aux, aux+(int)chain[i].size());
	}
}

int lca(int u, int v) {
	int cu = nchain[u], cv = nchain[v], ans = neutral;
	while(cu != cv) {
		//printf("cu, cv: %d,%d\n", cu, cv);
		if (depth[cu] > depth[cv]) {
			ans = comp(ans, st[cu].query(0, id[u]));
			u = up[cu];
		}
		else {
			ans = comp(ans, st[cv].query(0, id[v]));
			v = up[cv];
		}
		cu = nchain[u], cv = nchain[v];
	}
	if (id[u] < id[v]) {
		ans = comp(ans, st[cu].query(id[u]+1, id[v]));
	}
	else ans = comp(ans, st[cu].query(id[v]+1, id[u]));
	return ans;
}

int N, M;
vector<ii> adj[MAXN];

int prim() {
	bool taken[MAXN];
	memset(&taken, false, sizeof taken);
	taken[0] = true;
	priority_queue<ii> pq;
	ii v, front;
	int u, w, cost = 0;
	for(int j=0; j<(int)adj[1].size(); j++) {
		v = adj[1][j];
		pq.push(ii(-v.second, -v.first));
		par[v.first] = 1;
	}
	taken[1]  =true;
	while(!pq.empty()) {
		front = pq.top();
		pq.pop();
		u = -front.second;
		w = -front.first;
		if (!taken[u]) {
			taken[u] = true;
			cost += w;
			//printf("taken %d->%d\n", u, par[u]);
			if (par[u] != 0) adjList[u].push_back(ii(par[u], w));
			if (par[u] != 0) adjList[par[u]].push_back(ii(u, w));
			for(int j=0; j<(int)adj[u].size(); j++) {
				v = adj[u][j];
				if (!taken[v.first]) {
					par[v.first] = u;
					pq.push(ii(-v.second, -v.first));
				}
			}
		}
	}
	return cost;
}

map<ii, int> ecost;

int main() {
	scanf("%d %d", &N, &M);
	int u, v, w;
	for(int j=0; j<M; j++) {
		scanf("%d %d %d", &u, &v, &w);
		adj[u].push_back(ii(v, w));
		adj[v].push_back(ii(u, w));
		ecost[ii(u, v)] = w;
		ecost[ii(v, u)] = w;
	}
	int mincost = prim();
	//printf("mincost = %d\n", mincost);
	hld(1);
	
	int Q;
	scanf("%d", &Q);
	while(Q --> 0) {
		scanf("%d %d", &u, &v);
		int mine = lca(u, v);
		//printf("ecost = %d\n", ecost[ii(u, v)]);
		//printf("minedge = %d\n", mine);
		printf("%d\n", mincost - mine + ecost[ii(u, v)]);
	}
	return 0;
}
