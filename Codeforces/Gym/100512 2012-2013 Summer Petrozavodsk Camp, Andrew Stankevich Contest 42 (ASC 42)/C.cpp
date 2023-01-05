#include <bits/stdc++.h>
#define MAXN 200009
#define FOR(x,n) for(int x=0;x<n;x++)
using namespace std;
typedef pair<int,int> ii;

bool isSorted(vector<int>& vec) {
	for (int i = 1; i < vec.size(); i++) {
		if (vec[i-1] > vec[i]) return false;
	}
	return true;
}

void apply(vector<int> & arr, vector<ii>& perm) {
	FOR(k, perm.size()) {
		if (arr[perm[k].first - 1] > arr[perm[k].second - 1])
			swap(arr[perm[k].first - 1], arr[perm[k].second - 1]);
	}		
}

void print(vector<int> &arr) {
	FOR(k, arr.size()) {
		printf("%d ", arr[k]);
	}
	printf("\n");
}

int main() {
	freopen("comparator.in", "r", stdin);
	freopen("comparator.out", "w", stdout);

	int n;
	while (scanf("%d", &n) != EOF && n) {

		vector<int> input(n);
		vector<int> zeros, ones;

		FOR(i, n) {
			scanf("%d", &input[i]);
			if (input[i] == 0) zeros.push_back(i);
			else ones.push_back(i);
		}

		if (isSorted(input)) { printf("-1\n"); continue; }
		vector<ii> perm;
		for (int j = ones.size() - 1; j >= 0; j--) {
			for (int i = j-1; i >= 0; i--) {
				perm.push_back(ii(ones[i]+ 1, ones[j] + 1));
			}
		}
		for (int i = n-1; i >= 0; i--) {
			for (int j = i-1; j >= 0; j--) {
				if (!(input[j] == 1 && input[i] == 0)) perm.push_back(ii(j+1, i+1));
			} 
		}
		
		FOR(i, n) {
			FOR(j, n) {
				if (i == j || i == ones[0] || j == ones[0]) continue;
				perm.push_back(ii(min(i+1, j+1), max(i+1, j+1)));
			}
		}

		for (int i = 0; i < zeros.size(); i++) {
			for (int j = 0; j < zeros.size(); j++) {
				if (i == j) continue;
				perm.push_back(ii(min(i+1, j+1), max(i+1, j+1)));
			}
		}
		for (int i = 0; i < (int)zeros.size() - 1; i++) {
			perm.push_back(ii(i+1, zeros.size() + 1));
		}

		int nonSorted = 0;
		for (int msk = 0; msk < (1 << n); msk++) {
			vector<int> swapped, arr;
			FOR(k, n) {
				int v = 0;
				if ((1<<k)&msk) v = 1;
				swapped.push_back(v); arr.push_back(v);
			}

			apply(swapped, perm);
			if (!isSorted(swapped)) {
				nonSorted++;
			//	print(arr);
			//	print(swapped);
			}
		}

		if (nonSorted != 1) {
			printf("-1\n"); continue;
		}
		
		printf("%d\n", (int)perm.size());
		FOR(i, perm.size()) {
			printf("%d %d\n", perm[i].first, perm[i].second);
		}
	}
	fclose(stdin); fclose(stdout);
}