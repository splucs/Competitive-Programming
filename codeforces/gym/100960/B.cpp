#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int N, X, p[MAXN], ans;
int r[MAXN], l[MAXN];
bool fr[MAXN], fl[MAXN];

int findright(int g) {
	//printf("find right %d\n", g);
	if (fl[g]) return g;
	else return r[g] = findright(r[g]);
}

int findleft(int g) {
	//printf("find left %d\n", g);
	if (fr[g]) return g;
	else return l[g] = findleft(l[g]);
}

void simulate(int g, bool right) {
	int next;
	if (right) {
		next = findright(g);
		if (next == N+1) return;
		fl[next] = false;
	}
	else {
		next = findleft(g);
		if (next == 0) ans++;
		else fr[next] = false;
	}
	//printf("shot from %d to %d\n", g, next);
	simulate(next, !right);
}

int main()
{
	scanf("%d %d", &N, &X);
	memset(&fr, false, sizeof fr);
	memset(&fl, false, sizeof fl);
	p[0] = 0;
	int sg = 0, face;
	fr[0] = true;
	r[0] = 1;
	fl[N+1] = true;
	l[N+1] = N;
	for(int i=1; i<=N; i++) {
		scanf("%d %d", &p[i], &face);
		if (p[i] < X) sg = i;
		r[i] = i+1;
		l[i] = i-1;
		if (face) fl[i] = true;
		else fr[i] = true;
	}
	ans = 0;
	simulate(sg, false);
	for(int i=1; i<=N; i++) {
		if (fr[i] || fl[i]) ans = -1;
	}
	printf("%d\n", ans);
	return 0;
}