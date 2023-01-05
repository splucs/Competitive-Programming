#include <bits/stdc++.h>
#define DEBUG false
#define debugf if (DEBUG) printf
#define MAXN 109
#define MAXM 300009
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define INFLL 0x3f3f3f3f3f3f3f3f
#define EPS 1e-9
#define PI 3.141592653589793238462643383279502884L
#define FOR(x,n) for(int x=0; (x)<int(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=int(n); (x)++)
#define REP(x,n) for(int x=int(n)-1; (x)>=0; (x)--)
#define REP1(x,n) for(int x=(n); (x)>0; (x)--)
#define pb push_back
#define pf push_front
#define fi first
#define se second
#define mp make_pair
#define all(x) x.begin(), x.end()
#define mset(x,y) memset(&x, (y), sizeof(x));
using namespace std;
typedef vector<int> vi;
typedef pair<int, int> ii;
typedef long long ll;
typedef unsigned long long ull;
typedef long double ld;
typedef unsigned int uint;

struct point {
	double x, y, z;
	point() { x = y = z = 0.0; }
	point(double _x, double _y, double _z) : x(_x), y(_y), z(_z) {}
	double norm() {
		return sqrt(x*x + y*y + z*z);
	}
	point normalized() {
		return point(x,y,z)*(1.0/norm());
	}
	bool operator < (point other) const {
		if (fabs(x - other.x) > EPS) return x < other.x;
		else if (fabs(y - other.y) > EPS) return y < other.y;
		else return z < other.z;
	}
	bool operator == (point other) const {
		return (fabs(x - other.x) < EPS && fabs(y - other.y) < EPS && fabs(z - other.z) < EPS);
	}
	point operator +(point other) const{
		return point(x + other.x, y + other.y, z + other.z);
	}
	point operator -(point other) const{
		return point(x - other.x, y - other.y, z - other.z);
	}
	point operator *(double k) const{
		return point(x*k, y*k, z*k);
	}
};

double dist(point p1, point p2) {
	return (p1-p2).norm();
}

int main() {
	point A = point(0, 1, 3);
	point B = point(4, 5, 0);
	point P1 = point(0, 1, 0);
	point P2 = point(0, 19.0/7, 0);
	printf("%.5f %.5f", dist(A, P1) + dist(B, P1), dist(A, P2) + dist(B, P2));
}