#include <cstdio>
#include <algorithm>
using namespace std;
#define MAXN 509
#define INF (1LL << 60)

typedef long long ll;
ll adjMat[MAXN][MAXN];
int N;

//O(V^3)
void floydwarshall(){
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++){
				adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);
			}
}

int main(){
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			scanf("%I64d", &adjMat[i][j]);
			if (adjMat[i][j] <= 0) adjMat[i][j] = INF;
		}
	}
	/*for(int i=0; i<N; i++){
		for(int j=0; j<N; j++){
			printf("%I64d ", adjMat[i][j]);
		}
		printf("\n");
	}*/
	floydwarshall();
	int min_i = 0;
	for(int i=0; i<N; i++){
		if (adjMat[i][i] < adjMat[min_i][min_i]) min_i = i;
	}
	if (adjMat[min_i][min_i] == INF) printf("-1\n");
	else printf("%d %I64d\n", min_i+1, adjMat[min_i][min_i]);
	return 0;
}