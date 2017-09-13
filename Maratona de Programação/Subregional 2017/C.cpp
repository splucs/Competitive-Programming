#include <bits/stdc++.h>
using namespace std;
#define MAXN 10005
typedef long long int ll;
typedef pair<int, int> ii;

int cig[MAXN];
vector<ii> facs;

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}

ll mmc(int a, int b) {
	int g = gcd(a, b);
	ll ans = a/g;
	
	return ans*b;
}

ll compute(int n) {
	ll multiplier = 1;
	int tmp = 0, cnt = 0;
	for (int i = 0; i < n; i++) {
		for (int j = 0; j < (int)facs.size(); j++) {
			if (cig[i]%facs[j].first == 0) {
				cnt = 0;
				tmp = 1;
				while((cig[i]%facs[j].first) == 0) {
					cnt++;
					cig[i] /= facs[j].first;
					tmp *= facs[j].first;
				}
				multiplier = mmc(multiplier, tmp);
			}
		}
	}
	return multiplier;
}

int main() {
	int n, l;
	ll m = 1;
	scanf("%d %d", &n, &l);
	for (int i = 0; i < n; i++) {
		scanf("%d", &cig[i]);
		m = mmc(m, cig[i]);
	}
	
	int sol = 1, miss;
	for (int i = l; i >= (int)m; i--) {
		if (i%m == 0) {
			miss = i/m;
			if (miss == 1) {
				sol = 1;
				break;
			}
			
			int k = 2, cnt, saved = miss;
			while (miss > 1 && k < 1005) {
				if (miss%k == 0) {
					cnt = 0;
					while(miss%k == 0) {
						cnt++;
						miss /= k;
					}
					facs.push_back(ii(k, cnt));
				}
				k++;
			}
			if (miss > 1) { facs.push_back(ii(miss, 1)); }
			
			int multiplier = compute(n);
			sol = saved*multiplier;
			break;
		}
	}
	
	printf("%d\n", sol);
}
