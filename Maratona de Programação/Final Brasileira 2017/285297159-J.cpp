#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

bool possible[MAXN];
int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}
char word[MAXN];

bool check(int pos, int k, int n) {
	if (word[pos] == 'P') return false;
	int it = (pos+k)%n;
	
	while(it != pos) {
		if (word[it] == 'P') return false;
		it = (it+k)%n;
	}
	return true;
}
int main() {
	scanf("%s", word);
	
	int n = strlen(word);
	for (int i = 1; i*i <= n; i++) {
		if (n%i != 0) continue;
		
		possible[i] = false;
		for (int j = 0; j < i; j++) {
			if (check(j, i, n)) {
				possible[i] = true;
				break;
			}
		}
		
		if (i == n/i) continue;
		possible[n/i] = false;
		for (int j = 0; j < n/i; j++) {
			if (check(j, n/i, n)) {
				possible[n/i] = true;
				break;
			}
		}
	}
	
	int ans = 0;
	for (int i = 1; i < n; i++) {
		//printf("%d %d %d\n", i, n, gcd(i, n));
		if (possible[gcd(i, n)]) ans++;
	}
	printf("%d\n", ans);
	return 0;
}
