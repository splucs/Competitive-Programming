#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 20
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
#define INF (1LL<<60)
#define MOD 1000000007
typedef long long ll;
typedef pair<int, int> ii;

struct query {
	int id, l, x, ans;
} qrs[MAXN];

bool idcomp(query a, query b) {
	return a.id < b.id;
}

bool lcomp(query a, query b) {
	return a.l < b.l;
}

int N, Q, a[MAXN], killer[MAXM];

int modExp(int a, int b) {
	if (b == 0) return 1;
	int c = modExp(a, b>>1);
	c = (c*1ll*c) % MOD;
	if (b & 1) c = (c*1ll*a) % MOD;
	return c;
}

int main() {
	scanf("%d %d", &N, &Q);
	memset(&killer, -1, sizeof killer);
	FOR(i, N) {
		scanf("%d", &a[i]);
	}
	FOR(q, Q) {
		scanf("%d %d", &qrs[q].l, &qrs[q].x);
		qrs[q].id = q;
		qrs[q].l--;
	}
	sort(qrs, qrs+Q, lcomp);
	int q = 0, nz = 0;
	FOR(i, N) {
		FOR(j, MAXM) {
			if (killer[j] != -1 && (a[i] & 1 << j)) {
				a[i] ^= a[killer[j]];
			}
		}
		FOR(j, MAXM) {
			if (killer[j] == -1 && (a[i] & 1 << j)) {
				killer[j] = i;
				FOR(it, i) {
					if ((a[it] & 1 << j)) a[it] ^= a[i];
				}
				break;
			}
		}
		if (a[i] == 0) nz++;
		while(q < Q && qrs[q].l < i) q++;
		while(q < Q && qrs[q].l == i) {
			int x = qrs[q].x;
			FOR(j, MAXM) {
				if (killer[j] != -1 && (x & 1 << j)) {
					x ^= a[killer[j]];
				}
			}
			if (x == 0) qrs[q].ans = modExp(2, nz);
			else qrs[q].ans = 0;
			q++;
		}
	}
	sort(qrs, qrs+Q, idcomp);
	FOR(q, Q) {
		printf("%d\n", qrs[q].ans);
	}
	return 0;
}