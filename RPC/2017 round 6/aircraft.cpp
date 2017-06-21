#include <bits/stdc++.h>
using namespace std;
#define x first
#define y second.first
#define z second.second

typedef pair<int, pair<int, int> > iii;
iii mt(int a, int b, int c) {
	return iii(a, make_pair(b, c));
}
iii p[39];
set<iii> s;
int A, B, C, N;
char name[1009];

void bt1(int i, int a, int b, int c) {
	if (i == N/2){
		s.insert(mt(a, b, c));
		return;
	}
	else{
		bt1(i+1, a, b, c);
		bt1(i+1, a+p[i].x, b+p[i].y, c+p[i].z);
	}
}

bool bt2(int i, int a, int b, int c) {
	if (i == N){
		return s.count(mt(A-a, B-b, C-c));
	}
	else{
		if (bt2(i+1, a, b, c)) return true;
		if (bt2(i+1, a+p[i].x, b+p[i].y, c+p[i].z)) return true;
	}
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d %d %d %d", &A, &B, &C, &N);
		s.clear();
		for(int i=0; i<N; i++) {
			scanf(" %s %d %d %d", name, &p[i].x, &p[i].y, &p[i].z);
		}
		bt1(0, 0, 0, 0);
		if (bt2(N/2, 0, 0, 0)) printf("POSSIBLE\n");
		else printf("IMPOSSIBLE\n");
	}
	return 0;
}