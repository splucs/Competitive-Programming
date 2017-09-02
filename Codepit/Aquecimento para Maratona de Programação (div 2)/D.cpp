#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

multiset<int> ms;
int Q[MAXN];

int main() {
	int N, x;
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%d", &x);
		ms.insert(x);
	}
	for(int i=0; i<N; i++) {
		scanf("%d", &Q[i]);
	}
	sort(Q, Q+N);
	int ans = 0;
	for(int i=N-1; i>=0; i--) {
		multiset<int>::iterator it = ms.lower_bound(Q[i]);
		if (it == ms.begin()) {
			it = ms.end();
		}
		else {
			ans++;
		}
		it--;
		ms.erase(it);
	}
	printf("%d\n", ans);
	return 0;
}