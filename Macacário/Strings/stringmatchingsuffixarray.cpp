#include <cstdio>
#include <cstring>
#include <utility>
#define MAXN 100009 // second approach: O(n log n)
#include <algorithm>
using namespace std;

typedef pair<int, int> ii;

char str[MAXN]; // the input string, up to 100K characters
int n; // the length of input string
int RA[MAXN], tempRA[MAXN]; // rank array and temporary rank array
int SA[MAXN], tempSA[MAXN]; // suffix array and temporary suffix array
int c[MAXN]; // for counting/radix sort

void countingSort(int k) { // O(n)
	int i, sum, maxi = max(300, n);
	memset(c, 0, sizeof c);
	for (i = 0; i < n; i++)  c[i + k < n ? RA[i + k] : 0]++;
	for (i = sum = 0; i < maxi; i++) {
		int t = c[i];
		c[i] = sum;
		sum += t;
	}
	for (i = 0; i < n; i++)  tempSA[c[SA[i]+k < n ? RA[SA[i]+k] : 0]++] = SA[i];
	for (i = 0; i < n; i++)  SA[i] = tempSA[i];
}

void constructSA() { //O(nlogn)
	int i, k, r;
	for (i = 0; i < n; i++) RA[i] = str[i];
	for (i = 0; i < n; i++) SA[i] = i;
	for (k = 1; k < n; k <<= 1) {
		countingSort(k);
		countingSort(0);
		tempRA[SA[0]] = r = 0;
		for (i = 1; i < n; i++)  tempRA[SA[i]] =
			(RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
		for (i = 0; i < n; i++)  RA[i] = tempRA[i];
		if (RA[SA[n-1]] == n-1) break;
	}
}

ii stringMatching(char* P) { // string matching in O(m log n)
	int lo = 0, hi = n-1, mid = lo;
	while (lo < hi) { // find lower bound
		mid = (lo + hi) / 2;
		int res = strncmp(str + SA[mid], P, m);
		if (res >= 0) hi = mid;
		else lo = mid + 1;
	}
	if (strncmp(str + SA[lo], P, m) != 0) return ii(-1, -1);
	ii ans; ans.first = lo;
	lo = 0; hi = n - 1; mid = lo;
	while (lo < hi) { // if lower bound is found, find upper bound
		mid = (lo + hi) / 2;
		int res = strncmp(str + SA[mid], P, m);
		if (res > 0) hi = mid;
		else lo = mid + 1;
	}
	if (strncmp(str + SA[hi], P, m) != 0) hi--; // special case
	ans.second = hi;
	return ans;
} // return lower/upperbound as first/second item of the pair, respectively

int main() {
	n = (int)strlen(gets(str)); // input T as per normal, without the ‘$’
	str[n++] = ’$’; // add terminating character
	constructSA();
	for (int i = 0; i < n; i++) printf("%2d\t%s\n", SA[i], str + SA[i]);
} // return 0;