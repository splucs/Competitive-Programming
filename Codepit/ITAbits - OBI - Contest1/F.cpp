#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 309
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define pf push_front
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

int main() {
	ll N, B, n, x, y;
	scanf("%lld %lld", &N, &B);
	n = 2 + sqrt(N*N - B);
	if ((N - n) % 2 != 0) n++;
	n += 2;
	if (n > N) n = N;
	x = y = (N - n) / 2 +1;
	B -= N*N - n*n + 1;
	while (B > 0) {
		x += min(n-1, B); B -= min(n-1, B);
		y += min(n-1, B); B -= min(n-1, B);
		x -= min(n-1, B); B -= min(n-1, B);
		y -= min(n-2, B); B -= min(n-2, B);
		if (B > 0) x++, B--;
		n -= 2;
	}
	printf("%lld %lld\n", y, x);
	return 0;
}