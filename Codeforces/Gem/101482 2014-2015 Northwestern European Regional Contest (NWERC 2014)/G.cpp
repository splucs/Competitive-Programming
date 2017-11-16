#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define INF (1LL<<60)
typedef long long ll;

int N;

void computev(ll* x, ll* vx) {
	ll sum = 0;
	for(int i=0; i<N; i++) {
		vx[i] = i*(x[i]-x[0]) - sum;
		sum += x[i]-x[0];
	}
	sum = 0;
	for(int i=N-1; i>=0; i--) {
		vx[i] += (N-i-1)*(x[N-1]-x[i]) - sum;
		sum += x[N-1]-x[i];
	}
}

ll getvaluearr(ll qx, ll* x, ll* vx) {
	if (qx < x[0]) return N*(x[0]-qx) + vx[0];
	if (qx > x[N-1]) return N*(qx-x[N-1]) + vx[N-1];
	int lo = 0;
	int hi = N;
	while(hi > lo+1) {
		int mid = (hi+lo)/2;
		if (x[mid] <= qx) lo = mid;
		else hi = mid;
	}
	if (x[lo] == qx) return vx[lo];
	ll dv = vx[hi] - vx[lo];
	ll dx = x[hi] - x[lo];
	return vx[lo] + (dv/dx)*(qx-x[lo]);
}

ll x[MAXN], y[MAXN], vx[MAXN], vy[MAXN], D;
ll maxsum, minsum, maxdif, mindif;

ll getvalue(ll qx, ll qy) {
	return getvaluearr(qx, x, vx) + getvaluearr(qy, y, vy);
}

ll getyhi(ll qx) { return min(maxsum-qx, qx+maxdif); }
ll getylo(ll qx) { return max(minsum-qx, qx+mindif); }
ll getxhi(ll qy) { return min(maxsum-qy, qy-mindif); }
ll getxlo(ll qy) { return max(minsum-qy, qy-maxdif); }

bool inside(ll qx, ll qy) {
	return qx+qy <= maxsum && qx+qy >= minsum && qy-qx <= maxdif && qy-qx >= mindif;
}

int main() {
	scanf("%d", &N);
	maxsum = maxdif = INF;
	minsum = mindif = -INF;
	for(int i=0; i<N; i++) {
		scanf("%I64d %I64d", &x[i], &y[i]);
	}
	scanf("%I64d", &D);
	for(int i=0; i<N; i++) {
		maxsum = min(maxsum, x[i]+y[i]+D);
		minsum = max(minsum, x[i]+y[i]-D);
		maxdif = min(maxdif, y[i]-x[i]+D);
		mindif = max(mindif, y[i]-x[i]-D);
	}
	
	sort(x, x+N);
	sort(y, y+N);
	ll xopt = x[N/2];
	ll yopt = y[N/2];
	ll ans = INF, qx, qy;
	computev(x, vx);
	computev(y, vy);
	
	vector<pair<ll, ll> > corners;
	
	//top corner
	qx = (maxsum - maxdif)/2;
	qy = (maxsum + maxdif)/2;
	if (inside(qx, qy)) ans = min(ans, getvalue(qx, qy));
	if (inside(qx, qy+1)) ans = min(ans, getvalue(qx, qy+1));
	if (inside(qx+1, qy)) ans = min(ans, getvalue(qx+1, qy));
	if (inside(qx+1, qy+1)) ans = min(ans, getvalue(qx+1, qy+1));
	
	//right corner
	qx = (maxsum - mindif)/2;
	qy = (maxsum + mindif)/2;
	if (inside(qx, qy)) ans = min(ans, getvalue(qx, qy));
	if (inside(qx, qy+1)) ans = min(ans, getvalue(qx, qy+1));
	if (inside(qx+1, qy)) ans = min(ans, getvalue(qx+1, qy));
	if (inside(qx+1, qy+1)) ans = min(ans, getvalue(qx+1, qy+1));
	
	//bottom corner
	qx = (minsum - maxdif)/2;
	qy = (minsum + maxdif)/2;
	if (inside(qx, qy)) ans = min(ans, getvalue(qx, qy));
	if (inside(qx, qy+1)) ans = min(ans, getvalue(qx, qy+1));
	if (inside(qx+1, qy)) ans = min(ans, getvalue(qx+1, qy));
	if (inside(qx+1, qy+1)) ans = min(ans, getvalue(qx+1, qy+1));
	
	//left corner
	qx = (minsum - mindif)/2;
	qy = (minsum + mindif)/2;
	if (inside(qx, qy)) ans = min(ans, getvalue(qx, qy));
	if (inside(qx, qy+1)) ans = min(ans, getvalue(qx, qy+1));
	if (inside(qx+1, qy)) ans = min(ans, getvalue(qx+1, qy));
	if (inside(qx+1, qy+1)) ans = min(ans, getvalue(qx+1, qy+1));
	
	//x cordinates
	for(int i=0; i<N; i++) {
		ll yhi = getyhi(x[i]);
		ll ylo = getylo(x[i]);
		if (yhi < ylo) continue;
		if (yopt > yhi) ans = min(ans, getvalue(x[i], yhi));
		else if (yopt < ylo) ans = min(ans, getvalue(x[i], ylo));
		else ans = min(ans, getvalue(x[i], yopt));
	}
	
	//y cordinates
	for(int i=0; i<N; i++) {
		ll xhi = getxhi(y[i]);
		ll xlo = getxlo(y[i]);
		if (xhi < xlo) continue;
		if (xopt > xhi) ans = min(ans, getvalue(xhi, y[i]));
		else if (xopt < xlo) ans = min(ans, getvalue(xlo, y[i]));
		else ans = min(ans, getvalue(xopt, y[i]));
	}
	
	if (ans == INF) printf("impossible\n");
	else printf("%I64d\n", ans);
	
	return 0;	
}