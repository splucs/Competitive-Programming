#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

char str[MAXN];

int main() {
	scanf(" %s", str);
	int n = strlen(str);
	int cnt = 0, i;
	for(i = n-1; i>=0 && cnt < 6; i--) {
		if (str[i] == '0') cnt++;
	}
	bool ok = false;
	for(; i>=0; i--) {
		if (str[i] == '1') ok = true;
	}
	if (ok) printf("yes\n");
	else printf("no\n");
	return 0;
}