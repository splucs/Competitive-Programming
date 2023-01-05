#include <bits/stdc++.h>
using namespace std;
#define MAXN 49

typedef long long ll;
set<ll> app;
ll arr[MAXN], M;
int N;
bool ans;

void backtrack(int i, ll sum) {
	if (i == N/2) {
		app.insert(sum);
		app.insert(sum + arr[i]);
		return;
	}
	if (i == N) {
		ans = ans || app.count(M-sum);
		return;
	}
	if (ans) return;
	backtrack(i+1, sum);
	if (ans) return;
	backtrack(i+1, sum + arr[i]);
}

int main() {
	scanf("%d %lld", &N, &M);
	for(int i=0; i<N; i++) scanf("%lld", &arr[i]);
	ans = false;
	backtrack(0, 0);
	backtrack(N/2+1, 0);
	if (ans) printf("sim\n");
	else printf("nao\n");
	return 0;
}