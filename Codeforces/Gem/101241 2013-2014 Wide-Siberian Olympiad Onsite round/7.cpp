#include <bits/stdc++.h>
using namespace std;
#define MAXS 50009
#define MAXN 109
#define ALFA 67
#define MOD 40031
#define DT 901

int N, powd[MAXS];
vector<int> s[MAXN], hsh[MAXN];
vector<bool> vis[MAXN];

bool comphsh(int i, int j, int l) {
	int m = min((int)s[j].size(), (int)s[i].size() - l);
	int hj = hsh[j][m];
	int hi = (hsh[i][l+m] - (hsh[i][l]*powd[m])%MOD + MOD)%MOD;
	return hi == hj;
}

bool comp(int i, int j, int l) {
	if (!comphsh(i, j, l)) return false;
	int l1 = l, l2 = 0;
	while(l1 < (int)s[i].size() && l2 < (int)s[j].size()) {
		if (s[i][l1] != s[j][l2]) return false;
		l1++; l2++;
	}
	return true;
}

bool state(int i, int l) {
	if (vis[i][l]) return false;
	vis[i][l] = true;
	for(int j=0; j<N; j++) {
		if (!comphsh(i, j, l)) continue;
		if (i == j && l == 0) continue;
		
		if ((int)s[j].size() == (int)s[i].size() - l) return true;
		
		if ((int)s[j].size() > (int)s[i].size() - l) {
			if (state(j, (int)s[i].size() - l)) return true;
		}
		
		if ((int)s[j].size() < (int)s[i].size() - l) {
			if (state(i, l + (int)s[j].size())) return true;
		}
	}
	return false;
}

void buildhsh() {
	powd[0] = 1;
	int d = ALFA;
	for(int j=1; j<MAXS; j++) powd[j] = (d*powd[j-1])%MOD;
	
	for(int i=0; i<N; i++) {
		
		int h = 1, len = s[i].size();
		hsh[i].resize(len+1);
		vis[i].assign(len, false);
		
		hsh[i][0] = 0;
		for(int j=1; j<=len; j++) {
			hsh[i][j] = (d*hsh[i][j-1] + s[i][j-1])%MOD;
		}
	}
}

char buffer[MAXS];

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	char c;
	int v;
	scanf("%d", &N);
	for(int i=0; i<N; i++) {
		scanf(" %s", buffer);
		s[i].clear();
		int len = strlen(buffer);
		for(int j=0; j<len; j++) {
			c = buffer[j];
			if (c >= 'a' && c <= 'z') v = c - 'a';
			else if (c >= 'A' && c <= 'Z') v = c - 'A' + 'z'-'a';
			else if (c >= '0' && c <= '9') v = c - '0' + 'z'-'a' + 'Z'-'A';
			s[i].push_back(v);
		}
	}
	bool ok = false;
	buildhsh();
	for(int i=0; i<N && !ok; i++) {
		if (state(i, 0)) ok = true;
	}
	if (ok) printf("YES\n");
	else printf("NO\n");

	fclose(stdin);
	fclose(stdout);
	return 0;
}