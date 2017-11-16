#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

int N, K, c1[MAXN], c2[MAXN];
vector<int> col[MAXN];
typedef pair<unsigned int, int> ii;
set<ii> config;

int getMax() {
	if (config.empty()) return -1;
	int ans = config.rbegin()->second;
	config.erase(ii(col[ans].size(), ans));
	return ans;
}

int getMin() {
	if (config.empty()) return -1;
	int ans = config.begin()->second;
	config.erase(ii(col[ans].size(), ans));
	return ans;
}

void insertCol(int i) {
	if (!col[i].empty())
		config.insert(ii(col[i].size(), i));
}

void printblanket(int i) {
	printf("blanket %d: %d-%d\n", i, c1[i], c2[i]);
}

int main() {
	int c, sz;
	scanf("%d %d", &K, &N);
	for(int i=1; i<=K; i++) {
		scanf("%d", &c);
		c1[i] = c;
		if (c == -1) col[0].push_back(i);
		else col[c].push_back(i);
	}
	for(int i=1; i<=N; i++) {
		insertCol(i);
	}
	bool possible = true;
	while(!config.empty() && possible) {
		int m = getMin();
		int M = getMax();
		//printf("making a kit with %d and %d\n", m, M);
		sz = K/N;
		while(m >= 0 && sz > 0 && !col[m].empty()) {
			sz--;
			c2[col[m].back()] = (M == -1 ? 1 : M);
			//printblanket(col[m].back());
			col[m].pop_back();
		}
		while(M >= 0 && sz > 0 && !col[M].empty()) {
			sz--;
			c2[col[M].back()] = (m == -1 ? 1 : m);
			//printblanket(col[M].back());
			col[M].pop_back();
		}
		while(sz > 0 && !col[0].empty()) {
			sz--;
			c1[col[0].back()] = (m == -1 ? 1 : m);
			c2[col[0].back()] = (M == -1 ? 1 : M);
			//printblanket(col[0].back());
			col[0].pop_back();
		}
		if (sz > 0) possible = false;
		insertCol(m);
		insertCol(M);
	}
	if (possible) {
		while(!col[0].empty()) {
			c1[col[0].back()] = 1;
			c2[col[0].back()] = 1;
			col[0].pop_back();
		}
	}
	
	if (!possible) printf("No\n");
	else {
		printf("Yes\n");
		for(int i=1; i<=K; i++) {
			printf("%d %d\n", c1[i], c2[i]);
		}
	}
	return 0;
}