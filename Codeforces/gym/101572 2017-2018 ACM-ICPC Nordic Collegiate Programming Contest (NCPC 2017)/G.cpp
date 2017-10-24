#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

typedef pair<int, int> ii;
map<ii, int> sit2id;
int solved[MAXN], pen[MAXN], t[MAXN], p[MAXN];
int bit[MAXN];

void update(int i, int v) {
	while(i < MAXN) {
		bit[i] += v;
		i += (i&-i);
	}
}

int query(int i) {
	int sum = 0;
	while (i > 0) {
		sum += bit[i];
		i -= (i&-i);
	}
	return sum;
}

int query(int i, int j) {
	if (i > j) return 0;
	return query(j) - query(i-1);
}

int main() {
	int N, M;
	scanf("%d %d", &N, &M);
	sit2id[ii(0, 0)] = 0;
	for(int j=0; j<M; j++) {
		scanf("%d %d", &t[j], &p[j]);
		solved[t[j]]++;
		pen[t[j]] += p[j];
		sit2id[ii(solved[t[j]], -pen[t[j]])] = 0;
	}
	
	int cnt = 0;
	for(map<ii, int>::iterator it = sit2id.begin(); it != sit2id.end(); it++) {
		it->second = ++cnt;
	}
	
	memset(&solved, 0, sizeof solved);
	memset(&pen, 0, sizeof pen);
	update(sit2id[ii(0, 0)], N);
	for(int j=0; j<M; j++) {
		update(sit2id[ii(solved[t[j]], -pen[t[j]])], -1);
		solved[t[j]]++;
		pen[t[j]] += p[j];
		update(sit2id[ii(solved[t[j]], -pen[t[j]])], 1);
		printf("%d\n", query(sit2id[ii(solved[1], -pen[1])]+1, MAXN-1) + 1);
	}
	
	return 0;
}