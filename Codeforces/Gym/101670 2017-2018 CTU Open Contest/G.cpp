#include <bits/stdc++.h>
using namespace std;
#define MAXN 2000009
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define pb push_back
#define mset(x, y) memset(&x, y, sizeof x)
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

int n, k;
set<int> box[MAXN];
int cnt[MAXN], pres, cur, sz[MAXN];

bool canremove(int b) {
	for(int x : box[b]) {
		if (cnt[x] == 1) return false;
	}
	return true;
}

void add(int b) {
	cur += sz[b];
	for(int x : box[b]) {
		cnt[x]++;
		if (cnt[x] == 1) {
			pres++;
		}
	}
}

void rem(int b) {
	cur -= sz[b];
	for(int x : box[b]) {
		cnt[x]--;
		if (cnt[x] == 0) pres--;
	}
}

int main() {
	while(scanf("%d %d", &n, &k) != EOF) {

		mset(cnt, 0);
		FOR(i, 2*n) box[i].clear();
		pres = 0;
		cur = 0;

		FOR(i, n) {
			int x;
			scanf("%d", &sz[i]);
			sz[i+n] = sz[i];
			FOR(j, sz[i]) {
				scanf("%d", &x);
				box[i].insert(x);
				box[i+n].insert(x);
			}
		}
		FOR(i, n) add(i+n);
		if (pres < k) {
			printf("-1\n");
			continue;
		}
		int j = 2*n-1;
		int ans = INF;
		REP(i, n) {
			add(i);
			while(canremove(j)) {
				rem(j);
				j--;
			}
			ans = min(ans, cur);
		}
		printf("%d\n", ans);
	}
	return 0;
}