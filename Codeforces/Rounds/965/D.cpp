#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF (1<<30)
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

int n, l, a[MAXN];
int f[MAXN];

int main() {
	scanf("%d %d", &n, &l);
	FOR1(i, n-1) scanf("%d", &a[i]);
	memset(&f, 0, sizeof f);
	f[n] = INF;
	a[0] = INF;
	for(int i = n-1, j = n; i >= 0; i--) {
		while (i + l < j) j--;
		while(a[i] > 0 && j > i) {
			int df = min(a[i], f[j]);
			f[j] -= df;
			a[i] -= df;
			f[i] += df;
			if (f[j] == 0) j--;
		}
	}
	printf("%d\n", f[0]);
	return 0;
}