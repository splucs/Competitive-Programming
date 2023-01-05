#include <cstdio>
#include <algorithm>
#include <cmath>
using namespace std;
#define MAXN 300009

long long vet[MAXN];
	
int main(){
	int N;
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%lld", &vet[i]);
	}
	sort(vet, vet+N);
	long long ans = vet[N-1]*(vet[N-2]+vet[N-3]);
	for(int i=N-2; i>0; i--){
		if (i == 1) ans += vet[1]*vet[0];
		else ans += vet[i]*vet[i-2];
	}
	double dans = ans*0.5*sin(M_PI*2.0/N);
	printf("%.3f\n", dans);
	return 0;
}
