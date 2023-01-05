#include <bits/stdc++.h>
using namespace std;
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 100309
#define MAXM 60000009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define ROF(x,n) for(int x=(n)-1; (x)>=0; (x)--)
#define ROF1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define mset(x,y) memset(&x, (y), sizeof(x));
typedef pair<int, int> ii;
typedef long long ll;
#define DIG 20

int l[MAXM], r[MAXM], cnt = 0;

int newnode() {
	l[cnt] = r[cnt] = -1;
	cnt++;
	return cnt-1;
}

void insert(int root, int num) {
	int u = root;
	ROF(i, DIG) {
		if (num & (1<<i)) {
			if (r[u] == -1) r[u] = newnode();
			u = r[u];
		}
		else {
			if (l[u] == -1) l[u] = newnode();
			u = l[u];
		}
	}
}

int ans, limit;
bool search(int u, int h, int num, int cur) {
	if (u == -1) return false;
	if (cur > limit) return false;
	if (h == -1) {
		ans = cur;
		return true;
	}
	if (num & (1<<h)) {
		if (search(l[u], h-1, num, cur)) return true;
		if (search(r[u], h-1, num, cur | (1<<h))) return true;
	}
	else {
		if (search(r[u], h-1, num, cur | (1<<h))) return true;
		if (search(l[u], h-1, num, cur)) return true;
	}
	return false;
}

int root[MAXN];

int main() {
	FOR(i, MAXN) root[i] = newnode();

	int q;
	scanf("%d", &q);
	while (q --> 0) {
		int t, u, x, k, s;
		scanf("%d", &t);
		if (t == 1) {
			scanf("%d", &u);
			for(int i = 1; i*i <= u; i++) {
				if (u % i == 0) {
					insert(root[i], u);
					if (i*i < u) insert(root[u/i], u);
				}
			}
		}
		else if (t == 2) {
			scanf("%d %d %d", &x, &k, &s);
			limit = s-x;
			if (x % k != 0 || !search(root[k], DIG-1, x, 0)) printf("-1\n");
			else printf("%d\n", ans);
		}
	}
	return 0;
}