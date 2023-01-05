#include <bits/stdc++.h>
using namespace std;

int t, n, p;

int main() {
	char cmd[20];
	scanf("%d", &t);
	while (t--) {
		scanf("%d %s %d", &n, cmd, &p);
		if (cmd[0] == 'e') {
			printf("%d\n", 2*p-1);
		} else {
			printf("%d\n", 2*p);
		} 
	}
}