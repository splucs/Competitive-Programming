#define MAXN 100009
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

char str[MAXN];
int n; // the length of input string
int RA[MAXN], tempRA[MAXN];
int SA[MAXN], tempSA[MAXN]; //SA: suffix array
int c[MAXN];

void countingSort(int k) { // O(n)
	int i, sum, maxi = max(300, n);
	memset(c, 0, sizeof c);
	for (i = 0; i < n; i++)  c[i + k < n ? RA[i + k] : 0]++;
	for (i = sum = 0; i < maxi; i++) {
		int t = c[i];
		c[i] = sum;
		sum += t;
	}
	for (i = 0; i < n; i++)  tempSA[c[SA[i] + k < n ? RA[SA[i] + k] : 0]++] = SA[i];
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
			(RA[SA[i]] == RA[SA[i - 1]] && RA[SA[i] + k] == RA[SA[i - 1] + k]) ? r : ++r;
		for (i = 0; i < n; i++)  RA[i] = tempRA[i];
		if (RA[SA[n - 1]] == n - 1) break;
	}
}

ii stringMatching(char* P) {
	int lo = 0, hi = n - 1, mid = lo;
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

int Phi[MAXN];
int LCP[MAXN], PLCP[MAXN];

//Longest Common Prefix
SA[i] and SA[i - 1]
void computeLCP() { //O(n)
	int i, L;
	Phi[SA[0]] = -1;
	for (i = 1; i < n; i++)  Phi[SA[i]] = SA[i - 1];
	for (i = L = 0; i < n; i++) {
		if (Phi[i] == -1) {
			PLCP[i] = 0; continue;
		}
		while (str[i + L] == str[Phi[i] + L]) L++;
		PLCP[i] = L;
		L = max(L - 1, 0);
	}
	for (i = 0; i < n; i++) LCP[i] = PLCP[SA[i]];
}

int LRS() {	//O(n)
	int lrs = 0;
	for (int i = 0; i<n; i++) if (LCP[i] > LCP[lrs]) lrs = i;
	return lrs;
}

int LCS(char* str1, char* str2) {
	int n1 = strlen(str1);
	strcpy(str, str1); strcat(str, "$");
	strcat(str, str2); strcat(str, "#");
	n = strlen(str);
	constructSA(); computeLCP();
	int ans = 0;
	for (int i = 1; i<n; i++) {
		if (LCP[i] > LCP[ans] &&
			((SA[i]<n1 && SA[i - 1]>n1) || (SA[i]>n1 && SA[i - 1]<n1))) {
			ans = i;
		}
	}
	return LCP[ans];
}