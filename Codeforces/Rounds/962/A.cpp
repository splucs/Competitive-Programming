#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

typedef long long ll;
ll a[MAXN];

int main() {
	int N;
	scanf("%d", &N);
	ll tot = 0;
	for(int i = 0; i < N; i++) {
		scanf("%I64d", &a[i]);
		tot += a[i];
	}
	ll cur = 0;
	for(int i = 0; i < N; i++) {
		cur += a[i];
		if (2*cur >= tot) {
			printf("%d\n", i+1);
			break;
		}
	}
	return 0;
}