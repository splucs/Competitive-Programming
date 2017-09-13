#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

typedef long long ll;

struct point {
	ll x, y;
	point() {x = y = 0;}
	point (ll _x, ll _y) : x(_x), y(_y) {}
	point operator - (point o) {
		return point(x-o.x, y-o.y);
	}
} arr[MAXN];

ll cross(point p, point q) {
	return p.x*q.y - p.y*q.x;
}

int dp[MAXN], N;
point P[MAXN], A, B;

int DP(int n) {
	if (dp[n] >= 0) return dp[n];
	int ans = 1;
	for(int i=0; i<N; i++) {
		if (cross(P[n]-A, P[i]-A) <= 0 || cross(P[n]-B, P[i]-B) >= 0) continue;
		ans = max(ans, 1+DP(i));
	}
	return dp[n] = ans;
}

int main() {
	ll x, y;
	scanf("%d %lld %lld", &N, &x, &y);
	A = point(x, 0);
	B = point(y, 0);
	for(int i=0; i<N; i++) {
		scanf("%lld %lld", &x, &y);
		P[i] = point(x, y);
	}
	int ans = 0;
	memset(&dp, -1, sizeof dp);
	for(int i=0; i<N; i++) {
		ans = max(ans, DP(i));
	}
	printf("%d\n", ans);
	return 0;
}
