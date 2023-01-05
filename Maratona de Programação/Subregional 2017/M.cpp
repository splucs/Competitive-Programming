#include <bits/stdc++.h>
using namespace std;
#define INF (1<<30)

int main() {
	int ans = INF;
	int a, b, c;
	scanf("%d %d %d", &a, &b, &c);
	ans = min(ans, b + 2*c);
	ans = min(ans, b + 2*a);
	ans = min(ans, a+c);
	ans *= 2;
	printf("%d\n", ans);
	return 0;
}
