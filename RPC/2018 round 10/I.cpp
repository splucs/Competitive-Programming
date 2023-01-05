#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009
#define MAXM 10001009
#define INF 1e9
#define EPS 1e-9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)
#define pb push_back
#define L(N) N<<1
#define R(N) (N<<1) + 1
typedef long long int ll;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
const ll MOD = 1000000007;

set<int> valid = {2, 3, 5, 7, 13, 17, 19, 31, 61, 89, 107, 127, 521, 607, 1279};

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int t, a, b;
	while (scanf("%d%d", &a, &b) != EOF){
		if (valid.count(a + b)) printf("2^%d-1 is prime\n", a + b);
		else printf("2^%d-1 not prime\n", a + b);
	}
}
