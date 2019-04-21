#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

bool vis[MAXN][MAXN];
int len, N, p10[MAXN], arr[MAXN];
char str[MAXN];

bool bt(int i, int r) {
	if (i == len) {
		return r == 0;
	}
	if (vis[i][r]) return false;
	vis[i][r] = true;
	if (str[i] == '?') {
		for(int v=(i==0? 1 : 0); v<10; v++) {
			arr[i] = v;
			if (bt(i+1, (r + v*p10[len-i-1])%N)) return true;
		}
		return false;
	}
	else {
		int v = arr[i] = str[i]-'0';
		return bt(i+1, (r + v*p10[len-i-1])%N);
	}
}

int main() {
	scanf(" %s %d", str, &N);
	len = strlen(str);
	int p = 1;
	for(int i=0; i<=len; i++) {
		p10[i] = p;
		p = (p*10)%N;
	}
	
	bool ok = bt(0, 0);
	if (ok) {
		for(int i=0; i<len; i++) printf("%d", arr[i]);
		printf("\n");
	}
	else printf("*\n");
	
	return 0;
}
