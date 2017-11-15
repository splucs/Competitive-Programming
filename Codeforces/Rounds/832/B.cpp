#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

char P[MAXN], T[MAXN];
bool good[309];
int n, m, q;

bool match(int i, int j) {
	if (i > n || j > m) return false;
	if (i == n) return j == m;
	if (T[i] == P[j]) return match(i+1, j+1);
	if (T[i] == '?' && good[P[j]]) return match(i+1, j+1);
	if (T[i] == '*') {
		if (match(i+1, j)) return true;
		for(int k=1; k<=m-j && !good[P[j+k-1]]; k++) if (match(i+1, j+k)) return true;
	}
	return false;
}

int main() {
	scanf(" %s", T);
	n = strlen(T);
	memset(&good, false, sizeof good);
	for(int i=0; i<n; i++) {
		good[T[i]] = true;
	}
	scanf(" %s", T);
	n = strlen(T);
	scanf("%d", &q);
	while(q-->0) {
		scanf(" %s", P);
		m = strlen(P);
		if (match(0, 0)) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}