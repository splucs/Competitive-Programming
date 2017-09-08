#include <bits/stdc++.h>
using namespace std;
#define MAXN 500009

char txt[MAXN];
int a, b, nxt[MAXN], sz[MAXN];

inline int getsz(int i) {
	int ans = 0;
	while(txt[i] != ' ' && txt[i] > 0) {
		ans++;
		i++;
	}
	return ans;
}

int main() {
	while(gets(txt)) {
		//printf("|%s|\n", txt);
		scanf(" %d %d ", &a, &b);
		int last = 0, len = strlen(txt);
		sz[last] = getsz(last);
		for(int i=0; i<len; i++) {
			if (txt[i] == ' ') {
				last = i+1;
				sz[last] = getsz(last);
			}
			nxt[i] = last;
		}
		for(int m=a; m<=b; m++) {
			int ans = 0, i=0;
			//printf("m=%d:\n", m);
			while(true) {
				//printf("(%d) %s\n", sz[i], &txt[i]);
				if (ans > 0) ans++;
				ans += sz[i];
				i += m;
				if (i >= len) break;
				i = nxt[i];
			}
			printf("%d\n", ans);
		}
	}
	return 0;
}