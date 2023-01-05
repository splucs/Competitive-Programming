#include <cstdio>
#include <map>
#include <vector>
using namespace std;
#define MAXN 1009
#define REM 1000000007

int arr[MAXN], N, M;	//arr 1-indexed!!
int dp[MAXN][MAXN];	//dp[i][j] = number of size j increasing subsequences ending at i

int comp(int a, int b) {
	return a+b;
}

class FenwickTree {
	private: vector<int> ft;
	public: FenwickTree(int n) {
		ft.assign(n + 1, 0);	//1-indexed
	}
	int rsq(int i) { // returns RSQ(1, i)
		int sum = 0;
		while(i > 0) {
			sum = comp(sum, ft[i]);
			i -= (i & -i);
		}
		return sum;
	}
	void update(int i, int v) {
		while(i < (int)ft.size()) {
			ft[i] = comp(v, ft[i]);
			i += (i & -i);
		}
	}
};

void solve(int * arr, int N, int M) {
	for(int i=1; i<=N; i++) dp[i][1] = 1;
	for(int p=2; p<=M; p++) {
		FenwickTree ft(N);
		for(int i=2; i<=N; i++) {
			ft.update(arr[i-1], dp[i-1][p-1]);
			dp[i][p] = ft.rsq(arr[i]-1);
		}
	}
}

int main() {
	int T;
	scanf("%d", &T);
	map<int, int> newarr;
	map<int, int>::iterator it;

	for(int caseNo=1; caseNo<=T; caseNo++) {
		scanf("%d %d", &N, &M);
		printf("Case #%d: ", caseNo);
		newarr.clear();
		for(int i=1; i<=N; i++) {
			scanf("%d", arr+i);
			newarr[arr[i]] = i;
		}
		int aux = 1;
		for(it = newarr.begin(); it!=newarr.end(); it++) {
			it->second = aux++;
		}
		for(int i=1; i<=N; i++) {
			arr[i] = newarr[arr[i]];
		}

		solve(arr, N, M);

		int ans = 0;
		for(int i=1; i<=N; i++) {
			ans = (ans+dp[i][M])%REM;
		}
		printf("%d\n", ans);
	}
	return 0;
}