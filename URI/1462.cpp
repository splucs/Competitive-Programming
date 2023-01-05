#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

typedef long long ll;
ll d[MAXN], pd[MAXN];

ll Sum(int i, int j){
	if (j < i) return 0;
	return pd[j] - pd[i-1];
}

int main() {
	int N;
	while(scanf("%d", &N) != EOF) {
		for(int i=1; i<=N; i++) {
			scanf("%lld", &d[i]);
		}
		sort(d+1, d+1+N, greater<ll>());
		pd[0] = 0;
		for(int i=1; i<=N; i++){
			pd[i] = d[i] + pd[i-1];
		}
		
		bool possible = true;
		if (pd[N] % 2 != 0) possible = false;
		
		int p = N;
		for(int k=1; k<=N; k++){
			while(p > 0 && d[p] < k) p--;
			ll auxsum;
			if (p >= k) auxsum = (p-k)*1ll*k + Sum(p+1, N);
			else auxsum = Sum(k+1, N);
			if (pd[k] > k*1ll*(k-1) + auxsum) possible = false;
		}
		
		if (possible) printf("possivel\n");
		else printf("impossivel\n");
	}
	return 0;
}