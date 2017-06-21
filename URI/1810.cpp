#include <cstdio>
#define min(a,b) (a>b?b:a)

int n, instancia=1;
int f[200], p[200], h[200], d[200], pd[200];
int PD(int k){
	if(k==n) return 0;
	if(pd[k]>=0) return pd[k];
	int res=d[k]*p[k] + PD(k+1), sum = d[k]*p[k];
	for(int i=k+1; i<n; i++){
		sum+=d[i]*(p[k]+h[k]-h[i]);
		res = min(res, sum + PD(i+1));
	}
	res+=f[k];
	pd[k]=res;
	return res;
}

int main()
{
	while(true){
		scanf("%d", &n);
		if(n==0) break;
		for(int i=0; i<n; i++){
			pd[i]=-1;
			scanf("%d %d %d %d", f+i, p+i, h+i, d+i);
		}
		for(int i=n-2; i>=0; i--){
			h[i]+=h[i+1];
		}
		printf("Instancia #%d\n%d\n\n", instancia++, PD(0));
	}
	return 0;
}