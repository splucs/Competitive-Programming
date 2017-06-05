#define MAXN 100009 // second approach: O(n log n)
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

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

int Phi[MAXN];
int LCP[MAXN], PLCP[MAXN];

//Longest Common Prefix
//LCP[i] keeps the size of the longest common prefix between SA[i] and SA[i-1]
void computeLCP() { //O(n)
	int i, L;
	Phi[SA[0]] = -1;
	for (i = 1; i < n; i++)  Phi[SA[i]] = SA[i-1];
	for (i = L = 0; i < n; i++) {
		if (Phi[i] == -1) {
			PLCP[i] = 0; continue;
		}
		while (str[i + L] == str[Phi[i] + L]) L++;
		PLCP[i] = L;
		L = max(L-1, 0);
	}
	for (i = 0; i < n; i++) LCP[i] = PLCP[SA[i]];
}

int main() {
	n = (int)strlen(gets(str)); // input T as per normal, without the ‘$’
	str[n++] = '$'; // add terminating character
	constructSA();
	computeLCP();
	for (int i = 0; i < n; i++) printf("%2d\t%2d\t%s\n", SA[i], LCP[i], str + SA[i]);
} // return 0;