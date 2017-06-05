#include <cstdio>
#include <cstring>
#include <vector>
using namespace std;
#define MAXN 109
#define INF (1<<30)
#define min(a,b) (a>b?b:a)

int dp[MAXN][MAXN];
vector<int> divisors[MAXN];
char str[MAXN];

void calculatedivisors(){
	for(int n=0; n<MAXN; n++){
		divisors[n].resize(n);
		divisors[n].clear();
		for(int i=2; i*i<=n; i++){
			if (n%i==0){
				divisors[n].push_back(i);
				if (i*i!=n) divisors[n].push_back(n/i);
			}
		}
		divisors[n].push_back(n);
	}
}

int DP(int a, int b){
	if (dp[a][b]>=0) return dp[a][b];
	if (a==b) return dp[a][b]=1;
	int res = b-a+1, n = b-a+1, k, s;
	for(int i=a+1; i<=b; i++){
		res = min(res, DP(a, i-1)+DP(i, b));
	}
	bool valid;
	for(int iter=0; iter<(int)divisors[n].size(); iter++){
		valid = true;
		k = divisors[n][iter]; s = n/k;
		for(int i=1; valid && i<k; i++){
			for(int j=0; valid && j<s; j++){
				valid = (str[a+j]==str[a+j+s*i]);
			}
		}
		if (valid){
			res = min(res, DP(a, a+s-1));
		}
	}
	dp[a][b]=res;
	return res;
}

int main(){
	int n;
	calculatedivisors();
	while(scanf(" %s", str), str[0]!='*'){
		n = strlen(str);
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++) dp[i][j]=-1;
		}
		printf("%d\n", DP(0, n-1));
	}
	return 0;
}