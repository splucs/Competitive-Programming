#include <bits/stdc++.h>
using namespace std;

int main() {
	int cnt = -1, x;
	for(int i = 0; i < 9; i++) {
		scanf("%d", &x);
		cnt += x;
	}
	cnt %= 9;
	if (cnt == 0) printf("Dasher\n");
	if (cnt == 1) printf("Dancer\n");
	if (cnt == 2) printf("Prancer\n");
	if (cnt == 3) printf("Vixen\n");
	if (cnt == 4) printf("Comet\n");
	if (cnt == 5) printf("Cupid\n");
	if (cnt == 6) printf("Donner\n");
	if (cnt == 7) printf("Blitzen\n");
	if (cnt == 8) printf("Rudolph\n");
	return 0;
}