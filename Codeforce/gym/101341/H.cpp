#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009

struct cell{
	int r, c, val;
	bool operator < (cell o){
		return val > o.val;
	}
};
vector<cell> cells;

int main() {
	int N, M, vr;
	cell nc;
	scanf("%d %d", &N, &M);
	for(int i=1; i<=N; i++) {
		for(int j=1; j<=M; j++){
			scanf("%d", &vr);
			nc.r = i;
			nc.c = j;
			nc.val = vr;
			cells.push_back(nc);
		}
	}
	sort(cells.begin(), cells.end());
	if (N == 1 && M == 1) printf("1 1\n");
	else if (cells[0].r == cells[1].r){
		int j=2;
		while(cells[j].r == cells[0].r && j+1 < (int)cells.size()) j++;
		printf("%d %d\n", cells[0].r, cells[j].c);
	}
	else if (cells[0].c == cells[1].c){
		int j=2;
		while(cells[j].c == cells[0].c && j+1 < (int)cells.size()) j++;
		printf("%d %d\n", cells[j].r, cells[0].c);
	}
	else{
		if (cells[0].r == cells[2].r || cells[1].c == cells[2].c) printf("%d %d\n", cells[0].r, cells[1].c);
		else printf("%d %d\n", cells[1].r, cells[0].c);
	}
	return 0;
}