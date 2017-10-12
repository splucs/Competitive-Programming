#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

typedef long long ll;

int main() {
	freopen("perechi3.in", "r", stdin);
	freopen("perechi3.out", "w", stdout);
	
	int T;
	ll N;
	scanf("%d", &T);
	
	while(T --> 0) {
		scanf("%I64d", &N);
		ll ans = 0;
		ll sn = sqrt(N);
		for(ll i=1; i<=sn; i++) {
			ans += i*(N/i - N/(i+1));
			if(N/i > sn) ans += N/i;
		}
		printf("%I64d\n", ans);
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}