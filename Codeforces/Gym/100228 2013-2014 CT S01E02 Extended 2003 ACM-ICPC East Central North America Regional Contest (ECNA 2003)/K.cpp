#include <bits/stdc++.h>
using namespace std;

char board[10][10];
bool unoc[10][10];
string line;

void torre(int r, int c) {
	for (int i = r-1; i >= 1 && board[i][c] == '.'; i--) {
		unoc[i][c] = false;
	}
	for (int j = c-1; j >= 1 && board[r][j] == '.'; j--) {
		unoc[r][j]= false;
	}
	for (int i = r+1; i <= 8 && board[i][c] == '.'; i++) {
		unoc[i][c] = false;
	}
	for (int j = c+1; j <= 8 && board[r][j] == '.'; j++) {
		unoc[r][j] = false;
	}
}

void bispo(int r, int c) {
	for (int k = 1; r+k <= 8 && c+k <= 8 && board[r+k][c+k] == '.'; k++) {
		unoc[r+k][c+k] = false;
	}
	for (int k = 1; r+k <= 8 && c-k >= 1 && board[r+k][c-k] == '.'; k++) {
		unoc[r+k][c-k] = false;
	}
	for (int k = 1; r-k >= 1 && c+k <= 8 && board[r-k][c+k] == '.'; k++) {
		unoc[r-k][c+k] = false;
	}
	for (int k = 1; r-k >= 1 && c-k >= 1 && board[r-k][c-k] == '.'; k++) {
		unoc[r-k][c-k] = false;
	}
}

void cavalo(int r, int c) {
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (abs(i-r) + abs(j-c) == 3 && abs(i-r) > 0 && abs(j-c) > 0) unoc[i][j] = false;
		}
	}
}

void rei(int r, int c) {
	for (int i = 1; i <= 8; i++) {
		for (int j = 1; j <= 8; j++) {
			if (abs(i-r) <= 1 && abs(j-c) <= 1 && (abs(i-r) + abs(j-c)) > 0) unoc[i][j] = false;
		}
	}
}

void check(int r, int c) {
	unoc[r][c] = false;
	
	if (board[r][c] == 'Q' || board[r][c] == 'q') {
		bispo(r, c);
		torre(r, c);
	}
	if (board[r][c] == 'K' || board[r][c] == 'k') {
		rei(r, c);
	}
	if (board[r][c] == 'R' || board[r][c] == 'r') {
		torre(r, c);
	}
	if (board[r][c] == 'N' || board[r][c] == 'n') {
		cavalo(r, c);
	}
	if (board[r][c] == 'B' || board[r][c] == 'b') {
		bispo(r, c);
	}
	if (board[r][c] == 'p') {
		unoc[r+1][c-1] = false;
		unoc[r+1][c+1] = false;
	}
	if (board[r][c] == 'P') {
		unoc[r-1][c-1] = false;
		unoc[r-1][c+1] = false;
	}
}
int main() {
	while(getline(cin, line)) {
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				board[i][j] = '.';
				unoc[i][j] = true;
			}
		}
		
		int r= 1, c = 1;
		for (int k = 0; k < line.size(); k++) {
			if (line[k] == '/') {
				r++; c = 1;
				continue;
			}
			if (line[k] >= '0' && line[k] <= '9') {
				c += line[k] - '0';
				continue;
			}
			board[r][c] = line[k];
			c++;
		}
		
		int ans = 0;
		
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				if (board[i][j] != '.') check(i, j);
			}
		}
		
		
		for (int i = 1; i <= 8; i++) {
			for (int j = 1; j <= 8; j++) {
				if (unoc[i][j]) ans++;
			}
		}
		
		cout << ans << endl;
	}
}