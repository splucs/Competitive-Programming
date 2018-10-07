#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
#define sz(x) int(x.size())
typedef long long ll;
typedef pair<int, int> ii;
typedef vector<int> vi;

int n, s, t;
double p;

double DP(int i, int j) {
	if (i >= n) return 1;
	if (i == 0 || j == 0) return 0;
	int y = min(i, n-i);
	return p*DP(i+y, j-1) + (1-p)*DP(i-y, j-1);
}

int main() {
	freopen("betting.in", "r", stdin);
	freopen("betting.out", "w", stdout);
	while(scanf("%d %d %lf %d", &n, &s, &p, &t), n) {
		p /= 100.0;
		printf("%.20f\n", DP(s, t));
	}
	return 0;
}