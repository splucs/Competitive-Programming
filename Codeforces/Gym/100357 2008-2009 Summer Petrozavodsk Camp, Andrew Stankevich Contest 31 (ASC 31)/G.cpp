#include <bits/stdc++.h>
#define MAXN 2200009
#define ALFA 26
#define FOR(x, n) for(int x=0; x<n; x++)
#define REP(x, n) for(int x=n-1; x>=0; x--)
#define FOR1(x, n) for(int x=1; x<=n; x++)
#define REP1(x, n) for(int x=n; x>0; x--)
#define pb push_back
#define all(x) x.begin(), x.end()
#define sz(x) (int (x.size()) )
#define mset(x, y) memset(&x, y, sizeof x)
using namespace std;

const int P = 29;
const int nM = 2;
const int M[nM] = {1000000007, 1000000009};

struct hasher {
	int val[nM];
	int st, en;
	hasher(int _st) : st(_st), en(_st) {
		FOR(i, nM) val[i] = 0;
	}
	void push_back(char c) {
		FOR(i, nM) val[i] = (val[i]*1ll*P + c+1) % M[i];
		en++;
	}
};

bool operator < (hasher a, hasher b) {
	if (a.en-a.st != b.en-b.st) a.en-a.st < b.en-b.st;
	FOR(i, nM) if (a.val[i] != b.val[i]) return a.val[i] < b.val[i];
	return false;
}

bool operator == (hasher a, hasher b) {
	if (a.en-a.st != b.en-b.st) return false;
	FOR(i, nM) if (a.val[i] != b.val[i]) return false;
	return true;
}

vector<hasher> arr;

void go(char s[], int off) {
	int phi[ALFA];
	FOR(i, ALFA) phi[i] = -1;
	int cnt = 0;
	int len = strlen(s);
	hasher hsh(off);
	FOR(i, len) {
		int c = s[i]-'a';
		if (phi[c] < 0) phi[c] = cnt++;
		c = phi[c];
		hsh.push_back(c);
		arr.pb(hsh);
	}
}

char s[MAXN];

int main() {
	#ifdef ONLINE_JUDGE
	freopen("pattern.in", "r", stdin);
	freopen("pattern.out", "w", stdout);
	#endif

	scanf("%s", s);
	int len = strlen(s);
	FOR(i, len) go(s+i, i);
	
	sort(all(arr));

	hasher ans(0);
	int val = 0;
	FOR(i, sz(arr)) {
		int j = i;
		while(j < sz(arr) && arr[i] == arr[j]) j++;
		if (val < (j-i)*(arr[i].en-arr[i].st)) {
			val = (j-i)*(arr[i].en-arr[i].st);
			ans = arr[i];
		}
		i = j-1;
	}
	s[ans.en] = 0;
	printf("%s\n", s + ans.st);

	return 0;
}