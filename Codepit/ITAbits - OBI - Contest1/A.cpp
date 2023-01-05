#include <bits/stdc++.h>
using namespace std;
#define MAXN 209
#define MAXM 309
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

int a[5];

int main() {
	FOR(i, 5) scanf("%d", &a[i]);
	bool inc = true, dec = true;
	FOR(i, 4) {
		if (a[i] > a[i+1]) inc = false;
		if (a[i] < a[i+1]) dec = false;
	}
	if (inc) printf("C\n");
	else if (dec) printf("D\n");
	else printf("N\n");
	return 0;
}