#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define between(x, y, z) (((x) > (y) && (y) > (z)) || ((x) < (y) && (y) < (z)))

int arr[MAXN], N, M;
bool pres[MAXN];

int main() {
	freopen("pinball.in", "r", stdin);
	freopen("pinball.out", "w", stdout);
	
	scanf("%d", &N);
	int ans = 0;
	for(int i=1; i<=N; i++) {
		scanf("%d", &arr[i]);
		pres[i] = true;
		ans++;
	}
	
	for(int i=2; i<N; i++) {
		if (pres[i] && between(arr[i-1], arr[i], arr[i+1])) {
			ans--;
			pres[i] = false;
		}
	}
	printf("%d\n", ans);
	
	scanf("%d", &M);
	for(int j=0, it, v; j<M; j++) {
		scanf("%d %d", &it, &v);
		arr[it] = v;
		for(int i=max(it-1, 2); i<=min(it+1, N-1); i++) {
			if (pres[i] && between(arr[i-1], arr[i], arr[i+1])) {
				ans--;
				pres[i] = false;
			}
			if (!pres[i] && !between(arr[i-1], arr[i], arr[i+1])) {
				ans++;
				pres[i] = true;
			}
		}
		printf("%d\n", ans);
	}

	fclose(stdin);
	fclose(stdout);
	return 0;
}