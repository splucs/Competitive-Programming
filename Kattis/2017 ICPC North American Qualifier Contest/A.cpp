#include <bits/stdc++.h>
using namespace std;
#define MAXN 59

int N, M, R;
int cx[MAXN], cy[MAXN], mask[MAXN], a[MAXN], b[MAXN], c[MAXN];

bool intersection(int a1, int b1, int c1, int a2, int b2, int c2) {
	if (a1==a2 && b1==b2) return false;
	double x = (b2 *1.0* c1 - b1 *1.0* c2) / (a2 *1.0* b1 - a1 *1.0* b2), y;
	if (b1 != 0) y = -(a1 * x + c1) / b1;
	else y = -(a2 * x + c2) / b2;
	return hypot(x, y) < R;
}

int main() {
	scanf("%d %d %d", &N, &M, &R);
	for(int i=0; i<N; i++) {
		scanf("%d %d", &cx[i], &cy[i]);
	}
	int I = 1 + M;
	for(int i=0; i<M; i++) {
		scanf("%d %d %d", &a[i], &b[i], &c[i]);
		for(int j=0; j<i; j++) {
			if (intersection(a[i], b[i], c[i], a[j], b[j], c[j])) I++;
		}
	}
	
	bool ok = true;
	if (I != N) ok = false;
	
	for(int i=0; i<N; i++) {
		mask[i] = 0;
		for(int j=0; j<M; j++) {
			if (a[j]*cx[i] + b[j]*cy[i] + c[j] > 0) mask[i] |= (1<<j);
		}
	}
	sort(mask, mask+N);
	for(int i=1; i<N; i++) {
		if (mask[i] == mask[i-1]) ok = false;
	}
	
	if (ok) printf("yes\n");
	else printf("no\n");
	
	return 0;
}