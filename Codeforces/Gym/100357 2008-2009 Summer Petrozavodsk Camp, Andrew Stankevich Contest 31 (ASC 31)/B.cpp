#include <bits/stdc++.h>
#define MAXN 509
#define ALFA 26
#define FOR(x, n) for(int x=0; x<n; x++)
#define REP(x, n) for(int x=n-1; x>=0; x--)
#define FOR1(x, n) for(int x=1; x<=n; x++)
#define REP1(x, n) for(int x=n; x>0; x--)
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define sz(x) (int (x.size()) )
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;
typedef pair<int, int> ii;

int m, n, h;
int cnt[MAXN];
int row[MAXN], col[MAXN];
char ans[MAXN][MAXN];
int st[MAXN];

bool comp(int i, int j) {
	return col[i] > col[j];
}

int main() {
	#ifdef ONLINE_JUDGE
	freopen("chip.in", "r", stdin);
	freopen("chip.out", "w", stdout);
	#endif

	scanf("%d %d %d", &n, &m, &h);
	FOR(i, n) {
		scanf("%d", &row[i]);
		row[i] = m - row[i];
	}
	FOR(j, m) {
		scanf("%d", &col[j]);
		st[j] = 0;
	}

	bool ok = true;
	FOR(i, n) {
		if (row[i] == 0) continue;
		if (row[i] < 0 || i+h-1 >= n) {
			ok = false;
			break;
		}
		for(int it = i+1; it < i+h; it++) {
			row[it] -= row[i];
		}
	}

	priority_queue<ii> pq;
	FOR(j, m) pq.push({col[j], j});

	mset(ans, '*');
	while(ok && !pq.empty()) {
		int j = pq.top().se;
		pq.pop();
		if (col[j] == 0) continue;
		int &i = st[j];
		while(i < n && !row[i]) i++;
		if (i == n) {
			ok = false;
			break;
		}
		row[i]--;
		col[j]--;
		pq.push({col[j], j});
		for(int it = i; it < i+h; it++) ans[it][j] = '|';
		ans[i][j] = '+';
		ans[i+h-1][j] = '+';
		i += h;
	}

	FOR(i, n) {
		ans[i][m] = 0;
		if (row[i] != 0) ok = false;
	}

	if (ok) {
		FOR(i, n) printf("%s\n", ans[i]);
	}
	else printf("inconsistent\n");

	return 0;
}