#include <bits/stdc++.h>
using namespace std;
#define MAXN 19
#define MAXM (1<<MAXN)+9
#define state dp[mask][i]
#define INF 1e+15

double dp[MAXM][MAXN];
double W, L;
int N;

struct point {
	double x, y;
	point() : x(0), y(0) {}
	point(double _x, double _y) : x(_x), y(_y) {}
} bottle[MAXN];

double bd[MAXN][MAXN];

inline double borderd(point p, point q) {
    double ans = INF;
    ans = min(ans, hypot(q.x-p.x,       -q.y-p.y));
    ans = min(ans, hypot(q.x-p.x,       2*L-q.y-p.y));
    ans = min(ans, hypot(2*W-q.x-p.x,   q.y-p.y));
    ans = min(ans, hypot(-q.x-p.x,      q.y-p.y));
    return ans;
}

int main() {
    freopen("kitchen.in", "r", stdin);
    freopen("kitchen.out", "w", stdout);

	scanf("%lf %lf", &W, &L);
	point s;
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf("%lf %lf", &bottle[i].x, &bottle[i].y);
	}
	scanf("%lf %lf", &s.x, &s.y);
	for(int i=0; i<N; i++) {
        for(int j=0; j<N; j++) {
            bd[i][j] = borderd(bottle[i], bottle[j]);
        }
	}
	for(int mask=(1<<N)-1; mask>=0; mask--) {
		for(int i=0; i<N; i++) {
			state = INF;
			if (mask == (1<<N)-1){
				state = min(state, bottle[i].x);
				state = min(state, bottle[i].y);
				state = min(state, W-bottle[i].x);
				state = min(state, L-bottle[i].y);
			}
			else for(int j=0; j<N; j++) {
				if (mask & (1 << j)) continue;
				state = min(state, bd[i][j] + dp[mask | (1 << j)][j]);
			}
		}
	}
	double ans = INF;
	for(int i=0; i<N; i++) {
		ans = min(ans, hypot(s.x - bottle[i].x, s.y - bottle[i].y) + dp[1<<i][i]);
	}
	printf("%.14f\n", ans);

	fclose(stdin);
	fclose(stdout);
	return 0;
}