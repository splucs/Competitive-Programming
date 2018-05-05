#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

int N, a, b;
char arr[MAXN];

int main() {
	scanf("%d %d %d %s", &N, &a, &b, arr);
	int ans = 0;
	for(int i = 0; i < N; i++) {
		if (arr[i] == '*') {
			continue;
		}
		else if (i == 0 || (arr[i-1] != 'a' && arr[i-1] != 'b')) {
			if (a > 0 || b > 0) {
				if (a > b) {
					arr[i] = 'a';
					a--;
				}
				else {
					arr[i] = 'b';
					b--;
				}
				ans++;
			}
		}
		else if (arr[i-1] == 'a') {
			if (b > 0) {
				arr[i] = 'b';
				b--;
				ans++;
			}
		}
		else if (arr[i-1] == 'b') {
			if (a > 0) {
				arr[i] = 'a';
				a--;
				ans++;
			}
		}
	}
	printf("%d\n", ans);
	return 0;
}