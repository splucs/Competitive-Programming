#include <bits/stdc++.h>
using namespace std;
#define MAXN 59

vector<int> danger[MAXN];
char buffer[MAXN];

map<string, int> s2id;
int reduce(string str) {
	if (!s2id.count(str)) {
		int sz = s2id.size();
		s2id[str] = sz;
	}
	return s2id[str];
}

void getCode(const string & s, vector<int> & ans) {
	int n = s.size();
	ans.clear();
	for(int i = 0; i<n;) {
		int j = i+1;
		while(j < n && (s[j] < 'A' || s[j] > 'Z')) j++;
		string cur = s.substr(i, j-i);
		i = j;
		ans.push_back(reduce(cur));
	}
}

bool find(const vector<int> & s1, const vector<int> & s2) {
	int n = s1.size();
	int m = s2.size();
	for(int i = 0; i+m <= n; i++) {
		bool ok = true;
		for(int j = 0; j < m; j++) {
			if (s1[i+j] != s2[j]) {
				ok = false;
				break;
			}
		}
		if (ok) return true;
	}
	return false;
}

int main() {
	int T;
	scanf("%d", &T);
	string aux;
	vector<int> code;
	while(T --> 0) {
		int U, V;
		scanf("%d", &U);
		for(int i=0; i<U; i++) {
			scanf(" %s", buffer);
			aux = string(buffer);
			getCode(aux, danger[i]);
		}
		scanf("%d", &V);
		for(int i=0; i<V; i++) {
			scanf(" %s", buffer);
			aux = string(buffer);
			getCode(aux, code);
			bool ok = true;
			for(int j = 0; j < U; j++) {
				if (find(code, danger[j])) {
					ok = false;
					break;
				}
			}
			if (ok) printf("Prossiga\n");
			else printf("Abortar\n");
		}
		printf("\n");
	}
	return 0;
}