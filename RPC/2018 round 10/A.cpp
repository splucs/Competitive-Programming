#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009
#define MAXM 10001009
#define INF 1e9
#define EPS 1e-9
#define FOR(i, N) for(int i = 0; i < N; ++i)
#define FORN(i, j, N) for(int i = j; i < N; ++i)
#define pb push_back
#define L(N) N<<1
#define R(N) (N<<1) + 1
typedef long long int ll;
typedef pair<int, int> ii;
typedef pair<ii, int> iii;
const ll MOD = 1000000007;

struct point{
	double x, y;
	point operator +(point p) const{
		return {p.x + x, p.y + y};
	}
	point operator -(point p) const{
		return {x - p.x, y - p.y};
	}
	point operator *(double d) const{
		return {x * d, y * d};
	}
};
typedef vector<point> polygon;

double cross(point p1, point p2){
	return p1.x * p2.y - p1.y * p2.x;
}

point lIS(point p, point q, point A, point B){
	double c = cross(A - B, p - q);
	double a = cross(A, B);
	double b = cross(p, q);
	return ((p - q) * (a / c)) - ((A- B) * (b / c));
}

polygon cutPolygon(polygon &P, point a, point b){
	vector<point> R;
	double left1, left2;
	int n = P.size();
	FOR(i, n){
		left1 = cross(b - a, P[i] - a);
		left2 = cross(b - a, P[(i + 1) % n] - a);
		if (left1 > -EPS) R.pb(P[i]);
		if (left1 * left2 < -EPS) R.pb(lIS(P[i], P[(i + 1) % n], a, b));
	}
	return R;
}

double area(polygon &P){
	double ans = 0;
	int n = P.size();
	FOR(i, n){
		ans += cross(P[i], P[(i + 1) % n]);
	}
	return abs(ans) / 2;
}

double xmin, xmax, ymin, ymax, tarea;
polygon P;

double solve(double x){
	auto Q = cutPolygon(P, {x, 0}, {x, 1});
	return (x - xmin) * (ymax - ymin) - area(Q);
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	double x[4], y[4];
	
	while (cin>>x[0]>>y[0]){
		P.clear();
		ymin = ymax = y[0];
		xmin = xmax = x[0];
		FORN(i, 1, 4) {
			cin>>x[i]>>y[i];
			xmin = min(xmin, x[i]);
			xmax = max(xmax, x[i]);
			ymin = min(ymin, y[i]);
			ymax = max(ymax, y[i]);
		}
		FOR(i, 4){
			cin>>x[i]>>y[i];
			P.pb({x[i], y[i]});
		}
		cout<<"YES ";
		double l = xmin, r = xmax;

		tarea = (xmax - xmin) * (ymax - ymin) - area(P);
		FOR(i, 60){
			double mid = (l + r) / 2;
			if (solve(mid) > tarea / 2) r = mid;
			else l = mid;
		}
		//cout<<tarea<<' '<<solve(l)<<'\n';
		cout<<fixed<<setprecision(5)<<l<<' '<<ymin<<' '<<l<<' '<<ymax<<'\n';
	}
}
