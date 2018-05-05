#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

int arr[MAXN], lf, rt, N, M, C;

void initialize() {
	lf = 0;
	rt = N-1;
	memset(&arr, -1, sizeof arr);
}

int insertlf(int col) {
	int lo = -1;
	int hi = lf;
	while(hi > lo + 1) {
		int mid = (hi + lo) / 2;
		if (arr[mid] > col) hi = mid;
		else lo = mid;
	}
	if (hi == lf) lf++;
	arr[hi] = col;
	return hi;
}

int insertrt(int col) {
	int lo = rt;
	int hi = N;
	while(hi > lo + 1) {
		int mid = (hi + lo) / 2;
		if (arr[mid] < col) lo = mid;
		else hi = mid;
	}
	if (lo == rt) rt--;
	arr[lo] = col;
	return lo;
}

int main() {
	scanf("%d %d %d", &N, &M, &C);
	initialize();
	int mc = C/2;
	while (rt >= lf) {
		int col, ans;
		scanf("%d", &col);
		if (col <= mc) ans = insertlf(col);
		else ans = insertrt(col);
		printf("%d\n", ans + 1);
		fflush(stdout);
	}
	return 0;
}