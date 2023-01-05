#include <bits/stdc++.h>
using namespace std;
#define MAXN 52
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI (acos(-1.0))
#define FOR(i, n) for(int i = 0; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define pb push_back
#define fi first
#define se second
typedef long long ll;
typedef pair<int, int> ii;

int n, k;
map<ii, int> dp[MAXN][MAXN];
set<ii> aux[MAXN];

int count(const int x[], const int y[]) {
	FOR(i, n) {
		aux[i].clear();
		aux[i].insert({x[i], y[i]});
		if (i == 0) continue;
		for(ii v : aux[i-1]) {
			aux[i].insert(v);
			v.fi += x[i];
			v.se += y[i];
			aux[i].insert(v);
		}
	}
	return aux[n-1].size();
}

void swapdim(int x[], int y[]) {
	FOR(i, n) swap(x[i], y[i]);
}

int x[MAXN], y[MAXN], z[MAXN];
int cx, cy, cz, x1, y1, z1;
int sx[MAXN], sy[MAXN], sz[MAXN];

/*double compute(int tx, int ty, int tz, ll P, double gamma) {
	double alpha = (tx - sqrt(P*1.0*x1*cy/(y1*(tz-gamma*z1))));
	//if (alpha > 1.0) printf("%d %d %d %lld %.5f => alpha %.5f\n", tx, ty, tx, P, gamma, alpha);
	if (alpha < 0.0) alpha = 0.0;
	double beta = (ty-P/((tz-gamma*z1)*(tx-alpha*x1)))/y1;
	//if (beta > 1.0) printf("%d %d %d %lld %.5f %.5f => beta %.5f\n", tx, ty, tx, P, gamma, alpha, beta);
	if (beta < 0.0) beta = 0.0;
	printf("gamma = %.5f, cost = %.5f\n", gamma, alpha*cx + beta*cy + gamma*cz);
	return alpha*cx + beta*cy + gamma*cz;
}*/

int tx, ty, tz;
ll P;

double search(double beta, double gamma) {
	if ((tx-x1)*1.0*(ty-beta*y1)*1.0*(tz-gamma*z1) > P) return INF;
	if (tx*1.0*(ty-beta*y1)*1.0*(tz-gamma*z1) <= P) return beta*cy + gamma*cz;
	double alpha = (tx - P*1.0/((ty-beta*y1)*(tz-gamma*z1)))/x1;
	assert(-EPS <= alpha && alpha <= 1.0+EPS);
	//printf("alpha %.5f beta %.5f gamma %.5f cost %.5f\n", alpha, beta, gamma, alpha*cx + beta*cy + gamma*cz);
	return alpha*cx + beta*cy + gamma*cz;
}

double search(double gamma) {
	if ((tx-x1)*1.0*(ty-y1)*1.0*(tz-gamma*z1) > P) return INF;
	if (tx*1.0*ty*1.0*(tz-gamma*z1) <= P) return gamma*cz;
	double lo = 0;
	double hi = 1;
	FOR(it, 50) {
		double db = (hi-lo)/3;
		double b1 = lo + db;
		double b2 = hi - db;
		double c1 = search(b1, gamma);
		double c2 = search(b2, gamma);
		if (c2 > 1000) lo = b2;
		else if (c1 > 1000) lo = b1;
		else {
			if (c1 > c2) lo = b1;
			else hi = b2;
		}
	}
	double beta = (hi+lo)/2;
	double ans = search(beta, gamma);
	double alpha = (tx - P*1.0/((ty-beta*y1)*(tz-gamma*z1)))/x1;
	double error = P - (tx-alpha*x1)*1.0*(ty-beta*y1)*1.0*(tz-gamma*z1);
	//printf("alpha %.5f beta %.5f gamma %.5f cost %.5f error %.5f\n", alpha, beta, gamma, ans, error);
	return ans;
}

double search() {
	if ((tx-x1)*1.0*(ty-y1)*1.0*(tz-z1) > P) return INF;
	if (tx*1.0*ty*1.0*tz <= P) return 0;
	double lo = 0;
	double hi = 1;
	FOR(it, 50) {
		double dg = (hi-lo)/3;
		double g1 = lo + dg;
		double g2 = hi - dg;
		double c1 = search(g1);
		double c2 = search(g2);
		if (c2 > 1000) lo = g2;
		else if (c1 > 1000) lo = g1;
		else {
			if (c1 > c2) lo = g1;
			else hi = g2;
		}
	}
	double gamma = (hi+lo)/2;
	return search(gamma);
}

int main() {
	int A, B, C;
	scanf("%d %d %d %d %d", &n, &k, &A, &B, &C);
	FOR(i, n) scanf("%d %d %d", &x[i], &y[i], &z[i]);
	int xy = count(x, y);
	int yz = count(y, z);
	int zx = count(z, x);
	if (yz <= xy && yz <= zx) {
		//printf("swap x, z\n");
		swap(A, C);
		swapdim(x, z);
	}
	else if (zx <= xy && zx <= yz) {
		//printf("swap y, z\n");
		swap(B, C);
		swapdim(y, z);
	}

	sx[n] = sy[n] = sz[n] = 0;
	REP(i, n) {
		sx[i] = x[i] + sx[i+1];
		sy[i] = y[i] + sy[i+1];
		sz[i] = z[i] + sz[i+1];
	}

	REP(i, n+1) REP(j, k+1) {
		dp[i][j].clear();
		if (n-i < j) continue;
		if (n-i == j) {
			dp[i][j][{sx[i], sy[i]}] = sz[i];
		}
		else {
			if (i == 0) dp[i][j] = dp[i+1][j];
			else swap(dp[i][j], dp[i+1][j]);
			for(auto p : dp[i+1][j-1]) {

				ii cur = p.fi;
				cur.fi += x[i];
				cur.se += y[i];
				int val = p.se + z[i];

				if (!dp[i][j].count(cur)) {
					dp[i][j][cur] = val;
				}
				else {
					dp[i][j][cur] = min(dp[i][j][cur], val);
				}
			}
		}
	}

	P = INFLL;
	for(auto p : dp[0][k]) {
		ll cur = p.fi.fi*1ll*p.fi.se*1ll*p.se;
		if (cur < P) P = cur;
		//printf("{%d,%d} = %d\n", p.fi.fi, p.fi.se, p.se);
	}

	//printf("P = %lld\n", P);

	double ans = 1e33;
	for(auto p : dp[1][k-1]) {
		x1 = x[0]; cx = A;
		y1 = y[0]; cy = B;
		z1 = z[0]; cz = C;
		tx = x1 + p.fi.fi;
		ty = y1 + p.fi.se;
		tz = z1 + p.se;
		if (cx >= cz && cx >= cy) {
			swap(x1, z1);
			swap(tx, tz);
			swap(cx, cz);
		}
		if (cy >= cz && cy >= cx) {
			swap(y1, z1);
			swap(ty, tz);
			swap(cy, cz);
		}
		if (cy <= cx) {
			swap(y1, x1);
			swap(ty, tx);
			swap(cy, cx);
		}
		//printf("tx %d ty %d tz %d\n", tx, ty, tz);
		//printf("cx %d cy %d cz %d\n", cx, cy, cz);
		//printf("x %d y %d z %d\n", x1, y1, z1);
		ans = min(ans, search());
	}
	/*
	double cost = 1e33;
	for(double gamma = 0.0; gamma <= 1.0; gamma += 0.001)
	for(double beta = 0.0; beta <= 1.0; beta += 0.001)
	for(double alpha = 0.0; alpha <= 1.0; alpha += 0.001) {
		double prod = (1-gamma)*(1-beta)*(1-alpha)*x[0]*y[0]*z[0];
		if (prod > P) continue;
		cost = min(cost, cx*alpha + cy*beta + cz*gamma);
	}
	bool found = false;
	for(double gamma = 0.0; gamma <= 1.0 && !found; gamma += 0.001)
	for(double beta = 0.0; beta <= 1.0 && !found; beta += 0.001)
	for(double alpha = 0.0; alpha <= 1.0 && !found; alpha += 0.001) {
		double prod = (1-gamma)*(1-beta)*(1-alpha)*x[0]*y[0]*z[0];
		if (prod > P) continue;
		if (fabs(cost - cx*alpha - cy*beta - cz*gamma) < EPS) {
			printf("\nalpha %.5f beta %.5f gamma %.5f cost %.5f\n", alpha, beta, gamma, cx*alpha + cy*beta + cz*gamma);
			found = true;
		}
	}
	*/
	printf("%.20f\n", ans);
	return 0;
}