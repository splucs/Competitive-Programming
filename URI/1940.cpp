#include <cstdio>

int main(){
	int points[509], J, R, winner=1, x, max=0;
	scanf("%d %d", &J, &R);
	for(int i=0; i<J; i++) points[i]=0;
	for(int i=0; i<R; i++){
		for(int j=0; j<J; j++){
			scanf("%d", &x);
			points[j]+=x;
			if(points[j]>max){
				winner = j+1;
				max = points[j];
			}
		}
	}
	printf("%d\n", winner);
	return 0;
}