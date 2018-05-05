#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int N, sz, id[MAXN], bal[MAXN];
string str[MAXN];
char ans[MAXN];

bool comp(int i, int j) {
	if (bal[i] == bal[j]) return str[i].size() > str[j].size();
	return bal[i] < bal[j];
}

int main() {
	cin >> N;
	sz = 0;
	for(int i = 0; i < N; i++) {
		cin >> str[i];
		id[i] = i;
		bal[i] = 0;
		sz += str[i].size();
		for(int j = 0; j < (int)str[i].size(); j++) {
			if (str[i][j] == 'h') bal[i]++;
			else bal[i]--;
		}
	}

	sort(id, id+N, comp);

	for(int it = 0, k = 0; it < N; it++) {
		int i = id[it];
		for(int j = 0; j < (int)str[i].size(); j++) {
			ans[k++] = str[i][j];
		}
	}
	ans[sz] = 0;

	int val = 0, scount = 0;
	for(int i = 0; i < sz; i++) {
		if (ans[i] == 's') scount++;
		else val += scount;
	}

	printf("%d\n", val);
	return 0;
}