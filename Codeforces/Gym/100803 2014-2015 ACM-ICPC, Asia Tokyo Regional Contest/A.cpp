#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define sz(x) ((int)x.size())
typedef long long ll;

int compute(vector<int> a, vector<int> b) {
	int o1 = 0, o2 = 0;
	FOR(i, sz(a)) {
		if (a[i] == 1) o1++;
		if (b[i] == 1) o2++;
	}
	if (o1 != o2) return MAXN;

	int swaps = 0;
	FOR(i, sz(a)) {
		if (a[i] == b[i]) continue;
		int k = 0;
		for (int j = i+1; j < sz(a); j++) {
			swaps++;
			if(a[i] == b[j]) { k = j; break; }
		}
		swap(b[i], b[k]);
	}
	return swaps;
}

int main() {
	int n, m;
	scanf("%d %d", &n, &m);
	vector<int> input(n);
	vector<int> a, b;
	FOR(i, n) scanf("%d", &input[i]);
	FOR(i, m) {
		int val;
		scanf("%d", &val);
		while (val) {
			a.push_back(i%2);
			b.push_back((i+1)%2);
			val--;
		}
	}
	int ans = min(compute(a, input), compute(b, input));
	printf("%d\n", ans);
}