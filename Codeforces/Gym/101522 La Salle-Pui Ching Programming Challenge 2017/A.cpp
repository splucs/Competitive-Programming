#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define FOR(x,n) for (int x = 0; x < n; x++)

	const int neutral = 0;

int comp(int a, int b){
	return a+b;
}

class FenwickTree {
private:
	vector<int> ft;
public:
	FenwickTree(int n) {
		ft.assign(n + 1, 0);	//1-indexed
	}
	int rsq(int i) { // returns RSQ(1, i)
		int sum = neutral;
		while(i > 0){
			sum = comp(sum, ft[i]);
			i -= (i & -i);
		}
		return sum;
	}
	int rsq(int i, int j){
		return rsq(j) - rsq(i - 1);
	}
	void update(int i, int v) {
		while(i < (int)ft.size()) {
			ft[i] = comp(v, ft[i]);
			i += (i & -i);
		}
	}
};

int D[MAXN];

int main() {
	int n;
	scanf("%d", &n);
	FOR(x,n) {
		scanf("%d", &D[x]);
	}
	
	sort(D, D+n);
	FenwickTree ft(100005);
	
	long long ans = 0;
	
	int max_month = 0;
	FOR(x, n) {
		for (int i = max_month; i < min(n, D[x]); i++) {
			max_month++;
			ft.update(1, 1);
			ft.update(D[i]+1, -1);
		}
			
		if (D[x] >= x+1) ans--;
		ans += ft.rsq(x+1);
	}
	printf("%I64d\n", ans);
}