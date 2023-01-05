#include <bits/stdc++.h>
using namespace std;
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 10009
#define MAXM 309
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
typedef pair<int, int> ii;
typedef long long ll;

vector<int> g[MAXN];
int h[MAXN], mh, q;

void ask(int u) {
	assert(u >= 1 && u < (1<<mh));
	assert(q < 16);
	q++;
	int k, v;
	printf("? %d\n", u);
	fflush(stdout);
	g[u].clear();
	scanf("%d", &k);
	while (k --> 0) {
		scanf("%d", &v);
		g[u].pb(v);
	}
	random_shuffle(all(g[u]));
}

bool asked(int u) {
	return !g[u].empty();
}

void findleaf(int u, list<int> & l, bool back) {
	for(int v : g[u]) {
		if (asked(v)) continue;
		ask(v);
		if (back) l.pb(v);
		else l.pf(v);
		findleaf(v, l, back);
		return;
	}
}

int emptylist(list<int> & l) {
	int cur = 1;
	while(h[l.front()] > cur) {
		h[l.back()] = cur;
		l.pop_back();
		cur++;
	}
	while(l.size() > 1u) {
		h[l.front()] = cur;
		h[l.back()] = cur;
		l.pop_back();
		l.pop_front();
		cur++;
	}
	int u = l.front();
	h[u] = cur;
	l.clear();
	assert(u >= 1 && u < (1<<mh));
	return u;
}

int ans;
bool dfs(int u, int dep) {
	assert(u >= 1 && u < (1<<mh));
	if (dep <= 0) return false;
	if (q == 16 && !asked(u)) {
		ans = u;
		return true;
	}
	if (q < 16 && !asked(u)) ask(u);
	if (g[u].size() == 2u) {
		ans = u;
		return true;
	}
	for(int v : g[u]) {
		if (asked(v)) continue;
		if (dfs(v, dep-1)) return true;
	}
	return false;
}

void testcase() {
	q = 0;
	scanf("%d", &mh);
	FOR(i, MAXN) g[i].clear();

	//step 1
	int n = rand()%((1<<mh)-1) + 1;
	ask(n);
	list<int> l;
	l.pb(n);
	findleaf(n, l, true);
	findleaf(n, l, false);
	h[l.front()] = 1;
	n = emptylist(l);

	//step 2
	while (h[n] < min(4, mh-1)) {
		l.pb(n);
		findleaf(n, l, true);
		n = emptylist(l);
	}

	//step 3
	ans = -1;
	dfs(n, mh-h[n]+1);
	printf("! %d\n", ans);
	fflush(stdout);
}

int main() {
	int t;
	scanf("%d", &t);
	while (t --> 0) {
		testcase();
	}
}