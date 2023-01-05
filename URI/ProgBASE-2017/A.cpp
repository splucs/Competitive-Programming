#include <bits/stdc++.h>
using namespace std;

void printnum(int n) {
	if (n == 'A') printf("2");
	if (n == 'B') printf("2");
	if (n == 'C') printf("2");
	if (n == 'D') printf("3");
	if (n == 'E') printf("3");
	if (n == 'F') printf("3");
	if (n == 'G') printf("4");
	if (n == 'H') printf("4");
	if (n == 'I') printf("4");
	if (n == 'J') printf("5");
	if (n == 'K') printf("5");
	if (n == 'L') printf("5");
	if (n == 'M') printf("6");
	if (n == 'N') printf("6");
	if (n == 'O') printf("6");
	if (n == 'P') printf("7");
	if (n == 'Q') printf("7");
	if (n == 'R') printf("7");
	if (n == 'S') printf("7");
	if (n == 'T') printf("8");
	if (n == 'U') printf("8");
	if (n == 'V') printf("8");
	if (n == 'W') printf("9");
	if (n == 'X') printf("9");
	if (n == 'Y') printf("9");
	if (n == 'Z') printf("9");
}

int main() {
	char c;
	while(scanf("%c", &c)!= EOF) {
		if (c >= '0' && c <= '9') printf("%c", c);
		else if (c == '\n' || c == '*' || c == '#') printf("%c", c);
		else if (c >= 'A' && c <= 'Z') printnum(c);
		else if (c >= 'a' && c <= 'z') printnum(c - 'a' + 'A');
	}
	printf("\n");
	return 0;
}