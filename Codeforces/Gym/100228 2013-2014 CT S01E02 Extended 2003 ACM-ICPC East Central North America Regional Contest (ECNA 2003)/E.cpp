#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000001
#define INF (1<<30)
typedef long long ll;

vector<int> pol;

int compute(int val) {
	if (val == 0) return 0;
	
	int ans = 0;
	while(val != 0) {
		ans++;
		val /= 10;
	}
	return ans+1;
}

int main() {
	int n, coef, a0, sign;
	
	int contador = 1;
	while(cin >> n && n) {
		pol.clear();
		for (int i = 0; i < n; i++) {
			cin >> coef;
			pol.push_back(coef);
		}
		
		cin >> a0;
		cin >> sign;
		
		ll ans = 0, op = 0;
		
		ans += a0;
		if (sign < 0 && n%2 == 1) ans--;
		else ans++;
		
		op += 1 + 1 + compute(a0);
		
		for (int i = 1; i < pol.size(); i++) {
			op += 2 + compute(pol[i]);
			if (sign < 0 && (n-i)%2 == 1) ans -= pol[i];
			else ans += pol[i];
		}
		
		cout << "Polynomial " << contador++ << ": " << ans << " " << op << endl;
	}
}