#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

char board[MAXN][MAXN];
int N, M, k, r, c;

bool empty(int i, int j)
{
	if (i<1 || j<1 || i>N || j>M) return false;
	return board[i][j] != 'Q' && board[i][j] != 'K' && board[i][j] != 'P';
}

void queen(int si, int sj)
{
	for(int i=si-1, j=sj; true; i--){
		if (!empty(i, j)) break;
		board[i][j] = 'x';
	}
	for(int i=si+1, j=sj; true; i++){
		if (!empty(i, j)) break;
		board[i][j] = 'x';
	}
	for(int i=si, j=sj-1; true; j--){
		if (!empty(i, j)) break;
		board[i][j] = 'x';
	}
	for(int i=si, j=sj+1; true; j++){
		if (!empty(i, j)) break;
		board[i][j] = 'x';
	}
	for(int i=si-1, j=sj-1; true; i--, j--){
		if (!empty(i, j)) break;
		board[i][j] = 'x';
	}
	for(int i=si-1, j=sj+1; true; i--, j++){
		if (!empty(i, j)) break;
		board[i][j] = 'x';
	}
	for(int i=si+1, j=sj-1; true; i++, j--){
		if (!empty(i, j)) break;
		board[i][j] = 'x';
	}
	for(int i=si+1, j=sj+1; true; i++, j++){
		if (!empty(i, j)) break;
		board[i][j] = 'x';
	}
}

void knight(int si, int sj)
{
	if (empty(si-1, sj-2)) board[si-1][sj-2] = 'x';
	if (empty(si-1, sj+2)) board[si-1][sj+2] = 'x';
	if (empty(si+1, sj-2)) board[si+1][sj-2] = 'x';
	if (empty(si+1, sj+2)) board[si+1][sj+2] = 'x';
	if (empty(si-2, sj-1)) board[si-2][sj-1] = 'x';
	if (empty(si-2, sj+1)) board[si-2][sj+1] = 'x';
	if (empty(si+2, sj-1)) board[si+2][sj-1] = 'x';
	if (empty(si+2, sj+1)) board[si+2][sj+1] = 'x';
}

void pawn(int si, int sj)
{
	if (empty(si-1, sj-1)) board[si-1][sj-1] = 'x';
	if (empty(si-1, sj+1)) board[si-1][sj+1] = 'x';
}

int main()
{
	int count = 1;
	while(true)
	{
		scanf("%d %d", &N, &M);
		if (N == 0 && M == 0) break;
		memset(&board, '.', sizeof board);
		scanf("%d", &k);
		for(int i=0; i<k; i++){
			scanf("%d %d", &r, &c);
			board[r][c] = 'Q';
		}
		scanf("%d", &k);
		for(int i=0; i<k; i++){
			scanf("%d %d", &r, &c);
			board[r][c] = 'K';
		}
		scanf("%d", &k);
		for(int i=0; i<k; i++){
			scanf("%d %d", &r, &c);
			board[r][c] = 'P';
		}
		for(int i=1; i<=N; i++)
		{
			for(int j=1; j<=M; j++)
			{
				if (board[i][j] == 'Q') queen(i, j);
				if (board[i][j] == 'K') knight(i, j);
				//if (board[i][j] == 'P') pawn(i, j);
			}
		}
		int ans = 0;
		for(int i=1; i<=N; i++)
		{
			for(int j=1; j<=M; j++)
			{
				if (board[i][j] == '.') ans++;
			}
		}
		printf("Board %d has %d safe squares.\n", count++, ans);
	}
	return 0;
	
}