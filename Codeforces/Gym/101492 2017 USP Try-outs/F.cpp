#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define EPS 1e-9
#define FOR(x, n) for(int x = 0; x < n; x++)

int main() {
	int n, score = 0;
	int x, y;
	scanf("%d", &n);
	FOR(i, 3) {
		scanf("%d %d", &x, &y);
		double dist = hypot(x, y);
		
		for (int s = 10; s > 0; s--) {
			if (dist <= (10-s+1)*n + EPS) { score += s; break; }
		}
		
	}
	printf("%d\n", score);
}