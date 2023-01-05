#include <bits/stdc++.h>
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define MAXN 100009
#define FOR(x,n) for(int x=0;x<n;x++)
#define FOR1(x,n) for(int x=1;x<=n;x++)
#define sz(x) int(x.size())
#define mset(x, y) memset(&x, y, sizeof x)
#define fi first
#define se second
#define pb push_back
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;

int ans[MAXN], acum[MAXN];
int pr[MAXN];
pair<ii, int> queries[MAXN];

void pre() {
	pr[0] = 1;
	pr[1] = 1;
	for (int i = 2; i < MAXN; i++) {
		if (pr[i] == 0) {
			for (int j = i; j < MAXN; j += i) {
				pr[j] = i;
			}
		}
	}
}

int ft[MAXN];
int rsq(int i) {
	int sum = 0;
	for (; i; i -= (i&-i)) sum = sum + ft[i];
	return sum;
}

void update(int i, int v) {
	for (; i < MAXN; i += (i&-i)) ft[i] += v;
}

int main() {
	int n, a, b;
	scanf("%d", &n);
	FOR(i, n) {
		scanf("%d %d", &a, &b);
		queries[i] = make_pair(ii(a, b), i);
	}
	pre();
	sort(queries, queries + n);
	int st = 2;
	FOR(i, n) {
		int k = queries[i].first.first;
		while (st <= k) {
			update(pr[st], 1);
			st++;
		}
		ans[queries[i].second] = rsq(queries[i].first.second);
	}
	FOR(i, n) printf("%d\n", ans[i]);
}
