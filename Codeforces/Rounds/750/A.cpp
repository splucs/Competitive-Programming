#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define MAXLOGN 22
#define MAXM (30*MAXN)
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

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	int cur = 60*20, limit = 60*24;
	int ans = 0;
	FOR1(i, n) {
		if (cur + k + 5*i <= limit) {
			cur += 5*i;
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}