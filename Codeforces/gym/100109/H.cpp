#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

typedef long long ll;
ll w[MAXN], c[MAXN], sumw[MAXN], sumc[MAXN], k;
int n, m;

ll Sumw(int i, int j) {
	return sumw[j] - sumw[i-1];
}
ll Sumc(int i, int j) {
	return sumc[j] - sumc[i-1];
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	scanf("%d %d %I64d", &n, &m, &k);
	sumw[0] = sumc[0] = 0;
	for(int i=1; i<=n; i++) {
		scanf("%I64d %I64d", &w[i], &c[i]);
		sumw[i] = w[i] + sumw[i-1];
		sumc[i] = c[i] + sumc[i-1];
	}
	int ansx = 0, ansy = 0;
	ll ansc = 0;
	for(int x=0, y; x<n-m; x++) {
		if (Sumw(n-x-m+1, n-x) > k*Sumw(1, n-x-m)) break;
		ll curc = Sumc(n-x+1, n);
		int lo = 0;
		int hi = n-x-m;
		while(hi > lo+1) {
			int mid = (hi+lo)/2;
			if (Sumw(n-x-m+1, n-x) > k*Sumw(mid+1, n-x-m)) hi = mid;
			else lo = mid;
		}
		y = lo;
		curc += Sumc(1, y);
		if (curc > ansc) {
			ansx = x;
			ansy = y;
			ansc = curc;
		}
	}
	printf("%d %I64d\n", ansx+ansy, ansc);
	for(int x=0; x<ansx; x++) {
		printf("H");
	}
	for(int y=0; y<ansy; y++) {
		printf("T");
	}
	printf("\n", ansx+ansy, ansc);
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}