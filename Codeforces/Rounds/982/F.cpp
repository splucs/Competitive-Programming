/*
             /\\
              .\\\..
              \\   \\
              \ (o) /
              (/    \
               /\    \
              ///     \
             ///|     |
            ////|     |
           //////    /
           |////    /
          /|////--V/  Stephen Morgana
         //\//|   |
     ___////__\___\__________
    ()_________'___'_________)
        \\\\
          \\\
            \\
*/

#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 500309
#define MAXM 300009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI 3.141592653589793238462643383279502884
#define FOR(x,n) for(int x=0; (x)<int(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=int(n); (x)++)
#define REP(x,n) for(int x=int(n)-1; (x)>=0; (x)--)
#define REP1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define mp make_pair
#define all(x) x.begin(), x.end()
#define mset(x,y) memset(&x, (y), sizeof(x));
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;

const int neutral = -INF; //comp(x, neutral) = x
int comp(int a, int b) {
	return max(a, b);
}

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
			st[p] = comp(st[left(p)], st[right(p)]);
		}
	}
	int query(int p, int l, int r, int a, int b) {
		push(p, l, r);
		if (a > r || b < l) return neutral;
		if (l >= a && r <= b) return st[p];
		int p1 = query(left(p), l, (l + r) / 2, a, b);
		int p2 = query(right(p), (l + r) / 2 + 1, r, a, b);
		return comp(p1, p2);
	}
public:
	SegmentTree() {
		size = MAXN;
		st.assign(4 * size, neutral);
		lazy.assign(4 * size, 0);
	}
	int query(int a, int b) { return query(1, 0, size - 1, a, b); }
	void update(int a, int b, int k) { update(1, 0, size - 1, a, b, k); }
};

int num[MAXN], pos[MAXN], cnt, ncycles, intc[MAXN], stck[MAXN];
bool ok;
vi g[MAXN];
SegmentTree st;

void dfs(int u) {
	num[u] = 1;
	pos[u] = cnt++;
	stck[pos[u]] = u;
	st.update(pos[u], pos[u], -st.query(pos[u], pos[u]));
	for(int v : g[u]) {
		if (num[v] == 0) dfs(v);
		else if (num[v] == 1) {
			int mx = st.query(pos[v], pos[u]);
			printf("cycle:\n");
			for(int i = pos[v]; i <= pos[u]; i++) {
				printf("%d(%d) ", stck[i], st.query(i, i));
			}
			printf("\n");
			if (mx < ncycles) ok = false;
			else {
				ncycles++;
				st.update(pos[v], pos[u], 1);
			}
		}
	}
	num[u] = 2;
	intc[u] = st.query(pos[u], pos[u]);
	cnt--;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	FOR(j, m) {
		int u, v;
		scanf("%d %d", &u, &v);
		g[u].pb(v);
	}
	cnt = 0;
	ncycles = 0;
	ok = true;
	dfs(1);
	int ans = -1;
	FOR1(u, n) {
		if (ok && intc[u] == ncycles) ans = u;
	}
	printf("%d\n", ans);
	return 0;
}