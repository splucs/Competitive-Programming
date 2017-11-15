#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009

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

char str[MAXN];
int z[MAXN];

int main() {
	int T;
	scanf("%d", &T);
	for(int t=1; t<=T; t++) {
		scanf(" %s", str);
		int n = strlen(str);
		zfunction(str, z);
		int ans = 0;
		for(int i=1; i<n; i++) {
			if (i+z[i] == n) ans++;
		}
		printf("Case %d: %d\n", t, ans);
	}
	return 0;
}