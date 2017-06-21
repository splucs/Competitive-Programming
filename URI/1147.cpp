#include <cstdio>

int main()
{
	int p, caso=0;
	char c;
	int mat[8][8];
	int x, y;
	while(true){
		caso++;
		scanf("%d", &p);
		if (p==0) break;
		scanf("%c", &c);
		x = p-1;
		y = c-'a';
		for (int i = 0; i < 8; ++i)
		{
			for (int j = 0; j < 8; ++j)
			{
				mat[i][j]=1;
			}
		}
		for (int i = 0; i < 8; ++i)
		{
			scanf("%d", &p);
			if (p==0) break;
			scanf("%c", &c);
			if (p-2>=0 && c-'a'+1<8)
				mat[p-2][c-'a'+1]=0;
			if (p-2>=0 && c-'a'-1>=0)
				mat[p-2][c-'a'-1]=0;
		}
		p=0;
		if (x+2<8 && y+1<8) p+=mat[x+2][y+1];
		if (x+1<8 && y+2<8) p+=mat[x+1][y+2];
		if (x+2<8 && y-1>=0) p+=mat[x+2][y-1];
		if (x+1<8 && y-2>=0) p+=mat[x+1][y-2];
		if (x-2>=0 && y+1<8) p+=mat[x-2][y+1];
		if (x-1>=0 && y+2<8) p+=mat[x-1][y+2];
		if (x-2>=0 && y-1>=0) p+=mat[x-2][y-1];
		if (x-1>=0 && y-2>=0) p+=mat[x-1][y-2];
		printf("Caso de Teste #%d: %d movimento(s).\n", caso, p);
	}
	return 0;
}