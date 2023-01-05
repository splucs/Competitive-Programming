#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define ALFA 259

bool out[ALFA], app[ALFA];
char str[MAXN];

int main() {
	int N, ans = 0, cnt = 'z' - 'a' + 1;
	scanf("%d", &N);
	for(int q = 0; q < N; q++) {
		char op;
		scanf(" %c %s", &op, str);
		int len = strlen(str);
		memset(&app, false, sizeof app);
		for(int i = 0; i < len; i++) {
			app[str[i]] = true;
		}
		if (op == '!') {
			if (cnt == 1) ans++;
			for(char c = 'a'; c <= 'z'; c++) {
				if (!app[c]) {
					if (!out[c]) cnt--;
					out[c] = true;
				}
			}
		}
		if (op == '.') {
			for(char c = 'a'; c <= 'z'; c++) {
				if (app[c]) {
					if (!out[c]) cnt--;
					out[c] = true;
				}
			}
		}
		if (op == '?') {
			char c = str[0];
			if (!out[c]) {
				cnt--;
				out[c] = true;
			}
			else if (cnt == 1) ans++;
		}
		//printf("cnt = %d, ans = %d\n", cnt, ans);
	}
	printf("%d\n", ans);
	return 0;
}