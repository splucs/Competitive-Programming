#include <cstdio>
#define MAXN 1009

int main()
{
	int a[MAXN];
	int T, n, ans;
	scanf("%d", &T);
	a[0] = (1<<20);
	while(T-->0){
		scanf("%d", &n);
		ans=0;
		for(int i=1; i<=n; i++){
			scanf("%d", a+i);
		}
		for(int i=1; i<n; i++){
			for(int j=1; j<=i; j++){
				if (a[j] <= a[i+1]) ans++;
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}