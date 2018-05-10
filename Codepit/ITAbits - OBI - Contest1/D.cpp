#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009
#define MAXM 309
#define MOD 1000000007
#define INF 0x3f3f3f3f
#define EPS 1e-9
#define FOR(x,n) for(int x=0; (x)<(n); (x)++)
#define FOR1(x,n) for(int x=1; (x)<=(n); (x)++)
#define ROF(x,n) for(int x=(n)-1; (x)>=0; (x)--)
#define ROF1(x,n) for(int x=(n); (x)>0; (x)--)
#define pf push_front
#define pb push_back
#define fi first
#define se second
#define all(x) x.begin(), x.end()
typedef pair<int, int> ii;
typedef long long ll;
#define EPS 1e-9

int sum;
bool foundsum = false;
int square[3][3];

bool valid(int i, int j) {
	return i >= 0 && j >= 0 && i < 3 && j < 3;
}

bool checkline(int si, int sj, int di, int dj) {
	int nzeros = 0;
	int linesum = 0;
	for(int i = si, j = sj; valid(i, j); i += di, j += dj) {
		if (square[i][j] == 0) nzeros++;
		linesum += square[i][j];
	}
	if (nzeros == 0) {
		foundsum = true;
		sum = linesum;
	}
	if (nzeros == 1 && foundsum) {
		for(int i = si, j = sj; valid(i, j); i += di, j += dj) {
			if (square[i][j] == 0) {
				square[i][j] = sum - linesum;
				nzeros--;
			}
		}
	}
	return nzeros == 0;
}

int gettotalsum() {
	int tot = 0;
	FOR(i, 3) FOR(j, 3) tot += square[i][j];
	return tot;
}

int main() {
	//read
	FOR(i, 3) FOR(j, 3) scanf("%d", &square[i][j]);

	//corner cases
	if (square[0][0] == 0 && square[1][1] == 0 && square[2][2] == 0) {
		foundsum = true;
		sum = gettotalsum() / 2;
	}
	if (square[0][2] == 0 && square[1][1] == 0 && square[2][0] == 0) {
		foundsum = true;
		sum = gettotalsum() / 2;
	}

	//fill
	bool done;
	do {
		done = true;
		//columns
		done = checkline(0, 0, 1, 0) && done;
		done = checkline(0, 1, 1, 0) && done;
		done = checkline(0, 2, 1, 0) && done;

		//lines
		done = checkline(0, 0, 0, 1) && done;
		done = checkline(1, 0, 0, 1) && done;
		done = checkline(2, 0, 0, 1) && done;

		//diagonals
		done = checkline(0, 0, 1, 1) && done;
		done = checkline(2, 0, -1, 1) && done;
	} while (!done);

	//print
	FOR(i, 3) {
		FOR(j, 3) printf("%d%c", square[i][j], j == 2 ? '\n' : ' ');
	}
	return 0;
}