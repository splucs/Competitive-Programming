#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int arr[MAXN];

int main() {
	int T, N;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		bool ok = true;
		for(int i=0; i<N; i++) {
			scanf("%d", &arr[i]);
			if (arr[i] % 2 != arr[0] % 2) ok = false;
		}
		if (ok) printf("yes\n");
		else printf("no\n");
	}
	return 0;
}