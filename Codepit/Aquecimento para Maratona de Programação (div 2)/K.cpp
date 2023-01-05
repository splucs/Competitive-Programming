#include <bits/stdc++.h>
using namespace std;
#define MAXN 49

int N, F, arr[MAXN];
set<int> l, r;
char ans[MAXN];
bool pos[MAXN], neg[MAXN];

void fill(int i, int sum) {
	if (i == N/2) {
		l.insert(sum + arr[i]);
		l.insert(sum - arr[i]);
		return;
	}
	if (i == N) {
		r.insert(sum + arr[i]);
		r.insert(sum - arr[i]);
		return;
	}
	fill(i+1, sum+arr[i]);
	fill(i+1, sum-arr[i]);
}

bool check(int i, int sum) {
	if (i == N/2) {
		bool p = r.count(F - (sum + arr[i]));
		bool n = r.count(F - (sum - arr[i]));
		if (p) pos[i] = true;
		if (n) neg[i] = true;
		return p || n;
	}
	if (i == N) {
		bool p = l.count(F - (sum + arr[i]));
		bool n = l.count(F - (sum - arr[i]));
		if (p) pos[i] = true;
		if (n) neg[i] = true;
		return p || n;
	}
	bool p = check(i+1, sum+arr[i]);
	bool n = check(i+1, sum-arr[i]);
	if (p) pos[i] = true;
	if (n) neg[i] = true;
	return p || n;
}

int main() {
	while(scanf("%d %d", &N, &F), N||F) {
		for(int i=1; i<=N; i++) scanf("%d", &arr[i]);
		memset(&pos, false, sizeof pos);
		memset(&neg, false, sizeof neg);
		l.clear();
		r.clear();
		fill(1, 0);
		fill(N/2 + 1, 0);
		check(1, 0);
		check(N/2 + 1, 0);
		for(int i=1; i<=N; i++) {
			if (pos[i] && neg[i]) ans[i] = '?';
			else if (pos[i]) ans[i] = '+';
			else if (neg[i]) ans[i] = '-';
			else ans[i] = '*';
			if (ans[i] != '*') printf("%c", ans[i]);
		}
		if (ans[1] == '*') printf("*");
		printf("\n");
	}
	return 0;
}