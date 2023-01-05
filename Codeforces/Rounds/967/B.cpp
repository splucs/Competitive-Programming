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

int n, A, B, s[MAXN];

int main() {
	scanf("%d %d %d", &n, &A, &B);
	ll S = 0;
	priority_queue<int> pq;
	FOR1(i, n) {
		scanf("%d", &s[i]);
		S += s[i];
		if (i > 1) pq.push(s[i]);
	}
	int ans = 0;
	while(s[1]*1ll*A < B*1ll*S) {
		ans++;
		S -= pq.top();
		pq.pop();
	}
	printf("%d\n", ans);
	return 0;
}