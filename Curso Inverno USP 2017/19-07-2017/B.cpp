#include <bits/stdc++.h>
using namespace std;
#define MAXN 3009

typedef long long ll;
map<ll, ll> app, app2;
ll arr[MAXN], arr2[MAXN*MAXN];
ll pascal[MAXN][5];
int N, M;

ll App2(ll a) {
	if (app2.count(a)) return app2[a];
	return 0;
}

ll App(ll a) {
	if (app.count(a)) return app[a];
	return 0;
}

ll solve3(ll l) {
	ll ans = 0;
	for(map<ll, ll>::iterator it = app.begin(); it != app.end(); it++) {
		ll s1 = it->first;
		ll s2 = l - s1;
		ll d = it->second*App2(s2) - it->second*App(s2-s1);
		ans += d;
		printf("%lld possibilidades pra soma3 = %lld, s1 = %lld\n", d, l, s1);
	}
	return ans;
}

ll solve2(ll l) {
	ll ans = 0, ans2 = 0;
	for(map<ll, ll>::iterator it = app.begin(); it != app.end(); it++) {
		ll s1 = it->first;
		ll s2 = l - s1;
		if (s1 > s2) break;
		ll d;
		if (s1 != s2){
			ans2 = App(s1)*App(s2)*(App2(l) - App(s1)*App(s2));
			ans += pascal[App(s1)][2]*pascal[App(s2)][2];
			//printf("%lld possibilidades para sum2 = %lld, s1=%lld, s2=%lld\n", d, l, s1, s2);
			//printf("pares s1+s2 = %lld, pares sem s1 e s2 = %lld\n", App(s1)*App(s2), (App2(l) - App(s1)*App(s2)));
		}
		else {
			ans2 += pascal[App(s1)][2]*(App2(l) - pascal[App(s1)][2]);
			ans += pascal[App(s1)][4];
			//printf("%lld possibilidades para sum2 = %lld, s1=s2=%lld\n", d, l, s1);
			//printf("pares s1+s1 = %lld, pares sem s1 e s2 = %lld\n", pascal[App(s1)][2], (App2(l) - pascal[App(s1)][2]));
		}
	}
	return ans2 / 2 + ans;
}

int main() {
	for(int n=0; n<MAXN; n++) {
		for(int k=0; k<5; k++) {
			if (n == k || k == 0) pascal[n][k] = 1;
			else if (k > n) pascal[n][k] = 0;
			else pascal[n][k] = pascal[n-1][k-1] + pascal[n-1][k];
		}
	}
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%d", &arr[i]);
		if (app.count(arr[i])) app[arr[i]]++;
		else app[arr[i]] = 1;
		for(int j=0, s; j<i; j++) {
			s = arr[i] + arr[j];
			if (app2.count(s)) app2[s]++;
			else app2[s] = 1;
		}
	}
	ll ans = 0, d;
	for(map<ll, ll>::iterator it = app.begin(); it != app.end(); it++) {
		if (it->second >= 2) {
			d = solve2(it->first)*pascal[it->second][2];
			ans += d;
			printf("%lld type 2 solutions for l = %lld\n", d, it->first);
		}
		if (it->second >= 3) {
			d = solve3(it->first)*pascal[it->second][2];
			ans += d;
			printf("%lld type 3 solutions for l = %lld\n", d, it->first);
		}
	}
	printf("%lld\n", ans);
	return 0;
}