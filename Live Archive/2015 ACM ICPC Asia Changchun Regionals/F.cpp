#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF (1<<30)

int arr[MAXN];

int main() {
	int T, N;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d", &N);
		for(int i=1; i<=N; i++) scanf("%d", &arr[i]);
		arr[0] = -INF;
		arr[N+1] = INF;
		
		
		bool ok = false;
		for(int k=0; k<2 && !ok; k++) {
			ok = true;
			int removed = -1;
			for(int i=2; i<=N && ok; i++) {
				if (arr[i] < arr[i-1]) {
					if (removed != -1) ok = false;
					else removed = i;
				}
			}
			//printf("removed = %d\n", removed);
			if (removed == -1) break;
			if (ok && arr[removed-2] <= arr[removed-1] && arr[removed-1] <= arr[removed+1]) break;
			else if (ok && arr[removed-2] <= arr[removed] && arr[removed] <= arr[removed+1]) break;
			else ok = false;
			reverse(arr+1, arr+N+1);
		}
		if (ok) printf("YES\n");
		else printf("NO\n");
	}
	return 0;
}