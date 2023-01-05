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

int E[MAXN], N, U, k;

int main() {
	scanf("%d %d", &N, &U);
	double ans = -1.0;
	FOR1(i, N) scanf("%d", &E[i]);
	FOR1(i, N) {
		int lo = i+2;
		int hi = N+1;
		if (lo > N || E[lo] - E[i] > U) continue;
		while(hi > lo + 1) {
			int k = (hi + lo) / 2;
			if (E[k] - E[i] <= U) lo = k;
			else hi = k;
		}
		int k = lo;
		ans = max(ans, (E[k]-E[i+1])*1.0/(E[k]-E[i]));
	}
	if (ans > -0.5)	printf("%.18f\n", ans);
	else printf("-1\n");
	return 0;
}