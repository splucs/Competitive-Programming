#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009


typedef long long ll;
typedef pair<int, ll> ii;
set<pair<ii, int> > pq;
int col[3][MAXN], order[MAXN], N;
int rig[3][MAXN], lef[3][MAXN], val[MAXN];
ll id[MAXN];

int compcol;
bool comp(int i, int j) { return col[compcol][i] < col[compcol][j]; }

void update(int i) {
	if(pq.count(make_pair(ii(val[i], -id[i]), i))) pq.erase(make_pair(ii(val[i], -id[i]), i));
	val[i] = 0;
	for(int c=0; c<3; c++) {
		int l = lef[c][i];
		int r = rig[c][i];
		if (col[c][i] == col[c][l] || col[c][i] == col[c][r]) continue;
		int da = col[c][i] - col[c][l];
		val[i] += da >= 0 ? da : da + 360;
		da = col[c][r] - col[c][i];
		val[i] += da >= 0 ? da : da + 360;
	}
	pq.insert(make_pair(ii(val[i], -id[i]), i));
}

void erase(int i) {
	if(pq.count(make_pair(ii(val[i], -id[i]), i))) pq.erase(make_pair(ii(val[i], -id[i]), i));
	for(int c=0; c<3; c++) {
		rig[c][lef[c][i]] = rig[c][i];
		lef[c][rig[c][i]] = lef[c][i];
		update(rig[c][i]);
		update(lef[c][i]);
	}
}

int main() {
	
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		order[i] = i;
		scanf("%d %d %d %I64d", &col[0][i], &col[1][i], &col[2][i], &id[i]);
	}
	
	for(int c=0; c<3; c++) {
		compcol = c;
		sort(order, order+N, comp);
		for(int i=0; i<N; i++) {
			rig[c][order[i]] = order[(i+1)%N];
			lef[c][order[i]] = order[(i+N-1)%N];
		}
	}
	for(int i=0; i<N; i++) {
		update(i);
	}
	
	for(int j=0; j<N; j++) {
		int i = pq.begin()->second;
		printf("%I64d\n", id[i]);
		erase(i);
	}
	
	return 0;
}