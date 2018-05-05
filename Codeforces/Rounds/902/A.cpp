#include <bits/stdc++.h>
using namespace std;

int main() {
	int N, F;
	scanf("%d %d", &N, &F);
	int cur = 0, x, y;
	for(int i = 0; i < N; i++) {
		scanf("%d %d", &x, &y);
		if (x <= cur) cur = max(cur, y);
	}
	if (F <= cur) printf("YES\n");
	else printf("NO\n");
	return 0;
}