#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 100009

int vet[MAXN];

int main(){
	int n;
	scanf("%d", &n);
	vet[0] = vet[n+1] = 0;
	for(int i=1; i<=n; i++){
		scanf("%d", vet+i);
	}
	for(int i=1; i<=n; i++){
		vet[i] = min(vet[i], 1+vet[i-1]);
	}
	for(int i=n; i>=0; i--){
		vet[i] = min(vet[i], 1+vet[i+1]);
	}
	int ans = 0;
	for(int i=1; i<=n; i++) ans = max(ans, vet[i]);
	printf("%d\n", ans);
	return 0;
}
