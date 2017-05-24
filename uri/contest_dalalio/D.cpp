#include <bits/stdc++.h>
using namespace std;

int board[9][9];

int main()
{
	int T;
	scanf("%d", &T);
	while(T-->0) {
		for(int i=0; i<4; i++){
			for(int j=0; j<4; j++){
				scanf("%d", &board[i][j]);
			}
		}
		bool left = false, right = false, up = false, down = false, done = false;
		for(int i=0; i<4; i++) {
			for(int j=0; j<4; j++) {
				if (board[i][j] == 0) continue;
				for(int k=i+1; k<4 ; k++){
					if (board[k][j] == 0 || board[k][j] == board[i][j]) down = true;
					else break;
				}
				for(int k=i-1; k>=0; k--){
					if (board[k][j] == 0 || board[k][j] == board[i][j]) up = true;
					else break;
				}
				for(int k=j+1; k<4 ; k++){
					if (board[i][k] == 0 || board[i][k] == board[i][j]) right = true;
					else break;
				}
				for(int k=j-1; k>=0; k--){
					if (board[i][k] == 0 || board[i][k] == board[i][j]) left = true;
					else break;
				}
				if (board[i][j] == 2048) done = true;
			}
		}
		if (done) printf("NONE");
		else if (!up && !left && !right && !down) printf("NONE");
		else{
			bool printed = false;
			if (down){
				if (printed) printf(" ");
				printf("DOWN");
				printed = true;
			}
			if (left){
				if (printed) printf(" ");
				printf("LEFT");
				printed = true;
			}
			if (right){
				if (printed) printf(" ");
				printf("RIGHT");
				printed = true;
			}
			if (up){
				if (printed) printf(" ");
				printf("UP");
				printed = true;
			}
		}
		printf("\n");
	}
	return 0;
}