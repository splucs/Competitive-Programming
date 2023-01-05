#include <bits/stdc++.h>
using namespace std;

#define MAXN 30

char board[MAXN][MAXN];
int R, C;

bool nocolumn(int j){
	for(int i=0; i<R; i++){
		if (board[i][j] != '?') return false;
	}
	return true;
}

void copycolumn(int j, int jf){
	for(int i=0; i<R; i++){
		board[i][j] = board[i][jf];
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	for(int caseNo=1; caseNo<=T; caseNo++){
		scanf("%d %d", &R, &C);
		for(int i=0; i<R; i++){
			for(int j=0; j<C; j++){
				scanf(" %c", &board[i][j]);
			}
		}
		for(int j=0; j<C; j++){
			if (nocolumn(j)){
				bool switched = false;
				for(int jl=j-1; jl >= 0; jl--){
					if (!nocolumn(jl)){
						copycolumn(j, jl);
						switched = true;
						break;
					}
				}
				if (switched) continue;
				for(int jl=j+1; jl < C; jl++){
					if (!nocolumn(jl)){
						copycolumn(j, jl);
						switched = true;
						break;
					}
				}
			}
		}
		for(int i=0; i<R; i++){
			for(int j=0; j<C; j++){
				if (board[i][j] == '?') continue;
				int ni = i-1;
				while(ni >= 0 && board[ni][j] == '?'){
					board[ni][j] = board[ni+1][j];
					ni--;
				}
				ni = i+1;
				while(ni < R && board[ni][j] == '?'){
					board[ni][j] = board[ni-1][j];
					ni++;
				}
			}
		}
		printf("Case #%d:\n", caseNo);
		for(int i=0; i<R; i++){
			for(int j=0; j<C; j++){
				printf("%c", board[i][j]);
			}
			printf("\n");
		}
	}
	return 0;
}