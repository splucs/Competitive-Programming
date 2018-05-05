#include <bits/stdc++.h>
using namespace std;
#define INF (1<<30)

typedef long long ll;

int editdist(ll cur, ll num) {
	vector<int> dcur;
	while(cur > 0) {
		dcur.push_back(cur%10);
		cur /= 10;
	}
	vector<int> dnum;
	while(num > 0) {
		dnum.push_back(num%10);
		num /= 10;
	}
	for(int i = 0, j = 0; i < (int)dcur.size(); i++, j++) {
		while(j < (int)dnum.size() && dnum[j] != dcur[i]) j++;
		if (j == (int)dnum.size()) return INF;
	}
	return int(dnum.size()) - int(dcur.size());
}

int main() {
	ll N;
	int ans = INF;
	scanf("%I64d", &N);
	for(ll cur = 1; cur*cur <= N; cur++) {
		ans = min(ans, editdist(cur*cur, N));
	}
	if (ans == INF) printf("-1\n");
	else printf("%d\n", ans);
	return 0;
}