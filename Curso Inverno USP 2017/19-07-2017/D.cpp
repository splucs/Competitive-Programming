#include <bits/stdc++.h>
using namespace std;
#define INF (1<<30)

int board[3][3], magic[3][3], ans;
bool used[10];

int diff() {
	int dif = 0;
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			dif += abs(magic[i][j] - board[i][j]);
		}
	}
	return dif;
}

bool check() {
	int i, j, s;
	for(i=0, j; i<3; i++) {
		s = 0;
		for(j=0; j<3; j++) {
			s += magic[i][j];
			if (magic[i][j] == 0) break;
		}
		if (j == 3 && s != 15) return false; 
	}
	for(i, j=0; j<3; j++) {
		s = 0;
		for(i=0; i<3; i++) {
			s += magic[i][j];
			if (magic[i][j] == 0) break;
		}
		if (i == 3 && s != 15) return false; 
	}
	s = 0;
	for(i=0; i<3; i++) {
		s += magic[i][i];
		if (magic[i][i] == 0) break;
	}
	if (i == 3 && s != 15) return false;
	s = 0;
	for(i=0; i<3; i++) {
		s += magic[i][2-i];
		if (magic[i][2-i] == 0) break;
	}
	if (i == 3 && s != 15) return false;
	return true;	
}

void printmat(int m[3][3]) {
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			printf("%d ", m[i][j]);
		}
		printf("\n");
	}
	printf("\n");
}

void backtrack(int i, int j) {
	if (i == 3){
		//printf("dif = %d\n", diff());
		//printmat(magic);
		
		ans = min(ans, diff());
		return;
	}
	if (magic[i][j] != 0) {
		if (check()) backtrack(i + (j+1)/3, (j+1)%3);
		return;
	}
	for(int k=1; k<=9; k++) {
		if (used[k]) continue;
		magic[i][j] = k;
		used[k] = true;
		if (check()) backtrack(i + (j+1)/3, (j+1)%3);
		magic[i][j] = 0;
		used[k] = false;
	}
}

int main() {
	memset(&used, false, sizeof used);
	for(int i=0; i<3; i++) {
		for(int j=0; j<3; j++) {
			magic[i][j] = 0;
			scanf("%d", &board[i][j]);
		}
	}
	ans = INF;
	backtrack(0, 0);
	printf("%d\n", ans);
	return 0;
}