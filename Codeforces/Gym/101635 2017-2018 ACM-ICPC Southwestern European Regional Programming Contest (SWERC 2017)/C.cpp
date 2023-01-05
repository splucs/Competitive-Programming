#include <bits/stdc++.h>
#define MAXN 2009
#define MOD 1000000000
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define sz(x) int(x.size())
using namespace std;
typedef long long ll;
typedef pair<int, int> ii;

int n;
ll m;

int encode(int code[]) {
	int ans = 0;
	REP(i, n) ans = 2*ans + code[i];
	return ans;
}

void decode(int mask, int code[]) {
	FOR(i, n) {
		code[i] = mask % 2;
		mask /= 2;
	}
}

typedef vector< vector<int> > matrix;

matrix operator * (matrix a, matrix b) {
	int s = sz(a);
	matrix c(s);
	FOR(i, s) {
		c[i].assign(s, 0);
		FOR(j, s) FOR(k, s) {
			c[i][j] = (c[i][j] + a[i][k]*1ll*b[k][j]) % MOD;
		}
	}
	return c;
}

matrix id(int s) {
	matrix c(s);
	FOR(i, s) {
		c[i].assign(s, 0);
		c[i][i] = 1;
	}
	return c;
}

matrix zeros(int s) {
	matrix c(s);
	FOR(i, s) c[i].assign(s, 0);
	return c;
}

matrix pow(matrix a, ll b) {
	if (b == 0) return id(sz(a));
	matrix c = pow(a, b/2);
	c = c*c;
	if (b % 2 != 0) c = c*a;
	return c;
}

matrix A;

int cur[8], prv[8];

void bt(int i) {
	if (i == n) {
		A[encode(prv)][encode(cur)]++;
		return;
	}
	if (prv[i]) {
		cur[i] = 0;
		bt(i+1);
	}
	else {
		//1x1
		cur[i] = 0;
		bt(i+1);

		//2x1
		if (i+1 < n && prv[i+1] == 0) {
			cur[i] = cur[i+1] = 0;
			bt(i+2);
		}

		//1x2
		cur[i] = 1;
		bt(i+1);
	}
}

int main() {
	scanf("%d %lld", &n, &m);
	A = zeros(1<<n);
	FOR(mask, (1<<n)) {
		decode(mask, prv);
		bt(0);
	}
	matrix ans = pow(A, m);
	printf("%d\n", ans[0][0]);
	return 0;
}