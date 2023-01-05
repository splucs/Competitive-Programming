#include <cstdio>

bool g[3][3], ng[3][3];

bool end(){
	for(int i=0; i<3; i++){
		for(int j=0; j<3; j++){
			if (g[i][j]) return false;
		}
	}
	return true;
}

bool val(int x, int y){
	if (x<0 || x>2 || y<0 || y>2) return false;
	else return g[x][y];
}

int main(){
	int n, k;
	char c;
	scanf("%d", &n);
	while(n-->0){
		for(int i=0; i<3; i++){
			for(int j=0; j<3; j++){
				scanf(" %c", &c);
				g[i][j] = (c=='1');
			}
		}
		k = -1;
		while(!end()){
			k++;
			for(int i=0; i<3; i++){
				for(int j=0; j<3; j++){
					ng[i][j] = (val(i-1, j)!=val(i+1,j))!=(val(i, j-1)!=val(i,j+1));
				}
			}
			for(int i=0; i<3; i++){
				for(int j=0; j<3; j++){
					g[i][j] = ng[i][j];
				}
			}
		}
		printf("%d\n", k);
	}
	return 0;
}