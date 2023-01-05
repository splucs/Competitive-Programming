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

int arr[MAXN];

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	memset(&arr, 0, sizeof arr);
	FOR(i, m) {
		int x;
		scanf("%d", &x);
		arr[x]++;
	}
	int ans = INF;
	FOR1(i, n) ans = min(ans, arr[i]);
	printf("%d\n", ans);
	return 0;
}