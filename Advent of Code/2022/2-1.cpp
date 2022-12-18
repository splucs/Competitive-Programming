#include <bits/stdc++.h>
using namespace std;

int main() {
        int value[256];
        value['A'] = value['X'] = 1;
        value['B'] = value['Y'] = 2;
        value['C'] = value['Z'] = 3;
	char a, b;
	int score = 0;
        while(scanf(" %c %c", &a, &b) != EOF) {
		if (value[a] == value[b]) {
			score += 3;
		}
		else if (value[b]%3 == (value[a]+1)%3) {
			score += 6;
		} 
		score += value[b];
	}
	printf("%d\n", score);
	return 0;
}
