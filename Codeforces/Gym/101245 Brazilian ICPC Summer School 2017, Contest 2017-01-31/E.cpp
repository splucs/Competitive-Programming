#include <bits/stdc++.h>
using namespace std;
#define MAXN 2000009

void zfunction (char* s, int* z) {
	int n = strlen(s);
	fill(z, z+n, 0);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r)
			z[i] = min(r-i+1, z[i-l]);
		while (i+z[i] < n && s[z[i]] == s[i+z[i]])
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
}

int z[MAXN], prefix[MAXN], suffix[MAXN], K;
char T[MAXN], P[MAXN], S[MAXN];

int main() {	
	while(scanf(" %s %s %d ", T, P, &K) != EOF) {
		
		int n = strlen(T), m = strlen(P);
		strcpy(S, P);
		strcat(S, T);
		zfunction(S, z);
		for (int i = m; i<n+m; i++) {
			int j = i - m;
			prefix[j] = min(m, z[i]);
		}
		
		reverse(P, P+m);
		reverse(T, T+n);
		strcpy(S, P);
		strcat(S, T);
		zfunction(S, z);
		for (int i = m; i<n+m; i++) {
			int j = i-m;
			suffix[n-1-j] = min(m, z[i]);
		}
		
		vector<int> ans;
		for(int i=0; i<=n-m; i++) {
			if (prefix[i] + suffix[i+m-1] + K >= m) ans.push_back(i+1);
		}
		
		printf("%d\n", (int)ans.size());
		for(int i=0; i<(int)ans.size(); i++) {
			printf("%d ", ans[i]);
		}
		printf("\n");
	}
	return 0;
}