#include <bits/stdc++.h>
#define MAXN 100009
#define INF 1000000007
#define EPS 1e-9
#define FOR(i, n) for(int i = 0; i < n; i++)
#define FORN(i, j, n) for(int i = j; i < n; i++)
#define REP(i, n) for(int i = n-1; i >= 0; i--)
#define FOR1(i, n) for(int i = 1; i <= n; i++)
#define REP1(i, n) for(int i = n; i > 0; i--)
#define fi first
#define se second
#define pb push_back
#define sz(x) int(x.size())
using namespace std;
typedef long long int ll;
typedef pair<int, int> ii;

int N, R;

struct point{
	ll x, y;

	bool operator<(const point &other) const{
		if (abs(x - other.x) > EPS) return x < other.x;
		return y < other.y;
	}

	point operator -(const point &other){
		return {x - other.x, y - other.y};
	}

	point operator +(const point &other){
		return {x + other.x, y + other.y};
	}
};

ll inner(point p1, point p2){
	return p1.x * p2.x + p1.y * p2.y;
}

ll cross(point p1, point p2){
	return p1.x * p2.y - p1.y * p2.x;
}

bool ccw(point p, point q, point r){
	return cross(q - p, r - p) > 0;
}

bool collinear(point p, point q, point r){
	return cross(p - q, r - p) == 0;
}

point pivot;

bool angleCmp(point a, point b){
	if (collinear(pivot, a, b)){
		return inner(pivot - a, pivot - a) < inner(pivot - b, pivot - b); 
	}
	return cross(a - pivot, b - pivot) >= 0;
}

int leftmostIndex(vector<point> &P){
	int ans = 0;
	FOR(i, sz(P)){
		if (P[i] < P[ans]) ans = i;
	}
	return ans;
}

typedef vector<point> polygon;

polygon convexHull(vector<point> P){
	int i, j, n = (int) P.size();
	if (n <= 2) return P;
	int P0 = leftmostIndex(P);
	swap(P[0], P[P0]);
	pivot = P[0];
	sort(++P.begin(), P.end(), angleCmp);
	vector<point> S;
	S.pb(P[n - 1]);
	S.pb(P[0]);
	S.pb(P[1]);
	for (i = 2; i < n;){
		j = (int) S.size() - 1;
		if (ccw(S[j - 1], S[j], P[i])) S.pb(P[i++]);
		else S.pop_back();
	}
	reverse(S.begin(), S.end());
	S.pop_back();
	reverse(S.begin(), S.end());
	return S;
}

polygon p;

bool allcol(){
	point p0 = p[0];
	point p1 = p[1];

	FORN(i, 2, N){
		if (!collinear(p0, p1, p[i])) return false;
	}
	return true;
}

double dist(point p, point a, point b){
	double u = inner(p - a, b - a) *1.0/ inner(b - a, b - a);
	return hypot(a.x + (b-a).x*u - p.x, a.y + (b-a).y*u - p.y);
}

int main() {
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);

	int x, y;
	
	cin>>N>>R;
	FOR(i, N){
		cin>>x>>y;
		p.pb(point{x, y});
	}
	cout<<fixed<<setprecision(10);
	if (allcol()) {cout<<0.0<<'\n'; return 0;}
	p = convexHull(p);
	//for(point q : p) cout <<q.x<<" "<<q.y<<endl;

	int j = 2;
	double ans = 1e30;

	N = p.size();
	FOR(i, N){
		point p0 = p[i];
		point p1 = p[(i + 1) % N];

		while (dist(p[(j + 1) % N], p0, p1) >= dist(p[j], p0, p1)-EPS) {
			j = (j + 1) % N;
		}
		//printf("opt[%d,%d] = %d\n", i, (i+1)%N, j);
		ans = min(ans, dist(p[j], p0, p1)); 
	}
	cout<<ans<<'\n';
}
