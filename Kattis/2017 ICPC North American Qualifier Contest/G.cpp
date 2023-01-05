#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, ll> ii;
map<ii, int> mp;
vector<ii> cat;

int main() {
	int N;
	ll ans = 0;
	scanf("%d", &N);
	for(int i=0; i<=2018; i++) {
		int j = sqrt(2018*2018 - i*i);
		if (j*j + i*i == 2018*2018) cat.push_back(ii(i, j));
	}
	ll x, y;
	for(int i=0; i<N; i++) {
		scanf("%lld %lld", &x, &y);
		for(int k=0; k<(int)cat.size(); k++) {
			if (mp.count(ii(x+cat[k].first, y+cat[k].second))) ans += mp[ii(x+cat[k].first, y+cat[k].second)];
			if (cat[k].second > 0 && mp.count(ii(x+cat[k].first, y-cat[k].second))) ans += mp[ii(x+cat[k].first, y-cat[k].second)];
			if (cat[k].first > 0 && mp.count(ii(x-cat[k].first, y+cat[k].second))) ans += mp[ii(x-cat[k].first, y+cat[k].second)];
			if (cat[k].first > 0 && cat[k].second > 0 && mp.count(ii(x-cat[k].first, y-cat[k].second))) ans += mp[ii(x-cat[k].first, y-cat[k].second)];
		}
		if (mp.count(ii(x, y))) mp[ii(x, y)]++;
		else mp[ii(x, y)] = 1;
	}
	
	printf("%lld\n", ans);
	return 0;
	
}