#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009LL

typedef long long ll;
ll a, b, N, x, y;
set<ll> sy;
int points[10], appear[10];

void compute() {
	memset(&appear, 0, sizeof appear);
	int maxap = 0;
	while(y > 0) {
		appear[y%10]++;
		maxap = max(maxap, appear[y%10]);
		y /= 10;
	}
	for(int i=0; i<10; i++) {
		if (appear[i] == maxap) points[i]++;
	}
}

int main() {
	int T;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%I64d %I64d %I64d", &a, &b, &N);
		sy.clear();
		for(x = 1; x<=MAXN; x++) {
			y = a*x*x + b*x;
			if (y < 0) y = -y;
			if (y <= N) sy.insert(y);
		}
		if (sy.empty()) {
			printf("-1\n");
			continue;
		}
		memset(&points, 0, sizeof points);
		for(set<ll>::iterator it = sy.begin(); it != sy.end(); it++) {
			y = *it;
			//printf("y = %I64d\n", y);
			compute();
		}
		int maxap = 0;
		for(int i=0; i<10; i++) {
			maxap = max(maxap, points[i]);
		}
		for(int i=0; i<10; i++) {
			if (points[i] == maxap) {
				printf("%d ", i);
				break;
			}
		}
		printf("\n");
	}
	return 0;
}