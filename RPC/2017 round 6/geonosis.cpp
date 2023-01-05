#include <bits/stdc++.h>
using namespace std;
#define MAXN 509

typedef long long ll;
int d[MAXN][MAXN];
int x[MAXN];
bool cut[MAXN];

int main(){
	int T, N;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		for(int i=0; i<N; i++) {
			for(int j=0; j<N; j++) {
				scanf("%d", &d[i][j]);
			}
		}
		for(int i=0; i<N; i++){
			scanf("%d", &x[i]);
			cut[i] = true;
		}
		ll ans = 0;
		for(int ki=N-1, k; ki>=0; ki--){
			k = x[ki];
			for(int i=0; i<N; i++) {
				for(int j=0; j<N; j++) {
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
				}
			}
			cut[k] = false;
			for(int i=0; i<N; i++) {
				for(int j=0; j<N; j++) {
					if (!cut[i] && !cut[j]) ans += d[i][j];
				}
			}
		}
		printf("%lld\n", ans);
	}
	return 0;
}