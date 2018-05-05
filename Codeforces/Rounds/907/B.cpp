#include <bits/stdc++.h>
using namespace std;

char field[9][9];

int main() {
	int xl, yl;
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			scanf(" %c", &field[i][j]);
		}
	}
	scanf("%d %d", &xl, &yl);
	xl--; yl--;
	xl %= 3; yl %= 3;
	int cnt = 0;
	for(int i = 0; i < 3; i++) {
		for(int j = 0; j < 3; j++) {
			if (field[i+3*xl][j+3*yl] == '.') {
				field[i+3*xl][j+3*yl] = '!';
				cnt++;
			}
		}
	}
	if (cnt == 0) {
		for(int i = 0; i < 9; i++) {
			for(int j = 0; j < 9; j++) {
				if (field[i][j] == '.') {
					field[i][j] = '!';
					cnt++;
				}
			}
		}
	}
	for(int i = 0; i < 9; i++) {
		for(int j = 0; j < 9; j++) {
			printf("%c", field[i][j]);
			if (j == 2 || j == 5) printf(" ");
		}
		if (i == 2 || i == 5) printf("\n");
		printf("\n");
	}
	return 0;
}