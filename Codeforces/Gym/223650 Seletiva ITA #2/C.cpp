#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXLOGN 22
#define MAXM (30*MAXN)
#define MOD 1000000007
#define INF (1<<30)
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

int c[MAXN], d[MAXN], n;
int mn = -INF, mx = INF;

int main() {
	scanf("%d", &n);
	int cur = 0;
	c[0] = 0;
	FOR1(i, n) {
		scanf("%d %d", &c[i], &d[i]);
		c[i] += c[i-1];
	}
	FOR1(i, n) {
		if (d[i] == 2) mn = max(mn, c[i-1]+1);
		if (d[i] == 1) mx = min(mx, c[i-1]);
	}
	if (mx < mn) printf("Impossible\n");
	else if (mn == -INF) printf("Infinity\n");
	else {
		int d = 1900 - mn;
		mn += d;
		c[n] += d;
		printf("%d\n", c[n]);
	}
	return 0;
}