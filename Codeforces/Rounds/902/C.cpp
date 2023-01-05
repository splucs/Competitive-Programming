#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

int h[MAXN], first[MAXN], second[MAXN], N, p1[MAXN], p2[MAXN];

int main() {
	scanf("%d", &N);
	int k = 1;
	bool ok = true;
	for(int i = 0; i <= N; i++) {
		scanf("%d", &h[i]);
		first[i] = k;
		second[i] = k + (h[i] > 1 ? 1 : 0);
		for(int j = 0; j < h[i]; j++) {
			p1[k] = i > 0 ? first[i-1] : 0;
			if (!(j & 1)) p2[k] = i > 0 ? first[i-1] : 0;
			else {
				p2[k] = i > 0 ? second[i-1] : 0;
				if (i > 0 && second[i-1] != first[i-1]) ok = false;
			}
			k++;
		}
	}
	if (ok) printf("perfect\n");
	else {
		printf("ambiguous\n");
		for(int i = 1; i < k; i++) {
			printf("%d ", p1[i]);
		}
		printf("\n");
		for(int i = 1; i < k; i++) {
			printf("%d ", p2[i]);
		}
		printf("\n");
	}
	return 0;
}