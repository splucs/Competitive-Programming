#include <bits/stdc++.h>
#define pb push_back
#define FOR(x,n) for(int x=0;x<n;x++)
#define FOR1e(x,n) for(int x=1; x<=n; x++)
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

int h[109];

int main() {
	int t, n, w, s;
	scanf("%d", &t);
	while (t--) {
		scanf("%d %d %d", &n, &w, &s);
		int pos = -1;
		FOR(i, n) {
			scanf("%d", &h[i]);
			if (h[i] == 0) {
				pos = i;
			}
		}

		double max_angle = 0;
		FOR(i, pos) {
			max_angle = max(max_angle, atan2(h[i], (pos-i)*(w+s)));
		}
		double ans = 0;
		double PI = acos(-1.0);
		ans += (max_angle)*480.0 / (PI/2.0);
		max_angle = 0;
		for (int i = pos+1; i < n; i++) {
			max_angle = max(max_angle, atan2(h[i], (i-pos)*(w+s)));
		}
		ans += (max_angle)*480.0 / (PI/2.0);
		printf("%.10lf\n", 960-ans);
	}
}