#define MAXN 100009 // second approach: O(n log n)
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

/*
 * Suffix Array
 */

class SuffixArray {
	int RA[MAXN], tempRA[MAXN];
	int tempSA[MAXN], c[MAXN], n;
	int Phi[MAXN], PLCP[MAXN]; //for LCP
	void countingSort(int k, int SA[]) { // O(n)
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
public:
	void constructSA(char str[], int SA[]) { // O(nlogn)
		int i, k, r; n = strlen(str);
		for (i = 0; i < n; i++) RA[i] = str[i];
		for (i = 0; i < n; i++) SA[i] = i;
		for (k = 1; k < n; k <<= 1) {
			countingSort(k, SA);
			countingSort(0, SA);
			tempRA[SA[0]] = r = 0;
			for (i = 1; i < n; i++)  tempRA[SA[i]] = (RA[SA[i]] == RA[SA[i-1]] && RA[SA[i]+k] == RA[SA[i-1]+k]) ? r : ++r;
			for (i = 0; i < n; i++)  RA[i] = tempRA[i];
			if (RA[SA[n-1]] == n-1) break;
		}
	}
	void computeLCP(char str[], int SA[], int LCP[]) { // O(n)
		int i, L; n = strlen(str);
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
};

char str[MAXN]; // the input string, up to 100K characters
int SA[MAXN], LCP[MAXN];
SuffixArray sa;

int main() {
	int n = (int)strlen(gets(str)); // input T as per normal, without the ‘$’
	//str[n++] = '$'; // add terminating character
	sa.constructSA(str, SA);
	sa.computeLCP(str, SA, LCP);
	for (int i = 0; i < n; i++) printf("%2d\t%2d\t%s\n", SA[i], LCP[i], str + SA[i]);
} // return 0;