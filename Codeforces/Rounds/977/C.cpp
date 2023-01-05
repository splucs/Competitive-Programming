#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
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
#define EPS 1e-9

int a[MAXN], n, k;

int main() {
	scanf("%d %d", &n, &k);
	FOR(i, n) scanf("%d", &a[i]);
	sort(a, a+n);
	if (k > 0) {
		k--;
		if (a[k] != a[k+1]) printf("%d\n", a[k]);
		else printf("-1\n");
	}
	else {
		if (a[0] > 1) printf("1\n");
		else printf("-1\n");
	}
	return 0;
}