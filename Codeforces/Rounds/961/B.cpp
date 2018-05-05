#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 320
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-7
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int ans = 0;
int sum[MAXN], a[MAXN];

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	FOR1(i, n) scanf("%d", &a[i]);
	int ans = 0, mx = 0, t;
	FOR1(i, n) {
		scanf("%d", &t);
		if (t == 1) ans += a[i];
		else sum[i] += a[i];
	}
	sum[0] = 0;
	FOR1(i, n) sum[i] += sum[i-1];
	FOR1(i, n-k+1) mx = max(mx, sum[i+k-1] - sum[i-1]);
	ans += mx;
	printf("%d\n", ans);
	return 0;
}