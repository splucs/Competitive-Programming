#include <set>
using namespace std;

/*
 * Longest Increasing Subsequence O(nlogn)
 * At a given iteration i, k-th element (1-indexed) in set is the
 * smallest element that has a size k increasing subsequence ending in it
 */

int lis(int arr[], int n) {
	multiset<int> s;
	multiset<int>::iterator it;
	for(int i = 0; i < n; i++) {
		s.insert(arr[i]);
		it = s.upper_bound(arr[i]); //non-decreasing
		//it = ++s.lower_bound(arr[i]); //strictly increasing
		if (it != s.end()) s.erase(it);
	}
	return s.size();
}

/*
 * TEST MATRIX
 */

#include <cstdio>
#define MAXN 500009

int a[MAXN], n;

int main() {
	while(scanf("%d", &n) != EOF) {
		for(int i = 0; i < n; i++) {
			scanf("%d", &a[i]);
		}
		printf("%d\n", lis(a, n));
	}
	return 0;
}