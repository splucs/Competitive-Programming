#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int rpos[MAXN];
int n;
ii c[MAXN];

int ceil(int a, int b) {
	if (a % b == 0) return a / b;
	return a / b + 1;
}

bool solve(int x1, int x2, bool invert) {
	int i1 = -1, di1, i2 = -1, di2;
	for(int i = n-1; i >= 0; i--) {
		if (i < n-1) rpos[i] = rpos[i+1];
		else rpos[i] = -1;
		if (c[i].first*1ll*(n-i) >= x2) rpos[i] = i;
	}
	FOR(i, n) {
		int di = ceil(x1, c[i].first);
		int j = i + di;
		if (j < n && rpos[j] != -1) {
			i1 = i;
			di1 = di;
			i2 = rpos[j];
			di2 = n - i2;
			break;
		}
	}
	if (i1 == -1) {
		return false;
	}
	else {
		printf("Yes\n");
		if (invert) {
			swap(i1, i2);
			swap(di1, di2);
		}
		printf("%d %d\n", di1, di2);
		for(int i = i1; i < i1+di1; i++) printf("%d ", c[i].second);
		printf("\n");
		for(int i = i2; i < i2+di2; i++) printf("%d ", c[i].second);
		printf("\n");
	}
}

int main() {
	int x1, x2;
	scanf("%d %d %d", &n, &x1, &x2);
	FOR(i, n) {
		scanf("%d", &c[i].first);
		c[i].second = i+1;
	}
	sort(c, c+n);
	if (!solve(x1, x2, false) && !solve(x2, x1, true)) printf("No\n");
	return 0;
}