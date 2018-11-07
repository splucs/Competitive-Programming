#include <cstdio>
#define MAXI 1000009

/*
 * Pre-read all input fast
 */

char input[MAXI];
void readInput() {
	input[fread(input, 1, sizeof(input)-4, stdin)] = 0;
}

/*
 * a bit faster than scanf("%d", &x)
 */

int readInt() {
	bool minus = false;
	int ans = 0;
	char c;
	while (c = getchar()) {
		if (c == '-') break;
		if (c >= '0' && c <= '9') break;
	}
	if (c == '-') minus = true;
	else ans = c-'0';
	while (c = getchar()) {
		if (c < '0' || c > '9') break;
		ans = ans*10 + (c - '0');
	}
	return minus ? -ans : ans;
}

/*
 * TEST MATRIX
 */

int main() {
	while(true) {
		int x = readInt();
		if (x < -10000) return 0;
		printf("x = %d\n", x);
	}
}