#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
#define MAXM ((1e+18) + 100)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;

char s[MAXN];

int main() {
	scanf("%s", s);
	int n = strlen(s);
	int na = 0, nb = 0, nc = 0;
	bool ok = true;
	for(int i = 0; i < n; i++) {
		if (s[i] == 'a') {
			na++;
			if (nb > 0 || nc > 0) ok = false;
		}
		if (s[i] == 'b') {
			nb++;
			if (nc > 0 || na == 0) ok = false;
		}
		if (s[i] == 'c') {
			nc++;
			if (na == 0 || nb == 0) ok = false;
		}
	}
	if (na == 0 || nb == 0) ok = false;
	if (nc != na && nc != nb) ok = false;
	if (ok) printf("YES\n");
	else printf("NO\n");
	return 0;
}