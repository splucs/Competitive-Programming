#include <cstdio>
#include <cstring>

char board[20][20];
bool go[20][20];

void tower(int x, int y){
	char c = board[x][y];
	board[x][y] = '.';
	for(int i=x, j=y; i<=8; i++){
		go[i][j] = true;
		if (board[i][j] >= 'A' && board[i][j] <= 'Z') break;
		if (board[i][j] >= 'a' && board[i][j] <= 'z') break;
	}
	for(int i=x, j=y; i>=1; i--){
		go[i][j] = true;
		if (board[i][j] >= 'A' && board[i][j] <= 'Z') break;
		if (board[i][j] >= 'a' && board[i][j] <= 'z') break;
	}
	for(int i=x, j=y; j<=8; j++){
		go[i][j] = true;
		if (board[i][j] >= 'A' && board[i][j] <= 'Z') break;
		if (board[i][j] >= 'a' && board[i][j] <= 'z') break;
	}
	for(int i=x, j=y; j>=1; j--){
		go[i][j] = true;
		if (board[i][j] >= 'A' && board[i][j] <= 'Z') break;
		if (board[i][j] >= 'a' && board[i][j] <= 'z') break;
	}
	board[x][y] = c;
}

void bishop(int x, int y){
	char c = board[x][y];
	board[x][y] = '.';
	for(int i=x, j=y; i<=8 && j<=8; i++, j++){
		go[i][j] = true;
		if (board[i][j] >= 'A' && board[i][j] <= 'Z') break;
		if (board[i][j] >= 'a' && board[i][j] <= 'z') break;
	}
	for(int i=x, j=y; i<=8 && j>0; i++, j--){
		go[i][j] = true;
		if (board[i][j] >= 'A' && board[i][j] <= 'Z') break;
		if (board[i][j] >= 'a' && board[i][j] <= 'z') break;
	}
	for(int i=x, j=y; i>0 && j<=8; i--, j++){
		go[i][j] = true;
		if (board[i][j] >= 'A' && board[i][j] <= 'Z') break;
		if (board[i][j] >= 'a' && board[i][j] <= 'z') break;
	}
	for(int i=x, j=y; i>0 && j>0; i--, j--){
		go[i][j] = true;
		if (board[i][j] >= 'A' && board[i][j] <= 'Z') break;
		if (board[i][j] >= 'a' && board[i][j] <= 'z') break;
	}
	board[x][y] = c;
}

void pawn(int x, int y){
	go[x][y] = true;
	go[x+1][y+1] = true;
	go[x+1][y-1] = true;
}

void queen(int x, int y){
	bishop(x, y);
	tower(x, y);
}

void king(int x, int y){
	go[x][y] = true;
	go[x+1][y+1] = true;
	go[x+1][y-1] = true;
	go[x-1][y+1] = true;
	go[x-1][y-1] = true;
	go[x][y+1] = true;
	go[x][y-1] = true;
	go[x+1][y] = true;
	go[x-1][y] = true;
}

void knight(int x, int y){
	go[x+2][y+1] = true;
	go[x+2][y-1] = true;
	if(x>=2) go[x-2][y+1] = true;
	if(x>=2) go[x-2][y-1] = true;
	go[x+1][y+2] = true;
	if(y>=2) go[x+1][y-2] = true;
	go[x-1][y+2] = true;
	if(y>=2) go[x-1][y-2] = true;
}

int main(){
	for(int i=8; i>0; i--){
		for(int j=1; j<=8; j++){
			scanf(" %c", &board[i][j]);
		}
	}
	char c;
	int x, y;
	scanf(" %c %d", &c, &x);
	y = (c-'a') + 1;
	for(int i=8; i>0; i--){
		for(int j=1; j<=8; j++){
			if (board[i][j] == 'p') pawn(i, j);
			if (board[i][j] == 't') tower(i, j);
			if (board[i][j] == 'b') bishop(i, j);
			if (board[i][j] == 'k') king(i, j);
			if (board[i][j] == 'r') queen(i, j);
			if (board[i][j] == 'c') knight(i, j);
		}
	}
	if (go[x][y]) printf("Sim\n");
	else printf("Nao\n");
	/*for(int i=8; i>0; i--){
		for(int j=1; j<=8; j++){
			printf("%d", go[i][j]);
		}
		printf("\n");
	}*/
	return 0;
}