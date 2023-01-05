#include <bits/stdc++.h>
using namespace std;

int main() {
	int T, x, nplayers;
	scanf("%d", &T);
	for(int caseNo=1; caseNo <= T; caseNo++) {
		
		bool possible = true;
		scanf("%d", &nplayers);
		queue<int> deck[12];
		for(int i=0; i<52; i++) {
			scanf("%d", &x);
			deck[0].push(x%13);
		}
		int out = 0, cnt[12], ans[12];
		memset(&cnt, 0, sizeof cnt);
		
		for(int i=0, last = 0; out < nplayers && possible; i++) {
			
			if (i - last > 13*53) possible = false;
			
			for(int k=0; k<nplayers && possible; k++) {
				if (deck[k].empty()) continue;
				cnt[k] = (cnt[k]+1)%13;
				x = deck[k].front(); deck[k].pop();
				//printf("cnt[%d]=%d, x=%d\n", k, cnt[k], x);
				if (cnt[k] == x) {
					deck[k+1].push(x);
					last = i;
				}
				else deck[k].push(x);
				if (deck[k].empty() && k == out) {
					ans[k] = (cnt[k] == 0 ? 13 : cnt[k]);
					out++;
				}
			}
		}
		
		printf("Case %d:", caseNo);
		if (!possible) printf(" unwinnable\n");
		else {
			for(int k=0; k<nplayers; k++) {
				printf(" %d", ans[k]);
			}
			printf("\n");
		}
	}
	return 0;
}