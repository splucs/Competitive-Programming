#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXT 3000009

int t1[MAXN], t2[MAXN];

int main() {
	int X, Y, dx, dy, n1, n2;
	while(scanf("%d %d", &X, &Y) != EOF) {
		scanf("%d", &n1);
		for(int i=0; i<n1; i++) scanf("%d", &t1[i]);
		scanf("%d", &n2);
		for(int i=0; i<n2; i++) scanf("%d", &t2[i]);
		int u = 0, v = 0, t = 0;
		dx = dy = 0;
		bool collide = false;
		while(t < MAXT) {
			if (abs(X - Y) < 5) {
				printf("bumper tap at time %d\n", t-1);
				collide = true;
				break;
			}
			X += dx;
			Y += dy;
			if (u < n1 && t1[u] == t) dx = 1 - dx, u++;
			if (v < n2 && t2[v] == t) dy = 1 - dy, v++;
			t++;
		}
		if (!collide) printf("safe and sound\n");
	}
	return 0;
}