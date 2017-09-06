#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define MAXS 300001
#define EPS 0.000000001
#define INF (1<<30)

vector<int> viz[12];
pair<double, double> loc[12];
int color[12];

int check(int v, int k) {
	bool impossible[8];
	
	for (int i = 1; i <= k; i++) impossible[i] = false;
	
	for (int i = 0; i < viz[v].size(); i++) {
		if (color[viz[v][i]] != -1) {
			impossible[color[viz[v][i]]] = true;
		}
	}
	for (int j = 1; j <= k; j++) {
		if (impossible[j]) continue;
		
		color[v] = j;
		
		int cnt = 0;
		for (int i = 0; i < viz[v].size(); i++) {
			if (color[viz[v][i]] == -1) {
				if(check(viz[v][i], k)) return true;
				cnt++;
			}
		}
		if (cnt == 0) return true;
	}
	
	color[v] = -1;
	return false;
}
int main() {
	int n, cont = 1;
	while (cin >> n && n) {
		for (int i = 0; i < n; i++) {
			viz[i].clear();
			scanf("%lf %lf", &loc[i].first, &loc[i].second);
			for (int j = 0; j < i; j++) {
				if (hypot(loc[i].first - loc[j].first, loc[i].second - loc[j].second) <= 20.0 + EPS) {
					viz[i].push_back(j);
					viz[j].push_back(i);
				}
			}
		}

		int ans = 5;
		
		for (int k = 1; k < 5; k++) {
			bool ok = true;
			for (int i = 0; i < n; i++) {
				color[i] = -1;
			}
			
			for (int i = 0; i < n && ok; i++) {
				if (color[i] == -1) {
					color[i] = 1;
					for (int j = 0; j < viz[i].size() && ok; j++) {
						if (!check(viz[i][j], k)) ok = false;
					}
				}
			}
			if (ok) {
				ans = k; break;
			}
		}
		cout << "The towers in case " << cont++ << " can be covered in " << ans << " frequencies." << endl;
	}
}