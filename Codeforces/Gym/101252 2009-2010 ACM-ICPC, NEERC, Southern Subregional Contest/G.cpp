#include <bits/stdc++.h>
using namespace std;
#define MAXN 39

char str[MAXN];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int T;
	scanf("%d", &T);
	while(T-->0) {
		scanf(" %s", str);
		int len = strlen(str);
		if (str[len-1] == 'x' || str[len-1] == 's' || str[len-1] == 'o' || (str[len-2] == 'c' && str[len-1] == 'h')) {
			str[len++] = 'e';
			str[len++] = 's';
		}
		else if (str[len-1] == 'f') {
			str[len-1] = 'v';
			str[len++] = 'e';
			str[len++] = 's';
		}
		else if (str[len-2] == 'f' && str[len-1] == 'e') {
			str[len-2] = 'v';
			str[len-1] = 'e';
			str[len++] = 's';
		}
		else if (str[len-1] == 'y') {
			str[len-1] = 'i';
			str[len++] = 'e';
			str[len++] = 's';
		}
		else {
			str[len++] = 's';
		}
		str[len] = 0;
		printf("%s\n", str);
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}