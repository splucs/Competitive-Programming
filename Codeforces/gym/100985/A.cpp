#include <cstdio>

typedef long long ll;

ll gcd(ll x, ll y){
	if (y == 0) return x;
	else return gcd(y, x%y);
}

int main(){
	int n;
	ll a, b;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%I64d %I64d", &a, &b);
		if (gcd(a, b) == 1LL) printf("Nao\n");
		else printf("Sim\n");
	}
	return 0;
}