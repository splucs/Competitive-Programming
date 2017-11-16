#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

class FenwickTree {
private:
	vector<int> ft;
public:
	FenwickTree(int n) {
		ft.assign(n + 1, 0);	//1-indexed
	}
	int rsq(int i) { // returns RSQ(1, i)
		i++;
		int sum = 0;
		while(i > 0){
			sum += ft[i];
			i -= (i & -i);
		}
		return sum;
	}
	int rsq(int i, int j){
		return rsq(j) - rsq(i - 1);
	}
	void update(int i, int v) {
		i++;
		while(i < (int)ft.size()) {
			ft[i] += v;
			i += (i & -i);
		}
	}
};

int N, l[MAXN], r[MAXN], c[MAXN], id[MAXN];
int arr[MAXN];

bool comp(int i, int j) {
	return r[i] < r[j];
}

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%d %d %d", &l[i], &r[i], &c[i]);
		id[i] = i;
	}
	sort(id, id+N, comp);
	FenwickTree ft(MAXN);
	memset(&arr, 0, sizeof arr);
	int ans = 0;
	for(int it=0, i; it<N; it++) {
		i = id[it];
		int m = c[i] - ft.rsq(l[i], r[i]);
		int j = r[i];
		while(arr[j] == 1) j--;
		while(m --> 0) {
			ans++;
			arr[j] = 1;
			ft.update(j, 1);
			while(arr[j] == 1) j--;
		}
	}
	printf("%d\n", ans);
	return 0;
}