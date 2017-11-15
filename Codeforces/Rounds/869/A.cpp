#include <bits/stdc++.h>
using namespace std;
#define MAXN 2009

int x[MAXN], y[MAXN], N;
set<int> s;

int main() {
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%d", &x[i]);
		s.insert(x[i]);
	}
	for(int i=0; i<N; i++) {
		scanf("%d", &y[i]);
		s.insert(y[i]);
	}
	int ans = 0;
	for(int i=0; i<N; i++) {
		for(int j=0; j<N; j++) {
			if (s.count(x[i]^y[j])) ans++;
		}
	}
	if (ans % 2 == 0) printf("Karen\n");
	else printf("Koyomi\n");
	return 0;
}