#include <iostream>
#include <stdio.h>
using namespace std;
typedef long long ll;

string lines[8];
string ans[8];

char numbers[10][8][6];
int get_number(int start) {
	for (int n = 0; n < 10; n++) {
		bool ok = true;
		for (int i = 0; i < 7; i++) {
			for (int j = 0; j < 5; j++) {
				if (numbers[n][i][j] != lines[i][start+j]) ok = false;
			}
		}
		
		if (ok) return n;
	}
	return -1;
}

void print_number(int n) {
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 5; j++) {
			ans[i].push_back(numbers[n][i][j]);
		}
	}
}

void preprocess() {
	for (int i = 0; i < 10; i++) {
		for (int j = 0; j < 7; j++) {
			for (int k = 0; k < 5; k++) numbers[i][j][k] = '.';
		}
	}
	
	// 1
	for (int j = 0; j < 7; j++) {
		numbers[1][j][4] = 'x';
	}
	
	
	// 2
	for (int j = 0; j < 4; j++) {
		numbers[2][j][4] = 'x';
		numbers[2][6-j][0] = 'x';
	}
	for (int k = 0; k < 5; k++) {
		numbers[2][0][k] = 'x';
		numbers[2][3][k] = 'x';
		numbers[2][6][k] = 'x';
	}
	
	// 3
	for (int j = 0; j < 7; j++) {
		numbers[3][j][4] = 'x';
	}
	for (int k = 0; k < 5; k++) {
		numbers[3][0][k] = 'x';
		numbers[3][3][k] = 'x';
		numbers[3][6][k] = 'x';
	}
	
	// 4
	for (int j = 0; j < 7; j++) {
		numbers[4][j][4] = 'x';
		if (j < 4) numbers[4][j][0] = 'x';
	}
	for (int k = 0; k < 5; k++) {
		numbers[4][3][k] = 'x';
	}
	
	// 5
	for (int j = 0; j < 7; j++) {
		if (j < 4) numbers[5][j][0] = 'x';
		if (j >= 4) numbers[5][j][4] = 'x';
	}
	for (int k = 0; k < 5; k++) {
		numbers[5][0][k] = 'x';
		numbers[5][3][k] = 'x';
		numbers[5][6][k] = 'x';
	}
	
	// 6
	for (int j = 0; j < 7; j++) {
		numbers[6][j][0] = 'x';
		if (j >= 4) numbers[6][j][4] = 'x';
	}
	for (int k = 0; k < 5; k++) {
		numbers[6][0][k] = 'x';
		numbers[6][3][k] = 'x';
		numbers[6][6][k] = 'x';
	}
	
	// 7
	for (int j = 0; j < 7; j++) {
		numbers[7][j][4] = 'x';
	}
	for (int k = 0; k < 5; k++) {
		numbers[7][0][k] = 'x';
	}
	
	// 8
	for (int j = 0; j < 7; j++) {
		numbers[8][j][0] = 'x';
		numbers[8][j][4] = 'x';
	}
	for (int k = 0; k < 5; k++) {
		numbers[8][0][k] = 'x';
		numbers[8][3][k] = 'x';
		numbers[8][6][k] = 'x';
	}
	
	// 9
	for (int j = 0; j < 7; j++) {
		if (j < 4) numbers[9][j][0] = 'x';
		numbers[9][j][4] = 'x';
	}
	for (int k = 0; k < 5; k++) {
		numbers[9][0][k] = 'x';
		numbers[9][3][k] = 'x';
		numbers[9][6][k] = 'x';
	}
	
	// 0
	for (int j = 0; j < 7; j++) {
		numbers[0][j][4] = 'x';
		numbers[0][j][0] = 'x';
	}
	for (int k = 0; k < 5; k++) {
		numbers[0][0][k] = 'x';
		numbers[0][6][k] = 'x';
	}
}

int main() {
	preprocess();
	
	while(getline(cin, lines[0])) {
		if (lines[0].size() == 0) continue;
		for (int i = 1; i < 7; i++) {
			getline(cin, lines[i]);
		}
		
		int st = 0;
		
		ll a = 0, b = 0;
		bool plus = false;
		while (st < lines[0].size()) {
			int n = get_number(st);
			
			if (n < 0) { plus = true; }
			else if (!plus) {
				a *= 10;
				a += n;
			} else {
				b *= 10;
				b += n;
			}
			st += 6;
		}
		
		ll result = a + b;
		bool spaces = false;
		for (int i = 0; i < 7; i++) ans[i] = "";
		
		if (result == 0) print_number(0);
		
		int tam = 0;
		ll n = 1;
		
		while(result/n != 0) {
			n *= 10;
			tam++;
		}
		n /= 10;
		
		while (tam > 0) {
			if (spaces) {
				for (int i = 0; i < 7; i++) {
					ans[i].push_back('.');
				}
			}
			
			spaces = true;

			print_number(result/n);
			result = result%n;
			n /= 10;
			tam--;
		}
		
		for (int i = 0; i < 7; i++) {
			cout << ans[i] << endl;
		}
	}
}