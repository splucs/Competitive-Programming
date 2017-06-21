#include <cstdio>

int main()
{
	int n, h[30][30], linha1[30][30][3], linha2[30][6], linha3[4], x, y, op, winner, instancia=0;;
	while(true){
		instancia++;
		scanf("%d", &n);
		if (n==0) break;
		for(int i=0; i<n; i++){
			for(int j=0; j<n; j++){
				for(int k=0; k<3; k++){
					linha1[i][j][k]=0;
				}
				h[i][j]=0;
			}
			for(int k=0; k<6; k++){
				linha2[i][k]=0;
			}
		}
		for(int k=0; k<4; k++){
			linha3[k]=0;
		}
		winner=0;
		for (int jogada=0; jogada < n*n*n; jogada++){
			scanf("%d %d", &x, &y);
			x--;
			y--;
			if(jogada%2==0) op=1;
			else op=-1;
			linha1[x][h[x][y]][0]+=op;
			if ((linha1[x][h[x][y]][0]==n || linha1[x][h[x][y]][0]==-n) && winner==0) winner=op;
			linha1[y][h[x][y]][1]+=op;
			if ((linha1[y][h[x][y]][1]==n || linha1[y][h[x][y]][1]==-n) && winner==0) winner=op;
			linha1[x][y][2]+=op;
			if ((linha1[x][y][2]==n || linha1[x][y][2]==-n) && winner==0) winner=op;
			if(x==h[x][y]){
				linha2[y][0]+=op;
				if ((linha2[y][0]==n || linha2[y][0]==-n) && winner==0) winner=op;
			}
			if(x==n-1-h[x][y]){
				linha2[y][1]+=op;
				if ((linha2[y][1]==n || linha2[y][1]==-n) && winner==0) winner=op;
			}
			if(y==h[x][y]){
				linha2[x][2]+=op;
				if ((linha2[x][2]==n || linha2[x][2]==-n) && winner==0) winner=op;
			}
			if(y==n-1-h[x][y]){
				linha2[x][3]+=op;
				if ((linha2[x][3]==n || linha2[x][3]==-n) && winner==0) winner=op;
			}
			if(x==y){
				linha2[h[x][y]][4]+=op;
				if ((linha2[h[x][y]][4]==n || linha2[h[x][y]][4]==-n) && winner==0) winner=op;
			}
			if(x==n-1-y){
				linha2[h[x][y]][5]+=op;
				if ((linha2[h[x][y]][5]==n || linha2[h[x][y]][5]==-n) && winner==0) winner=op;
			}
			if(x==y && x==h[x][y]){
				linha3[0]+=op;
				if ((linha3[0]==n || linha3[0]==-n) && winner==0) winner=op;
			}
			if(x==n-1-y && x==h[x][y]){
				linha3[1]+=op;
				if ((linha3[1]==n || linha3[1]==-n) && winner==0) winner=op;
			}
			if(x==y && x==n-1-h[x][y]){
				linha3[2]+=op;
				if ((linha3[2]==n || linha3[2]==-n) && winner==0) winner=op;
			}
			if(x==n-1-y && x==n-1-h[x][y]){
				linha3[3]+=op;
				if ((linha3[3]==n || linha3[3]==-n) && winner==0) winner=op;
			}
			h[x][y]++;
		}
		if(winner>0) printf("Instancia %d\nBranco ganhou\n\n", instancia);
		else if (winner<0) printf("Instancia %d\nAzul ganhou\n\n", instancia);
		else printf("Instancia %d\nEmpate\n\n", instancia);
	}
	return 0;
}