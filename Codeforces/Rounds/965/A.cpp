#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
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

int ceil(int a, int b) {
	if (a % b == 0) return a/b;
	else return a/b + 1;
}

int main() {
	int k, n, s, p;
	scanf("%d %d %d %d", &k, &n, &s, &p);
	int pp = ceil(n, s);
	int np = ceil(pp*k, p);
	printf("%d\n", np);
}