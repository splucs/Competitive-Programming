#include <bits/stdc++.h>
using namespace std;
#define MAXN 300009
#define MAXM (30*MAXN)
#define MOD 1000000007
#define INF 1000000009
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pb push_back
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

char s[MAXN];

int main() {
	scanf("%s", s);
	int n = strlen(s);
	int co = 0, cd = 0;
	FOR(i, n) {
		if (s[i] == 'o') co++;
		if (s[i] == '-') cd++;
	}
	if (co == 0 || cd % co == 0) printf("YES\n");
	else printf("NO\n");
	return 0;
}