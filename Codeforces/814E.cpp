#include <bits/stdc++.h>
using namespace std;
#define MAXN 51
#define MOD 1000000007LL

typedef long long ll;

ll dp[MAXN][MAXN], dp2[MAXN][MAXN][MAXN][MAXN];
int d[MAXN], N;

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%d", &d[i]);
	}
	for(int i=N-1; i>=0; i--){
		for(int j=0; j<N; j++){
			for(int l=0; l<N; l++){
				for(int o=0; o<N; o++){
					if (j < i) dp2[i][j][l][o] = (o == 0);
					else {
						ll k = l+j-i;
						if (d[i] == 2){
							dp2[i][j][l][o] = (((k*(k-1)/2)%MOD)*dp2[i+1][j][l][o])%MOD;
							if (o >= 1) dp2[i][j][l][o] = (dp2[i][j][l][o] + ((k*o)%MOD)*dp2[i+1][j][l+1][o-1])%MOD;
							if (o >= 2) dp2[i][j][l][o] = (dp2[i][j][l][o] + ((o*(o-1)/2)%MOD)*dp2[i+1][j][l+2][o-2])%MOD;
						}
						else if (d[i] == 3){
							dp2[i][j][l][o] = (((k*(k-1)*(k-2)/6)%MOD)*dp2[i+1][j][l][o])%MOD;
							if (o >= 1) dp2[i][j][l][o] = (dp2[i][j][l][o] + ((k*(k-1)*o/2)%MOD)*dp2[i+1][j][l+1][o-1])%MOD;
							if (o >= 2) dp2[i][j][l][o] = (dp2[i][j][l][o] + ((k*o*(o-1)/2)%MOD)*dp2[i+1][j][l+2][o-2])%MOD;
							if (o >= 3) dp2[i][j][l][o] = (dp2[i][j][l][o] + ((o*(o-1)*(o-2)/6)%MOD)*dp2[i+1][j][l+3][o-3])%MOD;
						}
					}
				}
			}
		}
	}
	for(int i=N-1; i>=0; i--){
		for(int j=N-1; j>=i; j--){
			dp[i][j] = 0;
			int ni = j+1;
			for(int nj=ni; nj<N; nj++){
				dp[i][j] = (dp[i][j] + dp2[i][j][0][nj-ni+1]*dp[ni][nj])%MOD;
			}
		}
	}
	printf("%I64d\n", dp[0][0]);
	return 0;
}