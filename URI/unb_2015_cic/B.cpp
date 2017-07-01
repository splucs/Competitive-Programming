#include <bits/stdc++.h>
#define MAXN 100009
using namespace std;

int comp(int a, int b){
	return max(a, b);
}

class FenwickTree {
	private: vector<int> ft;
	public: FenwickTree(int n) {
		ft.assign(n + 1, 0);	//1-indexed
	}
	int rsq(int i) { // returns RSQ(1, i)
		int ans = 0;
		while(i > 0){
			ans = comp(ans, ft[i]);
			i -= (i & -i);
		}
		return ans;
	}
	void update(int i, int v) {
		while(i < (int)ft.size()) {
			ft[i] = comp(v, ft[i]);
			i += (i & -i);
		}
	}
};

int arr[MAXN], A[MAXN];
int rnk[MAXN], invrank[MAXN], N;

bool rankcomp(int a, int b){
	if (arr[a] == arr[b]) return a<b;	//crescente
	//if (arr[a] == arr[b]) return a>b;	//estritamente crescente
	else return arr[a] < arr[b];
}

int MSIS(){
	for(int i=1; i<=N; i++) invrank[i] = i;
	sort(invrank+1, invrank+1+N, &rankcomp);
	for(int i=1; i<=N; i++) rnk[invrank[i]] = i;
	memset(&A, 0, sizeof A);
	FenwickTree ft(N);
	for(int i=1, j; i<=N; i++){
		j = rnk[i];
		A[j] = arr[i] + ft.rsq(j-1);
		ft.update(j, A[j]);
	}
	return ft.rsq(N);
}

int main() {
	int K;
	char c;
	while(scanf("%d %d", &N, &K) != EOF){
		for(int i=1; i<=N; i++){
			scanf(" %c", &c);
			arr[i] = 26 - (c-'a');
			//printf("arr[%d] = %d\n", i, arr[i]);
		}
		//printf("msis = %d\n", MSIS());
		if (MSIS() >= K) printf("Aceita\n");
		else printf("Rejeita\n");
	}
	return 0;
}