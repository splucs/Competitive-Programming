#include <bits/stdc++.h>
using namespace std;
#define MAXK 19
#define INF (1LL<<60)

typedef long long ll;
ll N, K, dp[MAXK][9*MAXK + 1];

ll sless(ll N, int s) {
	int arr[MAXK], saux = s;
	ll Naux = N;
	for(int i=0; i<MAXK; i++) {
		arr[i] = Naux%10;
		Naux /= 10;
	}
	
	ll ans = 0;
	for(int k=MAXK-1; k>=0; k--) {
		for(int i=0; i<arr[k] && i<=saux; i++) {
			ans += dp[k][saux-i];
		}
		saux -= arr[k];
	}
	
	return ans;
}

int main() {
	scanf("%I64d %I64d", &N, &K);
	
	ll ans1, ans2;
	for(int k=0; k<MAXK; k++) {
		for(int s=0; s<=9*MAXK; s++) {
			if (k == 0) {
				if (s == 0) dp[k][s] = 1;
				else dp[k][s] = 0;
			}
			else {
				dp[k][s] = 0;
				for(int i=0; i<10 && i <= s; i++) {
					dp[k][s] += dp[k-1][s-i];
				}
			}
		}
	}
	
	ll Kaux = K;
	ans1 = 0;
	int sk = 0;
	while(Kaux > 0) { 
		sk += Kaux%10;
		Kaux /= 10;
	}
	for(int s=1; s<sk; s++) {
		ans1 += sless(N+1, s);
	}
	ans1 += sless(K+1, sk);
	printf("%I64d ", ans1);
	
	int anss;
	for(int s=1; s<INF; s++) {
		ll cur = sless(N+1, s);
		if (cur < K) {
			K -= cur;
		}
		else {
			anss = s;
			break;
		}
	}
	
	ll lo = 0;
	ll hi = N+1;
	while(hi > lo + 1) {
		ll mid = (hi + lo) / 2;
		if (sless(mid+1, anss) < K) lo = mid;
		else hi = mid;
	}
	
	printf("%I64d\n", hi);
	
	return 0;	
}