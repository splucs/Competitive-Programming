#include <bits/stdc++.h>
#define MAXN 100009
#define FOR(x,n) for(int x=0; x<n; x++)
#define FOR1(x,n) for(int x=1; x<=n; x++)
#define pb push_back
#define sz(x) ((int)x.size())
#define all(x) x.begin(),x.end()
using namespace std;
typedef pair<int,int> ii;

int k, p, x;

double check(double m) {
	return k*p/m + x*m;
}

int main() {
	int m;
	while(scanf("%d %d %d", &k, &p, &x) != EOF) {
		m = (int)sqrt(k*p*1.0/x);
		double ans = min(check(m), check(m+1));
		printf("%.3f\n", ans);
	}
	return 0;
}