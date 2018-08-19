#include <bits/stdc++.h>
#define FOR(x,n) for(int x=0;x<n;x++)
using namespace std;
#define MAXN 100009

int hanoi(int n, char from, char to, char mid, bool printans) {
	if (n == 0) return 0;
	int ans = 1;
	ans += hanoi(n-1, from, mid, to, printans);
	if (printans) printf("%c %c\n", from, to);
	ans += hanoi(n-1, mid, to, from, printans);
	return ans;
}

int main() {
	int n, k;
	scanf("%d %d", &n, &k);
	int cnt = hanoi(n, 'A', 'C', 'B', false);
	if (cnt > k || k == cnt+1) printf("N\n");
	else {
		printf("Y\n");
		if ((k-cnt)%2 != 0) {
			k -= 3;
			printf("A B\nB C\nC A\n");
		}
		while(k > cnt) {
			k -= 2;
			printf("A B\nB A\n");
		}
		hanoi(n, 'A', 'C', 'B', true);
	}
	return 0;
}