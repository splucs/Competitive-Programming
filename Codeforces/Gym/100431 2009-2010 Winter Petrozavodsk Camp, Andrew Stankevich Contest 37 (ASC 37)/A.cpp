#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define sz(x) int(x.size())
#define all(x) x.begin(),x.end()
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef vector<int> vi;

bool check(int n, int m) {
	if (m % 2 == 0) {
		return n > (m*(m-1))/2 + (m-2)/2;
	}
	else {
		if ((m*(m-1))/2 > n) return false;
		if ((m*(m-1))/2 == n) return true;
		if ((m*(m-1))/2 == n-1) return false;
		return true;
	}
}

int first[MAXN], nxt[MAXN], used[MAXN], to[MAXN];
int ned = 0, deg[MAXN];

void init() {
	ned = 0;
	mset(first, -1);
	mset(deg, 0);
}

void add(int u, int v) {
	assert(u != v);

	int e = ned++;
	to[e] = v; used[e] = 0;
	nxt[e] = first[u];
	first[u] = e;
	deg[u]++;

	e = ned++;
	to[e] = u; used[e] = 0;
	nxt[e] = first[v];
	first[v] = e;
	deg[v]++;

	//printf("edge %d-%d\n", u, v);
}

vector<int> eulertour(int n, int m) {
	FOR1(u, m) assert(deg[u] % 2 == 0);

	stack<int> dfs;
	vector<int> tour;
	dfs.push(1);
	while(!dfs.empty()) {
		int u = dfs.top();
		int &e = first[u];
		while(e != -1 && used[e]) e = nxt[e];
		if (e != -1) {
			dfs.push(to[e]);
			used[e] = 1;
			used[e^1] = 1;
			//printf("edge %d-%d used\n", to[e], to[e^1]);
		}
		else {
			tour.pb(u);
			dfs.pop();
		}
	}
	reverse(all(tour));
	tour.pop_back();
	return tour;
}

void fill(int s, int t, int n) {
	//printf("%d edges %d->%d\n", n, s, t);
	if (n == 0) return;
	if (n == 1) {
		assert(s != t);
		add(s, t);
	}
	else if (s == t) {
		int o1 = 1, o2 = 1;
		while(o1 == s) o1++;
		while(o2 == s || o2 == o1) o2++;
		int last = s;
		while(n --> 1) {
			add(last, o1);
			last = o1;
			swap(o1, o2);
		}
		add(last, t);
	}
	else {
		int o = 1;
		while(s == o || t == o) o++;
		int last = s;
		while(n --> 1) {
			add(last, o);
			last = o;
			swap(o, s);
		}
		add(last, t);
	}
}

int main() {
	#ifdef ONLINE_JUDGE
	freopen("achromatic.in", "r", stdin);
	freopen("achromatic.out", "w", stdout);
	#endif

	int n;
	while(scanf("%d", &n) != EOF) {
		if (n == 4) {
			printf("2\n1 2 1 2\n");
			continue;
		}
		int m = 3;
		FOR1(i, n) {
			if (i > 3 && check(n, i)) m = i;
		}
		//printf("n = %d m = %d\n", n, m);
		init();
		FOR1(u, m) {
			FOR1(v, u-1) add(u, v);
		}
		if (m % 2 == 0) {
			for(int u = 3; u <= m; u += 2) {
				add(u, u+1);
			}
			fill(1, 2, n - ned/2);
		}
		else fill(1, 1, n - ned/2);

		vector<int> tour = eulertour(n, m);
		printf("%d\n", m);
		for(int c : tour) printf("%d ", c);
		printf("\n");
	}
	return 0;
}