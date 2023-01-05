#include <bits/stdc++.h>
using namespace std;
#define MAXN 5009
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define PI (acos(-1.0))
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define sz(x) ((int)x.size())
typedef long long ll;
typedef pair<int,int> ii;

int p[402][52][52][52];
int d[59][59], ans[59];
char str[59], child[409][59];
int n, len[409], money[409];

int main() {
	int C;
	scanf(" %s %d", str, &C);
	n = strlen(str);
	FOR(i, C) {
		int j = 2*i;
		scanf(" %s %d", child[j], &money[j]);
		money[j + 1] = money[j];
		strcpy(child[j+1], child[j]);
		len[j] = len[j + 1] = strlen(child[j]);
		reverse(child[j+1], child[j+1] + len[j]);
	}
	C *= 2;

	FOR(s, n) {

		//p
		FOR(c, C) FOR(i, n) FOR(k, len[c]) {
			int j = i+s;
			if (j >= n || j-i < k) p[c][i][j][k] = -INF;
			else {
				p[c][i][j][k] = -INF;
				for(int it = j; it >= i+k; it--) {
					if (str[it] != child[c][k]) continue;

					int cur = 0;

					if (k > 0) cur += p[c][i][it-1][k-1];
					else if (it > i) cur += d[i][it-1];
					if (it < j) cur += d[it+1][j];

					if (p[c][i][j][k] < cur) p[c][i][j][k] = cur;
				}
			}
		}

		//d
		FOR(i, n) {
			int j = i+s;
			if (j >= n) break;
			d[i][j] = -INF;
			FOR(c, C) {
				int cur = money[c] + p[c][i][j][len[c]-1];
				if (d[i][j] < cur) d[i][j] = cur;
			}
		}
	}

	FOR(i, n) {
		if (i == 0) ans[i] = 0;
		else ans[i] = ans[i-1];

		if (ans[i] < d[0][i]) ans[i] = d[0][i];

		FOR(j, i) {
			int cur = d[j+1][i] + ans[j];
			if (ans[i] < cur) ans[i] = cur;
		}
	}

	printf("%d\n", ans[n-1]);
	return 0;
}