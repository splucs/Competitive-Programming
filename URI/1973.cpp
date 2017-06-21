#include <cstdio>
#include <cstring>
#define MAXN 1000009

typedef long long ll;
ll ovelhas[MAXN];
bool roubado[MAXN];

int main(){
	int N;
	ll total=0;
	memset(&roubado, false, sizeof roubado);
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%lld", &ovelhas[i]);
		total += ovelhas[i];
	}
	int pos = 0, proxpos, nroubado=0;
	while(pos>=0 && pos<N){
		if (!roubado[pos]){
			nroubado++;
			roubado[pos]=true;
		}

		if(ovelhas[pos]%2==0) proxpos = pos-1;
		else proxpos = pos+1;

		if (ovelhas[pos]>0) {
			total--; ovelhas[pos]--;
		}
		pos = proxpos;
		
	}
	printf("%d %lld\n", nroubado, total);
	return 0;
}