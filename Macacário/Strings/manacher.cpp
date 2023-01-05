#include <cstdio>
#include <cstring>
#include <algorithm>
#define MAXN 3009
using namespace std;

/*
 * Manacher's Algorithm O(n)
 */

void manacher(char str[], int L[]) {
	int n = strlen(str), c = 0, r = 0;
	for(int i = 0; i < n; i++) {
		if(i < r && 2*c >= i) L[i] = min(L[2*c-i], r-i);
		else L[i] = 0;
		while(i-L[i]-1 >= 0 && i+L[i]+1 < n &&
			str[i-L[i]-1] == str[i+L[i]+1]) L[i]++;
		if(i+L[i]>r) { c=i; r=i+L[i]; }
	}
}

/*
 * Longest Palindromic Substring O(n)
 */

int LPS(char T[]) {
	int n = 2*strlen(T) + 1;
	char tmp[n+1];
	for(int i = 0, k = 0; T[i]; i++) {
		tmp[k++] = '|'; tmp[k++] = T[i];
	}
	tmp[n-1] = '|'; tmp[n] = '\0';
	int L[n], ans = 1;
	manacher(tmp, L);
	for(int i=0; i<n; i++)
		ans = max(ans, L[i]);
	return ans;
}