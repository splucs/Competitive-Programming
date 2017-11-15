#include <bits/stdc++.h>
using namespace std;
#define MAXN 3009

char str[MAXN];

bool vocal(char c) {
	return c == 'a' || c == 'e' || c == 'i' || c == 'o' || c == 'u';
}

int main() {
	scanf("%s", str);
	int len = strlen(str);
	int lc = 0, le = 0;
	for(int i=0; i<len; i++) {
		if (vocal(str[i])) lc = i+1;
		if (str[i] != str[le]) le = i;
		if (i - lc >= 2 && le > lc) {
			printf(" ");
			lc = i;
			le = i;
		}
		printf("%c", str[i]);
	}
	printf("\n");
	return 0;
}