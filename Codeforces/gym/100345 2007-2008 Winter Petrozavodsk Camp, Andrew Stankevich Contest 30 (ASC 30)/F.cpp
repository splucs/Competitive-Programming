#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
ll N;
int mex[10001];

void stevehalim() {
	int last = 0;
	for(int n=0; n<10000; n++) {
		if (n <= 1) {
			mex[n] = n;
		}
		else {
			set<int> jog;
			for(int k=1; k<=sqrt(n); k++) {
				jog.insert(mex[n-k]);
			}
			int cnt = 0;
			while(jog.count(cnt)) cnt++;
			mex[n] = cnt;
		}
		if (mex[n] == 0) {
			printf("mex[%d] = %d, delta = %d\n", n, mex[n], n-last);
			last = n;
		}
	}
}

bool ispow2(ll n) {
	return n == (n & -n);
}

int main() {
	freopen("nim.in", "r", stdin);
	freopen("nim.out", "w", stdout);
	
	scanf("%I64d", &N);
	if (N == 1) {
		printf("WIN\n");
		return 0;
	}
	int cnt = 0;
	ll cur = 2, delta = 2;
	//printf("%I64d %I64d\n", 0, 0);
	//printf("%I64d %I64d\n", cur, delta);
	while(cur < N) {
		if (ispow2(delta) || cnt == 2) {
			delta++;
			cnt = 0;
		}
		cur += delta;
		cnt++;
		//printf("%I64d %I64d\n", cur, delta);
	}
	if (cur == N) printf("LOSE\n");
	else printf("WIN\n");
		
	fclose(stdin);
	fclose(stdout);
	return 0;
}