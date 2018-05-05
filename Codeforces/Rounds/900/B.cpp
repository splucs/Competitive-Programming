#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

bool app[MAXN];

int main() {
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	memset(&app, false, sizeof app);
	int ans = 0;
	while(!app[a]) {
		ans++;
		app[a] = true;
		a *= 10;
		if (a/b == c) {
			printf("%d\n", ans);
			return 0;
		}
		a %= b;
	}
	printf("-1\n");
	return 0;
}