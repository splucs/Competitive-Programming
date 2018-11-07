#include <bits/stdc++.h>
#define MAXN 10000009
#define INF 0x3f3f3f3f
#define FOR(i, n) for(int i = 0; i < int(n); i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= int(n); i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define all(x) x.begin(), x.end()
using namespace std;
typedef vector<int> vi;


int main() {
	int n;
	int one = 0, two = 0;
	scanf("%d", &n);
	int val = 0;
	FOR(i, n) {
		scanf("%d", &val);
		if (val == 1) one++;
		else if (val == 2) two++;
	}
	if (one == n) {
		if (one%3 == 0) puts("Lose");
		else puts("Win");
	} else if (one == n-1) {
		puts("Win");
	} else if (one == n-2) {
		if (one%3 == 0) puts("Lose");
		else if (two >= 1) puts("Win");
		else puts("Lose");
	} else puts("Lose");
	return 0;
}