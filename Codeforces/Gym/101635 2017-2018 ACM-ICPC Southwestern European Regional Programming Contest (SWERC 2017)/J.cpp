#include <bits/stdc++.h>
#define MAXN 100009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FORN(i, j, n) for(int i = j; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;

int N, a[MAXN], b[MAXN];
ll dp[3];

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	cin>>N;
	FOR(i, N) cin>>a[i];
	FOR(i, N) cin>>b[i];
	FOR(j, 3){
		for (int i = j; i < N; i += 3){
			dp[j] += b[i];
		}
	}
	ll ans[3] = {};
	FOR(i, N){
		FOR(j, 3){
			ans[j] += 1LL * a[i] * dp[(j + 3 - i % 3) % 3];
		}
	}
	cout<<ans[1]<<' '<<ans[2]<<' '<<ans[0]<<'\n';
}