#include <bits/stdc++.h>
using namespace std;
#define MOD 1000000007LL
#define MAXN 50

typedef unsigned long long ll;

map<vector<int>, ll> dp;
vector<int> cur;
set<ll> ans;
int D, H;

ll DP(vector<int> v) {
	sort(v.begin(), v.end());
	if (dp.count(v)) return dp[v];
	ll ans = 0;
	if (v[D-1] == 0) return dp[v] = 1;
	for(int i=0; i<D; i++){
		if (v[i] == 0) continue;
		v[i]--;
		ans += DP(v);
		v[i]++;
	}
	return dp[v] = ans;
}

void backtrack(const int i, const int left) {
	//printf("backtrack %d %d\n", i, left);
	if (i == D){
		if (left == 0){
			ll x = DP(cur);
			//for(int j=0; j<D; j++) printf("%d ", cur[j]);
			//printf(": dp = %I64d\n", x);
			ans.insert(x);
		}
		return;
	}
	for(cur[i] = (i==0?0:cur[i-1]); cur[i]<=left; cur[i]++){
		//printf("[%d,%d] : %d\n", i, left, cur[i]);
		backtrack(i+1, left-cur[i]);
	}
}

int main()
{
	scanf("%d %d", &D, &H);
	cur.resize(D);
	backtrack(0, H-1);
	for(set<ll>::iterator it = ans.begin(); it != ans.end(); it++) {
		printf("%I64d\n", *it);
	}
	return 0;
}