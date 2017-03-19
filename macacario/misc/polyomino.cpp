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

vector<ii> neightbors(ii pos) {
	vector<ii> v;
	v.push_back(ii(pos.first + 1, pos.second));
	v.push_back(ii(pos.first - 1, pos.second));
	v.push_back(ii(pos.first, pos.second + 1));
	v.push_back(ii(pos.first, pos.second - 1));
	return v;
}

//0->unused, 1->to be used, 2->used
void dfs(int sum, int h, int n) {
	used[coord[n].first][coord[n].second] = 2;
	path[h] = coord[n];
	if (h == M) {
		maxsum = max(maxsum, sum);
		used[coord[n].first][coord[n].second] = 1;
		return;
	}
	vector<ii> nei = neightbors(coord[n]);
	ii next;
	int nadded = 0;
	for (int i = 0; i<4; i++) {
		next = nei[i];
		if (!used[next.first][next.second]) {
			used[next.first][next.second] = 1;
			coord[nused] = next;
			nadded++; nused++;
		}
	}
	for (int i = n + 1, nextsum; i<nused; i++) {
		nextsum = mat[coord[i].first][coord[i].second];
		dfs(sum + nextsum, h + 1, i);
	}
	while (nadded-->0) {
		nused--;
		next = coord[nused];
		used[next.first][next.second] = 0;
	}
	used[coord[n].first][coord[n].second] = 1;
}