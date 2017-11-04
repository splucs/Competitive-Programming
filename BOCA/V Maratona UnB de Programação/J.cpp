#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

bool equal(char a, char b) {
	if (a == '*' || b == '*') return true;
	return a == b;
}

void zfunction (char* s, int* z) {
	int n = strlen(s);
	fill(z, z+n, 0);
	for (int i=1, l=0, r=0; i<n; ++i) {
		if (i <= r)
			z[i] = min(r-i+1, z[i-l]);
		while (i+z[i] < n && equal(s[z[i]], s[i+z[i]]))
			++z[i];
		if (i+z[i]-1 > r)
			l = i,  r = i+z[i]-1;
	}
}

char T[MAXN], P[MAXN];
int z[MAXN];

int main() {
	while(scanf(" %s %s", T, P) != EOF) {

		int n = strlen(P);
		strcat(P, "$");
		strcat(P, T);
		zfunction(P, z);
		
		vector<int> ans;
		for(int i=1; P[n+i]; i++) {
			if (z[n+i] >= n) ans.push_back(i);
		}
	
		if (ans.empty()) printf("-1");
		for(int i=0; i<(int)ans.size(); i++) {
			if (i > 0) printf(" ");
			printf("%d", ans[i]);
		}
		printf("\n");
	}

	return 0;
}