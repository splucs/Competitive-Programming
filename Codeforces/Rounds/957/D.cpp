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

int arr[MAXN], tot[MAXN];

int main() {
	int N;
	scanf("%d", &N);
	tot[0] = 0;
	FOR1(i, N) {
		scanf("%d", &arr[i]);
		tot[i] = max(arr[i]+1, tot[i-1]);
	}
	for(int i = N-1; i>=1; i--) {
		tot[i] = max(tot[i+1]-1, tot[i]);
	}
	ll ans = 0;
	FOR1(i, N) {
		ans += tot[i] - arr[i] - 1;
	}
	printf("%I64d\n", ans);
	return 0;
}