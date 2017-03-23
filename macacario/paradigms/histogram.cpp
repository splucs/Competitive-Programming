#include <cstdio>
#include <algorithm>
#define MAXN 100009
using namespace std;

typedef long long ll;

ll histogram(ll * vet, int a, int b){
	if (a>b) return 0;
	if (a==b) return vet[a];
	ll ans = 0, m;
	for(int i=a; i<=b; i++){
		m = min(m, vet[i]);
	}
	int l = a;
	for(int i=a; i<=b; i++){
		if (vet[i] == m){
			ans = max(ans, histogram(vet, l, i-1));
			l = i+1;
		}
	}
	if (vet[b] > m) ans = max(ans, histogram(vet, l, b));
	return max(m*(b-a+1), ans);
}

ll vet[MAXN];

int main(){
	int n;
	while(scanf("%d", &n), n){
		for(int i=0; i<n; i++){
			scanf("%lld", vet+i);
		}
		printf("%lld\n", histogram(vet, 0, n-1));
	}
	return 0;
}