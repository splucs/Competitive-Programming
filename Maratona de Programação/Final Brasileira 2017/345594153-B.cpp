#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

char str[MAXN];

typedef long long ll;

bool isVocal(char c) {
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u'; 
}

int sum[MAXN];
int numVocal(int i, int j) {
	int ans = sum[j];
	if (i >0) ans -= sum[i-1];
	return ans;
}

ll solve(int i, int j, bool inv) {
	if (i >= j) return 1;
	if (!inv) {
		if (!isVocal(str[i])) {
			if (numVocal(i, j) == 0) return 1;
			else return 0;
		}
		ll ans = 0;
		
		for(; !isVocal(str[j]); j--) {
			ans += solve(i+1, j, !inv);
		}
		ans += solve(i+1, j, !inv);
		return ans;
	}
	
	else {
		if (!isVocal(str[j])) {
			if (numVocal(i, j) == 0) return 1;
			else return 0;
		}
		ll ans = 0;
		
		for(; !isVocal(str[i]); i++) {
			ans += solve(i, j-1, !inv);
		}
		ans += solve(i, j-1, !inv);
		return ans;
	}
}

int main() {
	scanf(" %s", str);
	int len = strlen(str);
	for(int i=0; i<len; i++) {
		sum[i] = 0;
		if (i > 0) sum[i] += sum[i-1];
		if (isVocal(str[i])) sum[i]++;
	}
	ll ans = solve(0, len-1, false);
	printf("%lld\n", ans);
	return 0;
}
