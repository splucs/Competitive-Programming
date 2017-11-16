#include <bits/stdc++.h>
using namespace std;
#define MAXN 69
typedef pair<int, int> ii;

ii val[MAXN];

int main() {
	int n;
	int sum = 0;
	scanf("%d", &n);
	for (int i = 0; i < n; i++) {
		scanf("%d", &val[i].first);
		val[i].second = i+1;
		sum += val[i].first;
	}
	sort(val, val + n);
	
	if (val[n-1].first*2 > sum) { printf("impossible\n"); return 0; }
	for (int i = n-1; i >= 0; i--) {
		if (i < n-1) printf(" "); 
		printf("%d", val[i].second);
	}
	printf("\n");
}