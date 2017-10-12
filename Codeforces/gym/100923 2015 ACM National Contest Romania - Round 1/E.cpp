#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define MOD 1000000007

typedef long long int ll;
int a[19][109];
typedef pair<int, int> ii;
vector<ii> inter;

int main(){	
	freopen("cifrul.in", "r", stdin);
	freopen("cifrul.out", "w", stdout);
	
	int T, N, M, K, D;
	scanf("%d", &T);
	while (T --> 0){
		scanf("%d %d %d %d", &N, &M, &K, &D);
		for(int j=0; j<M; j++) {
			for(int i=0; i<N; i++) {
				scanf("%d", &a[j][i]);
			}
		}
		
		ll ans = 0;
		for(int mask = 1; mask < (1<<M); mask++) {
			int cb = 0;
			ll prod = 1;
			for(int i=0; i<N; i++) {
				inter.clear();
				for(int j=0; j<M; j++) {
					if (!(mask & (1<<j))) continue;
					if (i == 0) cb++;
					int l = (a[j][i] - D + K) % K;
					int r = (a[j][i] + D) % K;
					//printf("(%d,%d)\n", l, r);
					if (r >= l) {
						inter.push_back(ii(0, l-1));
						inter.push_back(ii(r+1, K-1));
					}
					else {
						inter.push_back(ii(r+1, l-1));
					}
				}
				sort(inter.begin(), inter.end());
				int cur = 0;
				//printf("mask = %d\n", mask);
				for(int it=0; it<(int)inter.size(); it++) {
					if (it+1 < (int)inter.size() && inter[it].second > inter[it+1].second) swap(inter[it].second, inter[it+1].second);
					if (it+1 < (int)inter.size()) inter[it].second = min(inter[it].second, inter[it+1].first-1);
					cur += inter[it].second - inter[it].first + 1;
				}
				cur = K - cur;
				if (2*D + 1 > K) cur = K;
				//printf("cur = %d\n", cur);
				prod = (prod*cur)%MOD;
			}
			//printf("%I64d possibilities for %d\n", prod, mask);
			if (cb % 2 == 0) ans = (ans + MOD - prod) % MOD;
			else ans = (ans + prod) % MOD;
		}
		
		printf("%I64d\n", ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}