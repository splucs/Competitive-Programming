#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

//Implementacao precisa ser otimizada, pode levar TLE se usar muita funcao...
int xw[MAXN], yw[MAXN], xb[MAXN], yb[MAXN];

int main()
{
	int N, M;
	while(scanf("%d %d", &N, &M)!=EOF) {
		for(int i=0; i<N; i++) {
			scanf("%d %d", &xb[i], &yb[i]);
		}
		for(int j=0; j<M; j++) {
			scanf("%d %d", &xw[j], &yw[j]);
		}
		int ans = 0, K;
		for(int i=0; i<N; i++) {
			for(int j=0; j<i; j++) {
				for(int k=0; k<j; k++) {
					K = 0;
					for(int w=0; w<M; w++){
						if(abs(xb[i]*yb[j] + xb[j]*yb[k] + xb[k]*yb[i] - yb[i]*xb[j] - yb[j]*xb[k] - yb[k]*xb[i])
							== abs(xw[w]*yb[j] + xb[j]*yb[k] + xb[k]*yw[w] - yw[w]*xb[j] - yb[j]*xb[k] - yb[k]*xw[w])
							+ abs(xb[i]*yw[w] + xw[w]*yb[k] + xb[k]*yb[i] - yb[i]*xw[w] - yw[w]*xb[k] - yb[k]*xb[i])
							+ abs(xb[i]*yb[j] + xb[j]*yw[w] + xw[w]*yb[i] - yb[i]*xb[j] - yb[j]*xw[w] - yw[w]*xb[i]))
							K++;
					}
					ans += K*K;
				}
			}
		}
		printf("%d\n", ans);
	}
	return 0;
}