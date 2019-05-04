#define MAXN 100009
#include <algorithm>
#include <cstdio>
#include <cstring>
using namespace std;

/*
 * Suffix Array O(n log n) - Andrew Stankevich
 */

int tsa[MAXN], c[MAXN], tc[MAXN], head[MAXN];

void bucket(int sa[], int n, int L) {
	memset(&head, 0, sizeof head);
	for(int i = 0; i < n; i++) head[c[i]]++;
	int maxi = max(300, n), k = 0;
	for(int i = 0; i < maxi; i++)
		swap(k, head[i]), k += head[i];
	for(int i = 0; i < n; i++) {
		int j = (sa[i]-L+n)%n;
		tsa[head[c[j]]++] = j;
	}
	memcpy(sa, tsa, n*sizeof(int));
}

void suffixArray(char str[], int sa[]) {
	int n = strlen(str) + 1;
	for(int i = 0; i < n; i++)
		sa[i] = i, c[i] = str[i];
	bucket(sa, n, 0);
	for(int L = 1; L < n; L <<= 1) {
		bucket(sa, n, L);
		for(int i = 0, cc = -1; i < n; i++)
			tc[sa[i]] = (i == 0 || c[sa[i]] != c[sa[i-1]] || c[(sa[i]+L)%n] != c[(sa[i-1]+L)%n]) ? ++cc : cc;
		memcpy(c, tc, n*sizeof(int));
	}
	for(int i = 0; i < n-1; i++) sa[i] = sa[i+1];
}

int inv[MAXN];

int computeLcp(char str[], int sa[], int lcp[]) {
	int n = strlen(str), k = 0;
	for(int i = 0; i < n; i++) inv[sa[i]] = i;
	for(int j = 0; j < n - 1; j++) {
		int i = inv[j];
		if (k < 0) k = 0;
		while(i > 0 && str[sa[i]+k] == str[sa[i-1]+k]) k++;
		lcp[i] = k--;
	}
}

int lowerBound(char s[], char t[], int sa[], int n, int m) {
	int hi = n, lo = -1;
	int khi = 0, klo = 0;
	while(hi > lo + 1) {
		int mid = (hi + lo) / 2;
		int i = sa[mid], k = min(klo, khi);
		while(k < m && s[i+k] == t[k]) k++;
		if (k == m || s[i+k] > t[k])
			hi = mid, khi = k;
		else lo = mid, klo = k;
	}
	return hi;
}

int match(char s[], char t[], int sa[], int n, int m) {
	int l = lowerBound(s, t, sa, n, m);
	t[m-1]++;
	int r = lowerBound(s, t, sa, n, m);
	t[m-1]--;
	return r - l;
}

/*
 * TEST MATRIX
 */
/*
void printSA(char str[]) {
	int sa[100];
	int n = strlen(str);
	suffixArray(str, sa, n);
	for(int i = 0; i < n+1; i++) {
		printf("%2d %2d %s\n", i, sa[i], str+sa[i]);
	}
}

int main() {
	char str[100];
	scanf("%s", str);
	printSA(str);
	return 0;
}*/

/*
 * SPOJ SARRAY
 */ 
/*
char str[MAXN];
int sa[MAXN];

int main() {
	scanf(" %s", str);
	int n = strlen(str);
	suffixArray(str, sa);
	//constructSA(str, sa);
	for(int i = 0; i < n; i++) {
		printf("%d\n", sa[i]);
	}
	return 0;
}*/

/*
 * SPOJ STRMATCH
 */
/*
char s[MAXN], t[MAXN];
int sa[MAXN];

int main() {
	int n, q;
	scanf("%d %d %s", &n, &q, s);
	suffixArray(s, sa);
	while (q --> 0) {
		scanf(" %s", t);
		printf("%d\n", match(s, t, sa, n, strlen(t)));
	}
	return 0;
}*/

/*
 * Codeforces 101711B
 */

char str[MAXN];
int SA[MAXN], LCP[MAXN];

long long psum(int i) {
	if (i <= 0) return 0;
	return i*(i+1LL)/2;
}

int main() {
	scanf("%s", str);
	int n = strlen(str);
	suffixArray(str, SA);
	computeLcp(str, SA, LCP);
	long long ans = 0;
	for(int i = 0; i < n; i++) {
		ans += psum(n-SA[i]) - psum(LCP[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
