#include <cstdio>
#include <cstring>
#define MAXN 100009

int repetend(char* s) {
	int n = strlen(s);
	int nxt[n + 1];
	nxt[0] = -1;
	for (int i = 1; i <= n; i++) {
		int j = nxt[i - 1];
		while (j >= 0 && s[j] != s[i - 1])
			j = nxt[j];
		nxt[i] = j + 1;
	}
	int a = n - nxt[n];
	if (n % a == 0)
		return a;
	return n;
}