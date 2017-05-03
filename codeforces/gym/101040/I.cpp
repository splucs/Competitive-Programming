#include <cstdio>
#include <cmath>
#include <algorithm>
#include <stack>
using namespace std;
#define MAXN 509
#define INF (1<<30)

typedef long long ll;
ll dp[MAXN][MAXN], C[MAXN];
int A[MAXN][MAXN];

int main(){
	int N, K;
	scanf("%d %d", &N, &K);
	for(int i=1; i<=N; i++){
		scanf("%I64d", &C[i]);
	}
	for(int i=1; i<=N; i++){
		dp[i][1] = C[i];
		A[i][1] = 0;
	}
	for(int j=2; j<=K; j++){
		dp[j][j] = C[j] + dp[j-1][j-1];
		A[j][j] = j-1;
		for(int i=j+1; i<=N; i++){
			dp[i][j] = -INF;
			ll cur;
			for(int k=j-1; k<i; k++){
				cur = dp[k][j-1] - abs(C[i]-C[k])*(i-k-1) + C[i];
				if (cur > dp[i][j]){
					dp[i][j] = cur;
					A[i][j] = k;
				}
			}
		}
	}
	/*for(int j=1; j<=K; j++)
		for(int i=j; i<=N; i++){
			printf("dp[%d][%d] = %d  ", i, j, dp[i][j]);
			printf("A[%d][%d] = %d\n", i, j, A[i][j]);
		}*/
	int s = K;
	for(int i=K; i<=N; i++){
		if (dp[i][K] > dp[s][K]) s = i;
	}
	printf("%I64d\n", dp[s][K]);
	stack<int> sta;
	int k = K;
	while(s != 0){
		sta.push(s);
		s = A[s][k];
		k--;
	}
	while(!sta.empty()){
		printf("%d", sta.top());
		sta.pop();
		if (!sta.empty()) printf(" ");
	}
	printf("\n");
	return 0;
}