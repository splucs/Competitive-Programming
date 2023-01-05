#include <bits/stdc++.h>
using namespace std;

int main() {
	int N;
	while(scanf("%d", &N) != EOF) {
		int x;
		long long ans = 0;
		stack<int> s;
		for(int i=0; i<N; i++) {
			scanf("%d", &x);
			while(!s.empty() && s.top() >= x) {
				ans += s.top();
				s.pop();
			}
			s.push(x);
		}
		printf("%lld\n", ans);
	}
	return 0;
}