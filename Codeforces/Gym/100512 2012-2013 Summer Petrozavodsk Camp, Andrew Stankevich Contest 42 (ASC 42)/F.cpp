#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) int(x.size())
typedef long long ll;
typedef vector<int> vi;

int dp[MAXN];

int solve(int n) {
	if (n <= 1) return 0;
	vi di;
	int ans = 0;
	for(int i = 2; i*i <= n; i++) {
		if (n % i == 0) {
			while(n % i == 0) {
				n /= i;
				ans++;
			}
		}
	}
	if (n > 1) ans++;
	return ans;
}

int main() {
	#ifdef ONLINE_JUDGE
	freopen("funny.in", "r", stdin);
	freopen("funny.out", "w", stdout);
	#endif
	int w, h;
	while(scanf("%d %d", &w, &h), w||h) {
		printf("%d %d - ", w, h);
		w = solve(w);
		h = solve(h);
		//printf("%d %d - ", w, h);
		if (w > h) printf("Vera\n");
		else printf("Harry\n");
	}
	return 0;
}