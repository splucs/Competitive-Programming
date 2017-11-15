#include <bits/stdc++.h>
using namespace std;

bool palindrome(int n, int s) {
	int dig[12];
	for(int i=0; i<s; i++) {
		dig[i] = n%10;
		n /= 10;
	}
	for(int i=0; 2*i < s; i++) {
		if (dig[i] != dig[s-1-i]) return false;
	}
	return true;
}

int main() {
	char buffer[12];
	int sz, num;
	while(true) {
		scanf(" %s", buffer);
		sscanf(buffer, "%d", &num);
		sz = strlen(buffer);
		if (sz == 1 && num == 0) break;
		int ans = 0;
		while(!palindrome(num, sz)) {
			ans++;
			num++;
		}
		printf("%d\n", ans);
	}
	return 0;
}