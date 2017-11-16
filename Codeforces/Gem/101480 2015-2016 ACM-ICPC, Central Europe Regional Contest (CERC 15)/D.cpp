#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define MOD 1000000007
#define MAXN 200001

int main() {
	int n, m;
	while(cin >> n >> m && n) {
	
	int especial = 0, acum = 0, v = 0;
	for (int i = 0; i < n; i++) {
		char c;
		cin >> c;
		v = c-'0';
		acum = (acum*10 + v)%m;
		if (acum == 0) {
			especial++;
		}
	}
	
	if (acum != 0) {
		cout << 0 << endl;
		continue;
	}
	
	ll ans = 1;
	for (int i = 0; i < especial - 1; i++) {
		ans *= 2;
		ans %= MOD;
	}
	cout << ans << endl;
	}
}