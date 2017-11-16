#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
#define UNKNOWN -1
#define IMPOSSIBLE -2

typedef pair<int, int> ii;
ii dp[MAXN];
int N, t[MAXN];

int main() {
	while(scanf("%d", &N) != EOF) {
		for(int i=1; i<=N; i++) {
			scanf("%d", &t[i]);
		}

		dp[0] = ii(0, 0);
		t[0] = -5000;
		for(int i=1; i<=N; i++) {
			int j = i;
			while (j > 1 && t[j] - t[j-1] <= 1000) j--;
			if (i - j > 2) {
				dp[i] = ii(IMPOSSIBLE, IMPOSSIBLE);
				//printf("dp[%d] = %d,%d\n", i, dp[i].first, dp[i].second);
				continue;
			}
			
			if (i == j) {
				if (j > 1 && t[j] - t[j-1] < 2000) j--;
				else {
					dp[i] = ii(IMPOSSIBLE, IMPOSSIBLE);
					//printf("dp[%d] = %d,%d\n", i, dp[i].first, dp[i].second);
					continue;
				}
			}
			
			while (j > 1 && t[j] - t[j-1] <= 1000) j--;
			if (i - j > 2) {
				dp[i] = ii(IMPOSSIBLE, IMPOSSIBLE);
				//printf("dp[%d] = %d,%d\n", i, dp[i].first, dp[i].second);
				continue;
			}
			
			set<ii> pos;
			
			if (dp[j-1].first == IMPOSSIBLE) ;
			else if (dp[j-1].first == UNKNOWN) pos.insert(ii(UNKNOWN, UNKNOWN));
			else pos.insert(ii(dp[j-1].first+(i-j==2?0:1), dp[j-1].second+(i-j==2?1:0)));
			
			if (i-j == 1 && j > 1 && t[j] - t[j-1] < 2000) {
				j--;
				while (j > 1 && t[j] - t[j-1] <= 1000) j--;
				if (i - j == 2) {
					if (dp[j-1].first == IMPOSSIBLE) ;
					else if (dp[j-1].first == UNKNOWN) pos.insert(ii(UNKNOWN, UNKNOWN));
					else pos.insert(ii(dp[j-1].first, dp[j-1].second+1));
				}
			}
			
			if (pos.empty()) dp[i] = ii(IMPOSSIBLE, IMPOSSIBLE);
			else if (pos.size() > 1u) dp[i] = ii(UNKNOWN, UNKNOWN);
			else dp[i] = *pos.begin();
			
			//printf("dp[%d] = %d,%d\n", i, dp[i].first, dp[i].second);
		}
		
		if (dp[N].first == UNKNOWN) printf("Ambiguous\n");
		else if (dp[N].first == IMPOSSIBLE) printf("Impossible\n");
		else printf("Cars without trailers: %d\nCars with trailers: %d\n", dp[N].first, dp[N].second);
	}
	
	return 0;
}