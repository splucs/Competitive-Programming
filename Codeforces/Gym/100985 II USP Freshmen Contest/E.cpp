#include <cstdio>
#define MAXN 100009

long long a[MAXN], sum[MAXN];

int main(){
	int n, q;
	sum[0] = 0;
	scanf("%d %d", &n, &q);
	for(int i=1; i<=n; i++){
		scanf("%I64d", &a[i]);
		sum[i] = a[i] + sum[i-1];
	}
	int l, r;
	for(int i=0; i<q; i++){
		scanf("%d %d", &l, &r);
		if ((sum[r] - sum[l-1])%2 == 0) printf("Sim\n");
		else printf("Nao\n");
	}
	return 0;
}