#include <bits/stdc++.h>
using namespace std;

char str[109];

int main() {
	scanf(" %s", str);
	int len = strlen(str);
	int ans = 0;
	for(int i=0; i<len; i++) {
		ans += str[i] - '1' + 1;
	}
	printf("%d\n", ans%3);
	return 0;
}
