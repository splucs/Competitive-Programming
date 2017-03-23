#include <cstdio>
#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#define MAXN 500
using namespace std;

typedef pair<int, int> ii;
ii coord[MAXN], path[MAXN];
int used[MAXN][MAXN];
int mat[MAXN][MAXN], maxsum, N, M, nused;

vector<ii> neightbors(ii pos){
	vector<ii> v;
	v.push_back(ii(pos.first+1, pos.second));
	v.push_back(ii(pos.first-1, pos.second));
	v.push_back(ii(pos.first, pos.second+1));
	v.push_back(ii(pos.first, pos.second-1));
	return v;
}

//0->unused, 1->to be used, 2->used
void dfs(int sum, int h, int n){
	used[coord[n].first][coord[n].second] = 2;
	path[h] = coord[n];

	if (h == M){
		maxsum = max(maxsum, sum);
		used[coord[n].first][coord[n].second] = 1;
		return;
	}

	vector<ii> nei = neightbors(coord[n]);
	ii next;

	int nadded = 0;
	for(int i=0; i<4; i++){
		next = nei[i];
		if (!used[next.first][next.second]){
			used[next.first][next.second] = 1;
			coord[nused] = next;
			nadded++; nused++;
		}
	}

	for(int i = n+1, nextsum; i<nused; i++){
		nextsum = mat[coord[i].first][coord[i].second];
		dfs(sum + nextsum, h+1, i);
	}
	
	while(nadded-->0){
		nused--;
		next = coord[nused];
		used[next.first][next.second] = 0;
	}
	used[coord[n].first][coord[n].second] = 1;
}

int main(){
	while(scanf("%d %d", &N, &M)!=EOF){
		for(int i=0; i<=N+1; i++){
			used[i][0] = used[0][i] = 1;
			used[i][N+1] = used[N+1][i] = 1;
		}
		for(int i=1; i<=N; i++){
			for(int j=1; j<=N; j++){
				scanf("%d", &mat[i][j]);
				used[i][j] = 0;
			}
		}
		maxsum = 0;
		for(int i=1; i<=N; i++){
			for(int j=1; j<=N; j++){
				used[i][j] = 1;
				nused = 0;
				coord[nused++] = ii(i, j);
				dfs(mat[i][j], 1, 0);
			}
		}

		printf("%d\n", maxsum);
	}
	return 0;
}