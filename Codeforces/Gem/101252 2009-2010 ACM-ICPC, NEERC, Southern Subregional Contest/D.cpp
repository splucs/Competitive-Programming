#include <bits/stdc++.h>
using namespace std;
#define MAXN 40000009

typedef long long ll;
typedef pair<int, int> ii;
ll A, B, C;

ll f(ll x){
	return (A*x + x%B)%C;
}

ii floydCycleFinding(ll x0) {
	// 1st part: finding k*start, hare’s speed is 2x tortoise’s
	ll tortoise = f(x0), hare = f(f(x0)); // f(x0) is the node next to x0
	int i = 0;
	while (tortoise != hare) {
		tortoise = f(tortoise);
		hare = f(f(hare));
		i++;
		if (i > MAXN) return ii(0, -1);
	}
	// 2nd part: finding start, hare and tortoise move at the same speed
	int start = 0; hare = x0;
	while (tortoise != hare) {
		tortoise = f(tortoise);
		hare = f(hare); start++;
	}
	// 3rd part: finding period, hare moves, tortoise stays
	int period = 1; hare = f(tortoise);
	while (tortoise != hare) { hare = f(hare); period++; }
	return ii(start, period);
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	scanf("%I64d %I64d %I64d", &A, &B, &C);
	ii ans = floydCycleFinding(1);
	int sr = ans.first + ans.second;
	if (sr > 20000000) sr = -1;
	printf("%d\n", sr);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}