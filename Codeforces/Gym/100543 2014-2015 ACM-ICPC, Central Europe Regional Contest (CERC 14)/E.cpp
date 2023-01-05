#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define MAXM 1000009
#define INF 0x3f3f3f3f
#define MOD 1000000009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef long long ll;
typedef vector<int> vi;
typedef pair<int, int> ii;

set<ii> vis[MAXN];
int n, a[MAXN];
char ans[MAXN];
int hi[MAXM];

void print(int i, int b1, int b2) {
	printf("%d:", i);
	FOR(k, 20) if ((1<<k) & b1) printf(" %d", 1<<k);
	REP(k, 20) if ((1<<k) & b2) printf(" %d", 1<<k);
	printf(" +%d\n", a[i]);
}

bool DP(int i, int b1, int b2) {
	if (vis[i].count({b1, b2})) return false;
	vis[i].insert({b1, b2});
	if (b1 > 0 && hi[b1] >= hi[b2]) return DP(i, b1-hi[b1], b2+hi[b1]);
	//print(i, b1, b2);
	if (i == n) {
		ans[i] = 0;
		if (b1 != (b1&-b1) || b2 != (b2&-b2)) return false;
		if (b1 == 0 || b2 == 0 || b1 == b2) return true;
		return false;
	}
	if (b1 == 0 || a[i] <= (b1 & -b1)) {
		ans[i] = 'l';
		if (DP(i+1, b1+a[i], b2)) return true;
	}
	if (b2 == 0 || a[i] <= (b2 & -b2)) {
		ans[i] = 'r';
		if (DP(i+1, b1, b2+a[i])) return true;
	}
	return false;
}

int main() {
	FOR(i, MAXM) {
		hi[i] = 0;
		FOR(k, 20) {
			if (i & (1<<k)) hi[i] = (1<<k);
		}
	}
	int T;
	scanf("%d", &T);
	FOR1(caseNo, T) {
		scanf("%d", &n);
		FOR(i, n) {
			vis[i].clear();
			scanf("%d", &a[i]);
		}
		vis[n].clear();
		if (!DP(0, 0, 0)) printf("no\n");
		else printf("%s\n", ans);
	}
	return 0;
}