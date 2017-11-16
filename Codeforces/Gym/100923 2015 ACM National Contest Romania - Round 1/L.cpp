#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int main() {
	freopen("semipal.in", "r", stdin);
	freopen("semipal.out", "w", stdout);
	
	int T, N;
	unsigned long long K;
	scanf("%d", &T);
	char ans[MAXN];
	while(T --> 0) {
		scanf("%d %I64u", &N, &K);
		K--;
		
		for(int i = N-2; i>=0; i--) {
			ans[i] = (K&1ULL) + 'a';
			K /= 2;
		}
		ans[N-1] = ans[0];
		ans[N] = 0;
		
		printf("%s\n", ans);
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}