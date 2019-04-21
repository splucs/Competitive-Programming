#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define mset(x, y) memset(&x, y, sizeof x)

int n, k;
int cnt[MAXN];

bool check() {
	int f = cnt[1];
	if (f == 0) return false;
	FOR1(i, k) if (cnt[i] != f) return false;
	return true;
}

int main() {
	while(scanf("%d %d", &k, &n) != EOF) {
		mset(cnt, 0);
		FOR(i, n) {
			int x;
			scanf("%d", &x);
			cnt[x]++;
		}
		int mi = 1;
		int ma = 1;
		FOR1(i, k) {
			if (cnt[i] > cnt[ma]) ma = i;
			if (cnt[i] < cnt[mi]) mi = i;
		}

		//+
		cnt[mi]++;
		if (check()) {
			printf("+%d\n", mi);
			continue;
		}
		cnt[mi]--;
		//-
		cnt[ma]--;
		if (check()) {
			printf("-%d\n", ma);
			continue;
		}
		cnt[ma]++;
		//-+
		cnt[ma]--;
		cnt[mi]++;
		if (check()) {
			printf("-%d +%d\n", ma, mi);
			continue;
		}

		printf("*\n");
	}
	return 0;
}