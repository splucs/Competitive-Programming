#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

typedef long long ll;

struct point {
	ll x, y, c;
	point() : x(0), y(0) {}
	point(ll _x, ll _y, ll _c) : x(_x), y(_y), c(_c) {}
	point operator - (point o) {
		return point(x-o.x, y-o.y, 0);
	}
	bool operator == (point o) {
		return x == o.x && y == o.y;
	}
};

ll inner(point p1, point p2) {
	return p1.x*p2.x + p1.y*p2.y;
}

ll cross(point p1, point p2) {
	return p1.x*p2.y - p1.y*p2.x;
}

inline bool sameHalf(point a, point b) {
	ll cr = cross(a, b);
	if (cr > 0) return true;
	if (cr == 0 && inner(a, b) >= 0) return true;
	return false;
}

int N, M;
point arr1[MAXN], arr2[MAXN], pivot;
ll c1[MAXN], c2[]

bool comp(point a, point b) {
	return atan2(a.y, a.x) - atan2(b.y, b.x) < 0;
}

ll linesweep() {
	vector<point> ord;
	for(int i=0; i<N; i++) {
		if (arr1[i] == pivot) continue;
		ord.push_back(arr1[i] - pivot);
		ord.back().c = arr1[i]
	}
	for(int j=0; j<M; j++) {
		if (arr2[j] == pivot) continue;
		ord.push_back(pivot - arr2[j]);
	}
	ll ans = 0, cur = ord[0].c;
	int K = ord.size();
	sort(ord.begin(), ord.end(), comp);
	for(int i=0, j=1; i<K; i++) {
		while(j%K != i && sameHalf(ord[i], ord[j])) {
			cur += ord[j].c;
			j = (j+1)%K;
		}
		ans = max(ans, cur);
		cur -= ord[i].c;
	}
	return ans;
}

int main() {
	while(scanf("%d %d", &N, &M), N || M) {
		for(int i=0; i<N; i++) {
			scanf("%lld %lld %lld", &arr1[i].x, &arr1[i].y, &arr1[i].c);
		}
		for(int i=0; i<M; i++) {
			scanf("%lld %lld %lld", &arr2[i].x, &arr2[i].y, &arr2[i].c);
		}
		ll ans = 0;
		for(int i=0; i<N; i++) {
			pivot = arr1[i];
			ans = max(ans, linesweep());
		}
		printf("%lld\n", N-ans);
	}
	return 0;
}