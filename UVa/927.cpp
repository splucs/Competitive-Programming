#include <cstdio>

typedef long long int ll;
int C, n, k, d, coef[25], id;

ll calculate(int q){
	ll ans = 0, po = 1;
	for(int i=0; i<=n; i++, po *= q)
		ans += coef[i]*po;
	return ans;
}

int main()
{
	scanf("%d", &C);
	while(C-->0){
		scanf("%d", &n);
		for(int i=0; i<=n; i++){
			scanf("%d", coef+i);
		}
		scanf("%d %d", &d, &k);
		id = 0;
		while(k>0){
			id++;
			k -= id*d;
		}
		printf("%lld\n", calculate(id));
	}
	return 0;
}