#include <cstdio>

int main()
{
	char board[8][8], type, p1;
	bool danger[8][8], checkMate;
	int N, p2;
	while(scanf("%d", &N)!=EOF){
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				board[i][j]=0;
				danger[i][j]=false;
			}
		}
		for (int i = 0; i < N; ++i)
		{
			scanf(" %c%c%d", &type, &p1, &p2);
			board[(int)(p1-'a')][p2-1]=type;
		}
		scanf(" %c%c%d", &type, &p1, &p2);
		p1-='a';
		p2-=1;
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				switch(board[i][j]){
					case 'W':
						for (int m = -1; m < 2; ++m)
						{
							for (int n=-1; n<2; n++)
							{
								if ((m==0 && n==0) || i+m<0 || i+m>=8 || j+n<0 || j+n>=8) continue;
								danger[i+m][j+n]=true;
							}
						}
						break;
					case 'R':
						for(int m=1; j+m<8 && i+m<8; m++){
							danger[i+m][j+m]=true;
							if (board[i+m][j+m]!=0) break;
						}
						for(int m=1; j-m>=0 && i+m<8; m++){
							danger[i+m][j-m]=true;
							if (board[i+m][j-m]!=0) break;
						}
						for(int m=1; j+m<8 && i-m>=0; m++){
							danger[i-m][j+m]=true;
							if (board[i-m][j+m]!=0) break;
						}
						for(int m=1; j-m>=0 && i-m>=0; m++){
							danger[i-m][j-m]=true;
							if (board[i-m][j-m]!=0) break;
						}
						for(int m=1; i+m<8; m++){
							danger[i+m][j]=true;
							if (board[i+m][j]!=0) break;
						}
						for(int m=1; j-m>=0; m++){
							danger[i][j-m]=true;
							if (board[i][j-m]!=0) break;
						}
						for(int m=1; j+m<8; m++){
							danger[i][j+m]=true;
							if (board[i][j+m]!=0) break;
						}
						for(int m=1; i-m>=0; m++){
							danger[i-m][j]=true;
							if (board[i-m][j]!=0) break;
						}
						break;
					case 'B':
						for(int m=1; j+m<8 && i+m<8; m++){
							danger[i+m][j+m]=true;
							if (board[i+m][j+m]!=0) break;
						}
						for(int m=1; j-m>=0 && i+m<8; m++){
							danger[i+m][j-m]=true;
							if (board[i+m][j-m]!=0) break;
						}
						for(int m=1; j+m<8 && i-m>=0; m++){
							danger[i-m][j+m]=true;
							if (board[i-m][j+m]!=0) break;
						}
						for(int m=1; j-m>=0 && i-m>=0; m++){
							danger[i-m][j-m]=true;
							if (board[i-m][j-m]!=0) break;
						}
						break;
					case 'T':
						for(int m=1; i+m<8; m++){
							danger[i+m][j]=true;
							if (board[i+m][j]!=0) break;
						}
						for(int m=1; j-m>=0; m++){
							danger[i][j-m]=true;
							if (board[i][j-m]!=0) break;
						}
						for(int m=1; j+m<8; m++){
							danger[i][j+m]=true;
							if (board[i][j+m]!=0) break;
						}
						for(int m=1; i-m>=0; m++){
							danger[i-m][j]=true;
							if (board[i-m][j]!=0) break;
						}
						break;
					case 'P':
						if (j-1>=0 && i-1>=0) danger[i-1][j-1]=true;
						if (j-1>=0 && i+1<8) danger[i+1][j-1]=true;
						break;
					default: break;
				}
			}
		}
		checkMate=true;
		for (int m = -1; m < 2 && checkMate; ++m)
		{
			for (int n=-1; n<2 && checkMate; n++)
			{
				if (p1+m<0 || p1+m>=8 || p2+n<0 || p2+n>=8) continue;
				if (!danger[(int)p1+m][p2+n]) checkMate=false;
			}
		}
		if (checkMate) printf("SIM\n");
		else printf("NAO\n");
	}
	return 0;
}