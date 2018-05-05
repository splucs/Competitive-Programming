#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

struct present {
	int vol;
	int id;
};

present arr[MAXN];

bool idcomp(present a, present b) {
	return a.id < b.id;
}

bool volcomp(present a, present b) {
	if (a.vol == b.vol) return idcomp(a, b);
	return a.vol > b.vol;
}

int main() {
	int T, N, K;
	scanf("%d", &T);
	while(T --> 0) {
		scanf("%d %d", &N, &K);
		int h, l, w;
		for(int i = 0; i < N; i++) {
			scanf("%d %d %d %d", &arr[i].id, &h, &l, &w);
			arr[i].vol = h*l*w;
		}
		sort(arr, arr+N, volcomp);
		sort(arr, arr+K, idcomp);
		for(int i = 0; i < K; i++) {
			if (i > 0) printf(" ");
			printf("%d", arr[i].id);
		}
		printf("\n");
	}
	return 0;
}