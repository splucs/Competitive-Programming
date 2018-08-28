#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < int(n); i++)
#define FOR1(i, n) for(int i = 1; i <= int(n); i++)
#define MAXN 1000009
#define MAXLOGN 20
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef vector<int> vi;
typedef long long ll;
typedef pair<int, int> ii;

void zfunction(char s[], int z[]) {
	int n = strlen(s);
	fill(z, z+n, 0);
	for(int i = 1, l=0, r=0; i < n; i++) {
		if (i <= r) z[i] = min(r-i+1, z[i-l]);
		while(i+z[i] < n && s[z[i]] == s[i+z[i]]) z[i]++;
		if (i+z[i]-1 > r) l=i, r=i+z[i]-1;
	}
}

char s[MAXN];
int z[MAXN];

int main() {
	int n;
	while(scanf("%d %s", &n, s) != EOF) {
		FOR(i, n) s[i+n] = s[i];
		s[2*n] = '\0';
		zfunction(s, z);
		bool ok = true;
		FOR1(i, n-1) {
			if (z[i] < n && s[z[i]] > s[i+z[i]]) {
				ok = false;
			}
		}
		if (ok) printf("Yes\n");
		else printf("No\n");
	}
	return 0;
}