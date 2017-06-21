#include <cstdio>

int main(){
	int n, m, k;
	scanf("%d %d %d", &n, &m, &k);
	int required = (n*7)/10;
	if ((n*7)%10 != 0) required++;
	int left = n-m;
	if (k>required) required = k;
	if (required-k <= left) printf("%d\n", required-k);
	else printf("-1\n");
	k += n-m;
	printf("%d\n", (k*100)/n);
	return 0;
}