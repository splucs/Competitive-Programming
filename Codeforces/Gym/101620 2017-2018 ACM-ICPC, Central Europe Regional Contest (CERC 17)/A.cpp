#include <bits/stdc++.h>
using namespace std;
#define FOR(i, n) for(int i = 0; i < n; i++)
#define INF 0x3f3f3f3f
#define MAXN 59
#define MAXM 29
#define pb push_back
#define fi first
#define se second
typedef pair<int, int> ii;

int r, ls, rs;

struct row {
	int num, navail;
	int isexit, distexit;
	bool avail[11];
	row(int n = 0) {
		num = n;
		if (n-1 == 0 || n-1 == r/2 + 1 || n-1 == r+2) isexit = 1;
		else isexit = 0;
		distexit = INF;
		distexit = min(distexit, abs(0-n));
		distexit = min(distexit, abs(r/2 + 1-n));
		distexit = min(distexit, abs(r+2-n));
	}
};

bool operator < (row a, row b) {
	if (a.isexit != b.isexit) return a.isexit < b.isexit;
	if (a.navail != b.navail) return a.navail < b.navail;
	if (a.distexit != b.distexit) return a.distexit > b.distexit;
	return a.num > b.num;
}

priority_queue<row> pq;
vector<ii> priority;
char plane[MAXN][15];

void occupy(row &u, int i, char c) {
	//printf("selected row %d, seat %d\n", u.num, i);
	assert(u.avail[i]);
	u.avail[i] = false;
	u.navail--;
	if (i < 5) ls++;
	if (i > 5) rs++;
	plane[u.num][i] = c;
}

int main() {
	priority.pb({4, 6});
	priority.pb({2, 8});
	priority.pb({0, 10});
	priority.pb({5, 5});
	priority.pb({4, 6});
	priority.pb({1, 9});
	int npar;
	ls = 0, rs = 0;
	scanf("%d %d", &r, &npar);
	FOR(i, r+3) {
		scanf(" %s", plane[i]);
		row u(i);
		FOR(j, 11) {
			if (plane[i][j] == '-') u.avail[j] = true;
			else {
				u.avail[j] = false;
				if (j < 5) ls++;
				if (j > 5) rs++;
			}
		}
		u.navail = 0;
		FOR(j, 11) if (u.avail[j]) u.navail++;
		//printf("row %d, isexit = %d, distexit = %d, navail = %d\n", i, u.isexit, u.distexit, u.navail);
		if (u.navail > 0) pq.push(u);
	}
	FOR(q, npar) {
		row u = pq.top();
		pq.pop();
		for(ii pp : priority) {
			int i = pp.fi;
			int j = pp.se;
			if (u.avail[i] && u.avail[j]) {
				if (ls > rs) occupy(u, j, q+'a');
				else occupy(u, i, q+'a');
				break;
			}
			else if (u.avail[i]) {
				occupy(u, i, q+'a');
				break;
			}
			else if (u.avail[j]) {
				occupy(u, j, q+'a');
				break;
			}
		}
		if (u.navail > 0) pq.push(u);
	}
	FOR(i, r+3) printf("%s\n", plane[i]);
	return 0;
}