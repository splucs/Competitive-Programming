#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

int main()
{
	int T, K, n, ans;
	char str[MAXN];
	scanf("%d", &T);
	for(int caseNo = 1; caseNo <= T; caseNo++){
		scanf(" %s %d", str, &K);
		n = strlen(str);
		ans = 0;
		for(int i=0; i<n-K+1; i++){
			if (str[i] == '-'){
				for(int j=0; j<K; j++){
					str[i+j] = (str[i+j] == '-' ? '+' : '-');
				}
				ans++;
			}
		}
		for(int i=n-K+1; i<n; i++) if (str[i] == '-') ans = -1;
		if (ans < 0) printf("Case #%d: IMPOSSIBLE\n", caseNo);
		else printf("Case #%d: %d\n", caseNo, ans);
	}
	return 0;
}