#include <bits/stdc++.h>
using namespace std;

int main() {
        int value[256];
        value['A'] = 1;
        value['B'] = 2;
        value['C'] = 3;
	char a, b, r;
	int score = 0;
        while(scanf(" %c %c", &a, &r) != EOF) {
		if (r == 'Y') {
			b = a;
			score += 3;
		}
		else if (r == 'X') {
			b = a-1;
			if (b < 'A') b = 'C';
		} 
		else if (r == 'Z') {
			b = a+1;
			if (b > 'C') b = 'A';
			score += 6;
		} 
		else {
			printf("error\n");
			return 1;
		}
		score += value[b];
	}
	printf("%d\n", score);
	return 0;
}
