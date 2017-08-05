#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
#define MAXN (1<<19)

double dp[MAXN];
int vet[20], N;

double DP(int mask){
	if (dp[mask] >= 0.0) return dp[mask];
	double ans = 0, aux;
	int n = 0, nleft, nright;
	for(int i=0; i<N; i++){
		if ((mask & (1<<i)) > 0) continue;
		n++;
		nleft = 0;
		nright = 0;
		for(int j=0; j<N; j++){
			if ((mask & (1<<j)) == 0) continue;
			if (vet[i] > vet[j]) nleft++;
			if (vet[i] < vet[j]) nright++;
		}
		aux = min(nleft, nright) + DP(mask | (1<<i));
		ans += aux;
	}
	if (n > 0) ans /= n;
	else ans = 0;
	dp[mask] = ans;
	return ans;
}

int main(){
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%d", vet+i);
	}
	memset(dp, -1.0, sizeof dp);
	printf("%.11f\n", DP(0));
	return 0;
}