#include <cstdio>
#define MAXN 1009

int mat[MAXN][MAXN], N, M;

enum direction {right, up, left, down};

bool isvalid(int i, int j){
	if (i<0 || j<0 || i>=N || j>=M) return false;
	if (mat[i][j]<0) return false;
	return true;
}

void go(int i, int j, direction dir){
	if (i==N-1 && j==0 && mat[i][j]==1) return;
	mat[i][j]++;
	if (dir==right){
		if (isvalid(i+1, j)) go(i+1, j, down);
		else if (isvalid(i, j+1)) go(i, j+1, right);
		else if (isvalid(i-1, j)) go(i-1, j, up);
		else go(i, j-1, left);
	}
	if (dir==left){
		if (isvalid(i-1, j)) go(i-1, j, up);
		else if (isvalid(i, j-1)) go(i, j-1, left);
		else if (isvalid(i+1, j)) go(i+1, j, down);
		else go(i, j+1, right);
	}
	if (dir==up){
		if (isvalid(i, j+1)) go(i, j+1, right);
		else if (isvalid(i-1, j)) go(i-1, j, up);
		else if (isvalid(i, j-1)) go(i, j-1, left);
		else go(i+1, j, down);
	}
	if (dir==down){
		if (isvalid(i, j-1)) go(i, j-1, left);
		else if (isvalid(i+1, j)) go(i+1, j, down);
		else if (isvalid(i, j+1)) go(i, j+1, right);
		else go(i-1, j, up);
	}
}

int main(){
	int count[5];
	char c;
	while(scanf("%d %d", &N, &M), (N||M)){
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				scanf(" %c", &c);
				if (c=='0') mat[i][j] = 0;
				else mat[i][j] = -1;
			}
		}
		go(N-1, 0, right);
		for(int i=0; i<5; i++) count[i]=0;
		for(int i=0; i<N; i++){
			for(int j=0; j<M; j++){
				if (mat[i][j]>=0 && mat[i][j]<5) count[mat[i][j]]++;
			}
		}
		for(int i=0; i<5; i++) printf("%3d", count[i]);
		printf("\n");
	}
	return 0;
}