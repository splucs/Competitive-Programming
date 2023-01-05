#define _CRT_SECURE_NO_WARNINGS
#define MAXN 100009
#include <algorithm>
#include <cstdio>
#include <cstring>
#include <string>
#include <set>
using namespace std;

/*
 * Suffix Array
 * Karp-Miller-Rosenberg's Algorithm (KMR) - O(n log n)
 * implementation adapted from Andrew Stankevich's class in Brazilian ICPC Summer School 2019
 */

int tsa[MAXN], c[MAXN], tc[MAXN], head[MAXN];

void bucket(int sa[], int n, int L) {
	memset(&head, 0, sizeof head);
	for (int i = 0; i < n; i++) head[c[i]]++;
	int maxi = max(300, n), k = 0;
	for (int i = 0; i < maxi; i++)
		swap(k, head[i]), k += head[i];
	for (int i = 0; i < n; i++) {
		int j = (sa[i] - L + n) % n;
		tsa[head[c[j]]++] = j;
	}
	memcpy(sa, tsa, n * sizeof(int));
}

void suffixArray(const char str[], int sa[]) {
	int n = strlen(str) + 1;
	for (int i = 0; i < n; i++)
		sa[i] = i, c[i] = str[i];
	bucket(sa, n, 0);
	for (int L = 1; L < n; L <<= 1) {
		bucket(sa, n, L);
		for (int i = 0, cc = -1; i < n; i++)
			tc[sa[i]] = (i == 0 || c[sa[i]] != c[sa[i - 1]] || c[(sa[i] + L) % n] != c[(sa[i - 1] + L) % n]) ? ++cc : cc;
		memcpy(c, tc, n * sizeof(int));
	}
	for (int i = 0; i < n - 1; i++) sa[i] = sa[i + 1];
}

int inv[MAXN];

void computeLcp(const char str[], int sa[], int lcp[]) {
	int n = strlen(str), k = 0;
	for (int i = 0; i < n; i++) inv[sa[i]] = i;
	for (int j = 0; j < n; j++) {
		int i = inv[j];
		if (k < 0) k = 0;
		while (i > 0 && str[sa[i] + k] == str[sa[i - 1] + k]) k++;
		lcp[i] = k--;
	}
}

int bound(char s[], char t[], int sa[], int n, int m, bool upper) {
	int hi = n, lo = -1;
	int khi = 0, klo = 0;
	while (hi > lo + 1) {
		int mid = (hi + lo) / 2;
		int i = sa[mid], k = min(klo, khi);
		while (k < m && s[i + k] == t[k]) k++;
		if (k == m && upper) lo = mid, klo = k;
		else if (k == m && !upper) hi = mid, khi = k;
		else if (s[i + k] > t[k]) hi = mid, khi = k;
		else lo = mid, klo = k;
	}
	return hi;
}

int match(char s[], char t[], int sa[], int n, int m) {
	int l = bound(s, t, sa, n, m, false);
	int r = bound(s, t, sa, n, m, true);
	return r - l;
}

string concat;
int sa[MAXN], lcp[MAXN], pos[MAXN], len[MAXN];

void addStringsToSA(int N, const char s[][MAXN]) {
	int j = 0;
	concat = "";
	for (int i = 0; i < N; ++i) {
		int n = strlen(s[i]) + 1;
		concat += string(s[i]) + "$";
		for (int k = 0; k < n; ++k) {
			pos[j] = i;
			len[j++] = n - k - 1;
		}
	}
	suffixArray(concat.c_str(), sa);
	computeLcp(concat.c_str(), sa, lcp);
}

void slide(set<pair<int, int> >& vals, string& ans, int& l, int* qty, int& cnt, int i, int N) {
	while (cnt == N || (lcp[i] <= (int)ans.size() && l < i)) {
		int u = sa[l];
		vals.erase({ lcp[l], l });

		if (cnt == N) {
			int n = vals.empty() ? len[u] : min(len[u], vals.begin()->first);
			if (n > (int) ans.size()) ans = concat.substr(u, n);
		}

		qty[pos[u]]--;
		if (qty[pos[u]] == 0) cnt--;
		++l;
	}
}

string getCommonSubstring(int N, const char s[][MAXN]) {
	addStringsToSA(N, s);

	string ans = "";
	int qty[21] = {}; // Must replaced 21 with the maximum value of N
	int cnt = 0, l = N;

	set<pair<int, int> > vals;

	lcp[concat.size()] = 0;
	for (int i = N; i < (int)concat.size(); ++i) {
		int u = sa[i];
		slide(vals, ans, l, qty, cnt, i, N);
		vals.insert({ lcp[i], i });
		qty[pos[u]]++;
		if (qty[pos[u]] == 1) cnt++;
	}
	slide(vals, ans, l, qty, cnt, concat.size(), N);

	return ans;
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
	Common substring manual test

	char p[21][MAXN];

	int main() {
		int N;

		scanf("%d", &N);

		for (int i = 0; i < N; ++i) {
			scanf("%s", p[i]);
		}
		printf("%s\n", getCommonSubstring(N, p).c_str());
	}
	*/
   /*
	* Codeforces 101711B
	*/

char str[MAXN];
int SA[MAXN], LCP[MAXN];

long long psum(int i) {
	if (i <= 0) return 0;
	return i * (i + 1LL) / 2;
}

int main() {
	scanf("%s", str);
	int n = strlen(str);
	suffixArray(str, SA);
	computeLcp(str, SA, LCP);
	long long ans = 0;
	for (int i = 0; i < n; i++) {
		ans += psum(n - SA[i]) - psum(LCP[i]);
	}
	printf("%lld\n", ans);
	return 0;
}
