#include <bits/stdc++.h>
using namespace std;

typedef long long ll;

int main()
{
	int a, b, n, ans = 0, ma = 0;
	scanf("%d", &n);
	for(int i=0; i<n; i++){
		scanf("%d %d", &a, &b);
		if (a <= ma) continue;
		ans = max(ans, b);
		ma = a;
	}
	printf("%d\n", ans);
	return 0;
}