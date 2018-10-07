#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM 1000009
#define INF 0x3f3f3f3f
#define MOD 1000000009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

#define MAXS 40000009
const int neutral = 0; //comp(x, neutral) = x
#define comp(a, b) ((a)+(b))

int nds, st[MAXS], ls[MAXS], rs[MAXS];

class PersistentSegmentTree {
private:
	int vroot[MAXN];
	int size, nds, nv;
	int newnode() {
		ls[nds] = rs[nds] = -1;
		st[nds++] = neutral;
		return nds-1;
	}
	void build(int p, int l, int r, int* A) {
		if (l == r) {
			st[p] = A ? A[l] : neutral;
			return;
		}
		int m = (l + r) / 2;
		build(ls[p] = newnode(), l, m, A);
		build(rs[p] = newnode(), m+1, r, A);
		st[p] = comp(st[ls[p]], st[rs[p]]);
	}
	void update(int prv, int p, int l, int r, int i, int k) {
		if (l == r) {
			st[p] = k; //substitui
			//st[p] = st[prv] + k; //agrega
			return;
		}
		int m = (l + r) / 2;
		if (i <= m) {
			rs[p] = rs[prv];
			update(ls[prv], ls[p] = newnode(), l, m, i, k);
		}
		else {
			ls[p] = ls[prv];
			update(rs[prv], rs[p] = newnode(), m+1, r, i, k);
		}
		st[p] = comp(st[ls[p]], st[rs[p]]);
	}
	int query(int p, int l, int r, int a, int b) {
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		int m = (l + r) / 2;
		int p1 = query(ls[p], l, m, a, b);
		int p2 = query(rs[p], m + 1, r, a, b);
		return comp(p1, p2);
	}
	void print(int p, int l, int r) {
		if (l == r) {
			printf("%d ", st[p]);
			return;
		}
		int m = (l + r) / 2;
		print(ls[p], l, m);
		print(rs[p], m+1, r);
	}
public:
	PersistentSegmentTree(int* begin, int* end) {
		nds = nv = 0; size = (int)(end-begin);
		vroot[nv++] = newnode();
		build(vroot[0], 0, size-1, begin);
	}
	PersistentSegmentTree(int _size = 1) {
		nds = nv = 0; size = _size;
		vroot[nv++] = newnode();
		build(vroot[0], 0, size-1, NULL);
	}
	int query(int a, int b, int v) {
		return query(vroot[v], 0, size-1, a, b);
	}
	int update(int i, int v, int k) {
		vroot[nv++] = newnode();
		update(vroot[v], vroot[nv-1], 0, size-1, i, k);
		return nv-1;
	}
	int nver() { return nv; }
	void print(int v) {
		print(vroot[v], 0, size-1);
		printf("\n");
	}
};

struct edge {
	int u, v, w, id;
};

bool operator < (edge a, edge b) {
	return a.w < b.w;
}

int n, m;
int q[MAXN];
vector<edge> g[MAXN];
edge dist[MAXN], adj[MAXN];

void removeedge(int u, edge e) {
	if (g[u].empty()) return;
	for(edge &e2 : g[u]) {
		if (e2.id == e.id) swap(e2, g[u].back());
	}
	if (g[u].back().id == e.id) g[u].pop_back();
}

edge gethigh(edge ne) {
	int s = ne.u, t = ne.v;
	int st = 0, en = 0;
	FOR1(u, n) dist[u].id = -1;
	q[en++] = s;
	dist[s].id = -2;
	dist[s].w = -INF;
	while(en > st) {
		int u = q[st++];
		for(edge e: g[u]) {
			int v = e.u + e.v - u;
			if (dist[v].id == -1) {
				dist[v] = dist[u];
				if (dist[v] < e) dist[v] = e;
				q[en++] = v;
			}
		}
	}
	edge ans = dist[t];
	if (ans.id != -1) {
		removeedge(ans.u, ans);
		removeedge(ans.v, ans);
		//printf("edge %d-%d: %d removes edge %d-%d: %d\n", ne.u, ne.v, ne.w, ans.u, ans.v, ans.w);
	}
	g[s].push_back(ne);
	g[t].push_back(ne);
	//printf("add edge %d-%d: %d\n", ne.u, ne.v, ne.w);
	return ans;
}

int find(int w) {
	int lo = -1;
	int hi = m;
	while(hi > lo + 1) {
		int mid = (hi + lo) / 2;
		if (adj[mid].w < w) lo = mid;
		else hi = mid;
	}
	return hi;
}

int ver[MAXN];
PersistentSegmentTree pst;

int main() {
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		scanf("%d %d", &n, &m);
		FOR1(u, n) g[u].clear();
		FOR(j, m) {
			scanf("%d %d %d", &adj[j].u, &adj[j].v, &adj[j].w);
		}
		sort(adj, adj+m);
		pst = PersistentSegmentTree(m);
		REP(j, m) {
			adj[j].id = j;
			edge cur = adj[j];
			edge e = gethigh(cur);
			//printf("iteration %d:", j);
			//printf(" add %d to %d", cur.w, j);
			ver[j] = pst.update(j, pst.nver()-1, cur.w);
			if (e.id != -1) {
			//	printf(" rem %d from %d", e.w, e.id);
				ver[j] = pst.update(e.id, pst.nver()-1, 0);
			}
			//printf("\n");
			//pst.print(ver[j]);
		}
		int q;
		scanf("%d", &q);
		int lastans = 0, l, r;
		while(q --> 0) {
			scanf("%d %d", &l, &r);
			l -= lastans;
			r -= lastans;
			int lid = find(l);
			int rid = find(r+1)-1;
			//printf("query [%d,%d], ids %d to %d\n", l, r, lid, rid);
			if (lid >= m || rid < lid) {
				lastans = 0;
			}
			else {
				lastans = pst.query(0, rid, ver[lid]);
			}
			printf("%d\n", lastans);
		}
	}
	return 0;
}