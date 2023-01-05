#include <bits/stdc++.h>
using namespace std;
#define MAXN 30

#define FOR(i, n) for(int (i)=0; (i)<(n); (i)++)
#define FOR1(i, n) for(int (i)=1; (i)<=(n); (i)++)

int col[MAXN], nxt[MAXN], inv[MAXN], cur[MAXN];

bool check() {
	int last;
	FOR1(i, 24) {
		if ((i-1)%4 == 0) last = cur[i];
		if (cur[i] != last) return false;
	}
	return true;
}

int main() {
	FOR1(i, 24) scanf("%d", &col[i]);
	bool ok = false;

	FOR1(i, 24) nxt[i] = i;
	nxt[16] = 3;
	nxt[14] = 4;
	nxt[3] = 17;
	nxt[4] = 19;
	nxt[17] = 10;
	nxt[19] = 9;
	nxt[10] = 16;
	nxt[9] = 14;
	FOR1(i, 24) inv[nxt[i]] = i;
	FOR1(i, 24) cur[i] = col[nxt[i]];
	ok = ok  || check();
	FOR1(i, 24) cur[i] = col[inv[i]];
	ok = ok  || check();

	FOR1(i, 24) nxt[i] = i;
	nxt[1] = 5;
	nxt[3] = 7;
	nxt[5] = 9;
	nxt[7] = 11;
	nxt[9] = 24;
	nxt[11] = 22;
	nxt[24] = 1;
	nxt[22] = 3;
	FOR1(i, 24) inv[nxt[i]] = i;
	FOR1(i, 24) cur[i] = col[nxt[i]];
	ok = ok  || check();
	FOR1(i, 24) cur[i] = col[inv[i]];
	ok = ok  || check();

	FOR1(i, 24) nxt[i] = i;
	nxt[13] = 5;
	nxt[14] = 6;
	nxt[5] = 17;
	nxt[6] = 18;
	nxt[17] = 21;
	nxt[18] = 22;
	nxt[21] = 13;
	nxt[22] = 14;
	FOR1(i, 24) inv[nxt[i]] = i;
	FOR1(i, 24) cur[i] = col[nxt[i]];
	ok = ok  || check();
	FOR1(i, 24) cur[i] = col[inv[i]];
	ok = ok  || check();

	if (ok) printf("YES\n");
	else printf("NO\n");

	return 0;
}