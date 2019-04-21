#include <bits/stdc++.h>
#define INF 1e9
#define EPS 1e-9
#define MAXN 10009
#define FOR(x,n) for(int x=0;x<n;x++)
using namespace std;
typedef long long int ll;

int N, c[MAXN], d[MAXN];
double dp[MAXN][7][130];
double mlt[7] = {1, 0.5, 0.25, 0.25, 0.25, 0.25, INF};

double solve(int i, int qty, int t){
	if (t >= 120) return solve(i, 0, 0);
	double &ans = dp[i][qty][t];
	
	if (abs(ans - INF) > EPS) return ans;
	
	double cost = mlt[qty] * c[i];
	if (qty < 5) ans = cost + solve(i + 1, qty + 1, t + d[i]);
	ans = min(ans, cost + solve(i + 1, 0, 0));
	
	return ans;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	cin>>N;
	FOR(i, N) cin>>d[i]>>c[i];
	FOR(i, N) FOR(k, 7) FOR(j, 130) dp[i][k][j] = INF;
	
	cout<<fixed<<setprecision(2);
	cout<<solve(0, 0, 0)<<'\n';
}
