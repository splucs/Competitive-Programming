#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

bool changeable[MAXN];
char str[MAXN];
int N, len, arr[MAXN];

bool divideable() {
	int p = 1, ans = 0;
	for(int i=len-1; i>=0; i--) {
		ans += arr[i]*p;
		p *= 10;
		ans %= N;
		p %= N;
	}
	return ans == 0;
}

bool sum1() {
	int carry = 1;
	for(int i=len-1; i>=0; i--) {
		if (changeable[i] && carry) {
			arr[i]++;
			carry = 0;
			if (arr[i] == 10) {
				arr[i] = 0;
				carry = 1;
			}
		}
	}
	return carry == 0;
}

int main() {
	scanf(" %s %d", str, &N);
	len = strlen(str);
	for(int i=0; i<len; i++) {
		if (str[i] == '?') {
			arr[i] = i > 0 ? 0 : 1;
			changeable[i] = true;
		}
		else arr[i] = str[i] - '0', changeable[i] = false;
	}
	
	bool ok = true;
	int cnt = 0;
	while(cnt < 10*MAXN && ok && !divideable()) {
		ok = sum1();
		cnt++;
	}
	
	if (ok && cnt < 10*MAXN) {
		for(int i=0; i<len; i++) {
			printf("%d", arr[i]);
		}
		printf("\n");
	}
	else printf("*\n");
	
	return 0;
}
