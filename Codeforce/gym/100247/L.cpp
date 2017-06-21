#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
map<ll, ll> dp;

vector<ll> factors(ll n)
{
	vector<ll> ans;
	for(int i=1; i*i <= n; i++){
		if (n%i == 0){
			ans.push_back(i);
			if(i*i != n) ans.push_back(n/i);
		}
	}
	return ans;
}

ll DP(ll n){
	if (n == 1) return 1;
	if (dp.count(n)) return dp[n];
	vector<ll> fac = factors(n);
	ll div, mult, ans = n;
	for(int i=0; i<(int)fac.size(); i++){
		div = fac[i];
		if (div == 1) continue;
		mult = div/2 + 1;
		ans = min(ans, mult*DP(n/div));
		//printf("dividing %I64d into %I64d yelds %I64d\n", n, div, mult*DP(n/div));
	}
	return dp[n] = ans;
}

int main()
{
	ll n;
	scanf("%I64d", &n);
	printf("%I64d\n", DP(n));
	return 0;
}