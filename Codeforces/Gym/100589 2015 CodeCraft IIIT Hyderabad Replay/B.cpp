#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define MAXN 100009

int acum[24*60*60 + 1000];

bool isPalindrom(char* w, int n) {
	int i = 0, j = n-1;
	while (i < j) {
		if (w[i] != w[j]) return false;
		i++; j--;
	}
	return true;
}

int get(int h, int m, int s) {
	return h*60*60 + m*60 + s;
}
int main() {
	char w[20];
	FOR(h, 24) {
		FOR(m, 60)
			FOR(s, 60) {
				sprintf(w, "%02d:%02d:%02d", h, m, s);
				int msk = get(h, m, s);
				
				if (isPalindrom(w, 8)) {	
					acum[msk]++;
				}
				if (msk > 0) acum[msk] += acum[msk-1];
			}
	}
	int t;
	scanf("%d", &t);
	while (t--) {
		int h1, h2, m1, m2, s1, s2;
		scanf("%d%*c%d%*c%d %d%*c%d%*c%d", &h1, &m1, &s1, &h2, &m2, &s2);
		int msk1 = get(h1, m1, s1);
		int msk2 = get(h2, m2, s2);

		int ans = acum[msk2];
		if (msk1 > 0) ans -= acum[msk1-1];
		printf("%d\n", ans);
	}
}