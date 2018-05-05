#include <bits/stdc++.h>
using namespace std;

int main() {
	int v1, v2, v3, vm;
	scanf("%d %d %d %d", &v1, &v2, &v3, &vm);
	bool ok = false;
	for(int c1 = max(v1, 2*vm+1); c1 <= 2*v1 && !ok; c1++) {
		for(int c2 = max(v2, 2*vm+1); c2 <= 2*v2 && c2 < c1 && !ok; c2++) {
			for(int c3 = max(v3, vm); c3 <= 2*v3 && c3 <= 2*vm && c3 < c2 && !ok; c3++) {
				ok = true;
				printf("%d\n%d\n%d\n", c1, c2, c3);
			}
		}
	}
	if (!ok) printf("-1\n");
	return 0;
} 