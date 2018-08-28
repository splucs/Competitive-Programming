#include <bits/stdc++.h>
using namespace std;
#define MAXN 509
#define MAXM 1009
#define INF 1e9
#define EPS 1e-9
#define FOR(i, N) for (int i = 0; i < N; ++i)
#define FORN(i, j, N) for (int i = j; i < N; ++i)
#define pb push_back
typedef long long int ll;
typedef pair<int, int> ii;

char a[MAXN][MAXN];

int movx[4][4] = {{0, -1, 0, 1}, {1, 0, -1, 0}, {0, 1, 0, -1}, {-1, 0, 1, 0}};
int movy[4][4] = {{1, 0, -1, 0}, {0, 1, 0, -1}, {-1, 0, 1, 0}, {0, -1, 0, 1}};
int nxtdir[4][4] = {{1, 0, 3, 2}, {2, 1, 0, 3}, {3, 2, 1, 0}, {0, 3, 2, 1}};

int conv(char c){
	if (c == 'F') return 1;
	if (c == 'R') return 0;
	if (c == 'L') return 2;
	return 3;
}

int main(){
	ios_base::sync_with_stdio(false);
	cin.tie(NULL);
	
	string s;
	int t, xmin, xmax, ymax, ymin, l, r;
	cin>>t;
	cout<<t<<'\n';

	while (t--){
		cin>>s;

		int dir = 1, x, y;
		memset(a, 0, sizeof a);
		l = 100, r = 100;
		xmin = ymin = xmax = ymax = 100;
		a[100][100] = '.';

		for (char c : s){
			int u = conv(c);

			FOR(i, 4){	
				x = l + movx[dir][i], y = r + movy[dir][i];
				a[x][y] = '#';
				xmin = min(xmin, x), ymin = min(ymin, y);
				xmax = max(xmax, x), ymax = max(ymax, y);
				if (u == i) break;
			}
			a[x][y] = '.';
			l = x, r = y;
			dir = nxtdir[dir][u];
		}
		cout<<(xmax - xmin + 1)<<' '<<(ymax - ymin + 1)<<'\n';
		FORN(i, xmin, xmax + 1) {FORN(j, ymin, ymax + 1){
			if (!a[i][j]) a[i][j] = '#';
			cout<<a[i][j];
		}cout<<'\n';}
	}
}
close