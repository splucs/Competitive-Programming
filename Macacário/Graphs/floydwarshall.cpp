#include <cstidio>
#define MAXN 409

int adjMat[MAXN][MAXN], N;

//O(V^3)
void floydwarshall() {
	for (int k = 0; k < N; k++)
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				adjMat[i][j] = min(adjMat[i][j], adjMat[i][k] + adjMat[k][j]);
}