#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

bool pr[MAXN];
bool super(int N) {
	while(N > 0) {
		if (!pr[N%10]) return false;
		N /= 10;
	}
	return true;
}

int main() {
	memset(&pr, true, sizeof pr);
	pr[0] = pr[1] = false;
	for(int i=2; i<MAXN; i++) {
		if (pr[i]) {
			for(int j=2*i; j<MAXN; j += i) pr[j] = false;
		}
	}
	int n;
	while (scanf("%d", &n) != EOF) {
		if (!pr[n]) printf("Nada\n");
		else if (super(n)) printf("Super\n");
		else printf("Primo\n");
	}
	return 0;
}