#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main() {
	
	ll N;
	
	for(int caseNo=1; true; caseNo++) {
		scanf("%lld", &N);
		if (N == 0) break;
		
		bool printed = false;
		for(ll i=1; i*i <= N && !printed; i++) {
			ll j = sqrt(N - i*i);
			while(i*i + j*j < N) j++;
			if (i*i + j*j == N) {
				printf("Caso %d: %lld %lld\n", caseNo, max(i, j), min(i, j));
				printed = true;
			}
		}
		
		if (!printed) printf("Caso %d: metragem invalida\n", caseNo);
	}
	
	return 0;
}