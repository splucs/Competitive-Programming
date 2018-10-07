#include <bits/stdc++.h>
#define FOR(x, n) for(int x=0; x<n; x++)
#define pb push_back
using namespace std;

char mat[200][200];
set<vector<string> > used;

int main() {
	int r, c;
	scanf("%d %d", &r, &c);
	FOR(x, r) {
		scanf("%s", mat[x]);
	}
	
	int d = 1, l = 1;
	for (; d <= r; d++) {
		if (mat[d][1] == '#') break;
	}
	for (; l <= c; l++) {
		if (mat[1][l] == '#') break;
	}
	l--; d--;

	int cnt = 0;
	for (int k = 1; k < c; k += l+1) {
		for (int k2 = 1; k2 < r; k2 += d+1) {
			bool ok = true;

			vector<string> vec;
			for (int i = k2; i < k2+d; i++) {
				string st;
				for (int j = k; j < k+l; j++) {
					st.pb(mat[i][j]);
				}
				vec.pb(st);
			}
			if (used.count(vec)) { continue; }

			cnt++;
			used.insert(vec);
			
			vec.clear();
			for (int i = k2+d-1; i >= k2; i--) {
				string st;
				for (int j = k+l-1; j >= k; j--) {
					st.pb(mat[i][j]);
				}
				vec.pb(st);
			}
			used.insert(vec);


			vec.clear();
			for (int j = k; j < k+l; j++) {
				string st;
				for (int i = k2+d-1; i >= k2; i--) {
					st.pb(mat[i][j]);
				}
				vec.pb(st);
			}
			used.insert(vec);


			vec.clear();
			for (int j = k+l-1; j >= k; j--) {
				string st;
				for (int i = k2; i < k2+d; i++) {
					st.pb(mat[i][j]);
				}
				vec.pb(st);
			}
			used.insert(vec);
		}
	}
	printf("%d\n", cnt);
}