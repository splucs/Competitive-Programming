#include <bits/stdc++.h>
using namespace std;
#define INF (1<<30)
#define MAXN 1000005
typedef long long ll;

ll C[20][20];

int main() {
	C[0][0] = 1;
	for (int i = 1; i < 20; i++) {
		C[i][0] = 1;
		for (int j = 1; j <= i; j++) {
			C[i][j] = C[i-1][j-1] + C[i-1][j];
		}
	}
	
	ll a, divisores = 0;
	ll i = 2, ans = 0;
	
	cin >> a;
	
	while(a > 1 && i < MAXN) {
		if (a%i == 0) {
			divisores++;
			while(a%i == 0) a /= i;
		}
		i++;
	}
	
	if (a != 1) divisores++;
	
	if (divisores == 0 || divisores == 1) cout << 0 << endl;
	else {
		ans = 0;
		for (int i = 2; i <= divisores; i++) {
			ans += C[divisores][i];
		}
		
		cout << ans << endl;
	}
}
