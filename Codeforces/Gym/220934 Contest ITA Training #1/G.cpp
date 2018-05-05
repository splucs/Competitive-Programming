#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

typedef pair<int, int> ii;
set<ii> pres;
int x[MAXN], y[MAXN];

int main() {
	int N;
	scanf("%d", &N);
	for(int i = 0; i < N; i++) {
		scanf("%d %d", &x[i], &y[i]);
	}
	
	if (N <= 3) {
		bool ok = false;
		for(int i = 0; i < N; i++) {
			for(int j = 0; j < i; j++) {
				if (x[i] == x[j] && y[i] == y[j]) ok = true;
			}
		}
		if (ok) printf("1\n");
		else printf("0\n");
	}
	else {
		bool ok = false;
		for(int i = 0; i < N && !ok; i++) {
			for(int j = 0; j < i && !ok; j++) {
				if (pres.count(ii(x[i]+x[j], y[i]+y[j]))) ok = true;
				else pres.insert(ii(x[i]+x[j], y[i]+y[j]));
			}
		}
		if (ok) printf("1\n");
		else printf("2\n");
	}
	
	return 0;
}