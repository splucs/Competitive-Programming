#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009
#define INF (1LL<<60)

typedef long long ll;
int N;
ll t[MAXN], start[MAXN], S, T;

ll simulate(ll x) {
	map<ll, int> s;
	for(int i=0; i<N; i++) {
		if (s.count(t[i])) s[t[i]]++;
		else s[t[i]] = 1;
	}
	ll ans = 0;
	while(!s.empty()) {
		map<ll, int>::iterator it = s.lower_bound(x);
		if (it == s.end()) it = s.begin();
		
		ans += (it->first - x + S)%S;
		x = it->first;
		it->second--;
		if (it->second == 0) s.erase(it);
		
		ans += T;
		x += T;
		x %= S;
	}
	return ans;
}

ll gcd(ll x, ll y) {
	if (y == 0) return x;
	return gcd(y, x%y);
}

int main() {
	
	scanf("%d %I64d %I64d", &N, &S, &T);
	for(int i=0; i<N; i++) {
		scanf("%d", &t[i]);
	}
	sort(t, t+N);
	
	ll mint = INF, maxt = -INF;
	for(int i=0; i<N; i++) {
		if (i>0 && t[i] == t[i-1]) {
			start[i] = start[i-1];
			continue;
		}
		ll cur = simulate(t[i]);
		start[i] = cur;
		mint = min(mint, cur);
		ll n = i > 0 ? t[i] - t[i-1] : t[0] - t[N-1] + S;
		n--;
		maxt = max(maxt, cur + n);
	}
		
	ll tot = 0;
	for(int i=0; i<N; i++) {
		if (i > 0 && t[i] == t[i-1]) continue;
		ll n = i > 0 ? t[i] - t[i-1] : t[0] - t[N-1] + S;
		n--;
		tot += (n+1)*start[i] + (n*(n+1))/2;
	}
	
	ll g = gcd(tot, S);
	tot /= g;
	S /= g;
	printf("%I64d\n%I64d\n", mint, maxt);
	printf("%I64d/%I64d\n", tot, S);
	
	return 0;
}