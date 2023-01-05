#include <cstdio>
#define MAXN 100009

int n;
int vet[MAXN];

int bs(int l, int r, int x){
	if (l == r) return 1;
	int m = (l+r)/2;
	if (vet[m] == x) return 1;
	else if (vet[m] < x) return 1 + bs(m+1, r, x);
	else return 1 + bs(l, m-1, x);
}

int main(){
	scanf("%d", &n);
	for(int i=1; i<=n; i++){
		scanf("%d", &vet[i]);
	}
	int ans = 0, y;
	for(int i=1; i<=n; i++){
		y = bs(1, n, vet[i]);
		if (y > ans) ans = y;
	}
	printf("%d\n", ans);
	return 0;
}