#include <cstdio>
#define MAXN 1000009

typedef long long ll;
ll foot[MAXN], floo[MAXN], chain[MAXN];

ll sqr(ll x){
	return x*x;
}

int main(){
	int N;
	scanf("%d", &N);
	for(int i=1; i<=N; i++){
		scanf("%I64d", &floo[i]);
	}
	for(int i=1; i<=N; i++){
		scanf("%I64d", &foot[i]);
	}
	for(int i=1; i<=N; i++){
		scanf("%I64d", &chain[i]);
	}
	ll distff = 0, distfc = 0;
	for(int i=1; i<=N; i++){
		distff += sqr(floo[i]-foot[i]);
		distfc += sqr(floo[i]-chain[i]);
	}
	if (distff > distfc) printf("MaratonIME\n");
	else printf("Yan\n");
	return 0;
}