#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define INF (1<<30)

int pascal[MAXN][MAXN];
map<int, int> comb;

vector<int> getdiv(int n) {
	vector<int> ans;
	for(int i=1; i*i <= n; i++) {
		if (n % i == 0) {
			ans.push_back(i);
			if (i*i<n) ans.push_back(n/i);
		}
	}
	sort(ans.begin(), ans.end());
	return ans;
}

int S[MAXN];

int main() {
	int T;
	scanf("%d", &T);
	for(int cases = 1; cases<=T; cases++) {
		scanf("%d", &S[cases]);
		vector<int> div = getdiv(S[cases]);
		for(int i=0; i<(int)div.size(); i++) {
			comb[div[i]] = div[i];
		}
	}
	for(int i=0; i<MAXN; i++) {
		for(int j=0; j<MAXN; j++) {
			if (j > i) pascal[i][j] = 0;
			else if (j == 0 || j == i) pascal[i][j] = 1;
			else pascal[i][j] = pascal[i-1][j-1] + pascal[i-1][j];
			if (pascal[i][j] > INF) pascal[i][j] = INF;
			if (i > 0 && comb.count(pascal[i][j])) {
				comb[pascal[i][j]] = min(comb[pascal[i][j]], i);
			}
		}
	}
	for(int cases = 1; cases<=T; cases++) {
		vector<int> div = getdiv(S[cases]);
		int ans = INF;
		for(int i=0; i<(int)div.size(); i++) {
			int u = div[i];
			int v = S[cases]/u;
			//printf("%d and %d -> %d\n", u, v, comb[u]+comb[v]);
			ans = min(ans, comb[u]+comb[v]);
		}
		printf("Case #%d: %d\n", cases, ans);
	}
	return 0;
}