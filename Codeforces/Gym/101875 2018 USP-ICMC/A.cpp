#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < int(n); i++)
#define MAXN 100009
#define pb push_back
typedef vector<int> vi;
typedef long long ll;

int main() {
	int n, k;
	cin >> n >> k;
	int g = __gcd(n, k);

	ll ans = 1LL*k*g*(n/g - 1) + 1LL*(g-1)*(k-1);
	cout << ans << endl;
}