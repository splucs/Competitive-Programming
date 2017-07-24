#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF (1LL << 30)

typedef long long ll;
ll A[MAXN], h, S;
int n;

int simulate(ll j) {
	ll cur = j*S;
	ll d = n*j;
	ll curh = h - (d*(d+1))/2;
	if (curh <= cur) return 0;
	for(int i=1; i<=n; i++) {
		cur += A[(i-1)%n];
		d++;
		curh -= d;
		if (curh <= cur) return i;
	}
	return -1;
}

int main() {
	scanf("%d %lld", &n, &h);
	S = 0;
	for(int i=0; i<n; i++) {
		scanf("%lld", &A[i]);
		S += A[i];
	}
	ll lo = -1;
	ll hi = INF;
	while(hi > lo+1) {
		ll mid = (hi+lo)/2;
		//printf("mid = %lld\n", mid);
		if (simulate(mid) == -1) lo = mid;
		else hi = mid;
	}
	/*for(ll i=0; i<10; i++) {
		printf("simulate(%lld)=%d\n", i, simulate(i));
	}*/
	printf("%lld\n", max(1LL, n*hi + simulate(hi)));
	return 0;
}