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

#include <cstdio>
#define MAXN 1000009

int a[MAXN], n;

int main() {
	n = 0;
	while(scanf("%d", &a[n]) != EOF) n++;
	for(int i = 0; i < n; i++) {
		scanf("%d", &a[i]);
	}
	printf("%d\n", n-lis(a, n));
	return 0;
}