#include <bits/stdc++.h>
using namespace std;
#define MAXN 20009
#define INF (1<<30)

char belt[MAXN];

int main() {
	int T, ans, N, K, si, sj;
	char cur;
	scanf("%d", &T);
	while(T --> 0) {
		scanf("%d %d", &N, &K);
		scanf(" %s", belt);
		ans = 0;
		bool possible = false;
		for(si=0, sj=0; sj<N; sj++) {
			if (belt[si] != belt[sj]) si = sj;
			if (sj-si+1 == K) {
				possible = true;
				break;
			}
		}
		if (!possible){
			printf("-1\n");
			continue;
		}
		for(int i=0, j=-1; i<si; i++) {
			if (i <= j && belt[i] == cur) continue;
			ans++;
			cur = belt[i];
			j = i + K - 1;
		}
		for(int i=N-1, j=N; i > sj; i--) {
			if (i >= j && belt[i] == cur) continue;
			ans++;
			cur = belt[i];
			j = i - K + 1;
		}
		printf("%d\n", ans+1);
	}
	return 0;
}