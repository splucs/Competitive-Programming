#include <bits/stdc++.h>
using namespace std;
#define MAXN 109
#define EPS 1e-9
#define MAXS 29
#define INF 1e+18
#define dist(i, j) hypot(x[i] - x[j], y[i] - y[j])

int N, M, id[MAXN];
double x[MAXN], y[MAXN], t[MAXN], d[MAXN][MAXN];
bool shot[MAXN], before[MAXN][MAXN], after[MAXN][MAXN];
char name[MAXN][MAXS];
map<string, int> name2id;

bool comp(int i, int j) {
	if (before[i][j]) return true;
	if (after[i][j]) return false;
	return t[i] < t[j];
}

int main() {
	int T;
	scanf("%d", &T);
	while(T --> 0) {
		
		bool possible = true;
		bool multiple = false;
		
		scanf(" %d %d", &N, &M);
		name2id.clear();
		for(int i=1; i<=N; i++) {
			scanf(" %s %lf %lf", name[i], &x[i], &y[i]);
			name2id[string(name[i])] = i;
			shot[i] = false;
			for(int j=1; j<=N; j++) d[i][j] = INF;
			d[i][i] = 0;
		}
		char s1[MAXS], s2[MAXS], s3[MAXS];
		memset(&before, false, sizeof before);
		memset(&after, false, sizeof after);
		for(int m=0; m<M; m++) {
			scanf(" %s heard %s firing before %s", s1, s2, s3);
			int k = name2id[string(s1)];
			int i = name2id[string(s2)];
			int j = name2id[string(s3)];
			shot[i] = shot[j] = true;
			double dt = dist(k, j) - dist(k, i);
			d[i][j] = min(d[i][j], dt);
			if (fabs(dt) < EPS || dt > 0.0) {
				before[i][j] = true;
				after[j][i] = true;
				if (before[j][i] || after[i][j]) possible = false;
			}
		}
		
		for(int k=1; k<=N; k++) {
			for(int i=1; i<=N; i++) {
				for(int j=1; j<=N; j++) {
					d[i][j] = min(d[i][j], d[i][k] + d[k][j]);
				}
			}
		}
		
		int s = -1;
		for(int i=1; i<=N; i++) {
			if (d[i][i] < 0.0) possible = false;
			bool ok = true;
			for(int j=1; j<=N; j++) {
				//printf("d[%s][%s] = %.3f\n", name[i], name[j], d[i][j]);
				if (i == j || !shot[i] || !shot[j]) continue;
				if (d[i][j] >= 0.0) ok = false;
			}
			if (ok && shot[i]) {
				if (s == -1) s = i;
				else multiple = true;
			}
		}
		if (s == -1) multiple = true;
		
		if (!possible) printf("IMPOSSIBLE\n");
		else if (multiple) printf("UNKNOWN\n");
		else {
			t[s] = 0.0;
			for(int i=1; i<=N; i++) {
				id[i] = i;
				t[i] = d[i][s] + t[s];
			}
			sort(id+1, id+1+N, comp);
			/*bool ok = true;
			for(int it=2, i; it<=N; it++) {
				if (shot[id[it]] && shot[id[it-1]] && fabs(t[id[it]] - t[id[it-1]]) < EPS && !before[id[it]][id[it-1]]) ok = false;
			}
			if (!ok) printf("UNKNOWN");*/
			for(int it=1, i; it<=N; it++) {
				i = id[it];
				if (shot[i]) printf("%s ", name[i]);
			}
			printf("\n");
		}
	}
	
	return 0;
}