#include <bits/stdc++.h>
using namespace std;
#define MAXN 50009

string str;
char straux[100];
map<string, int> p2id;
vector<int> cur, in;
map<vector<int>, int> ans;

void backtrack(unsigned int i) {
	if (i == cur.size()) {
		if(!ans.count(in)) ans[in] = 0;
		ans[in]++;
		return;
	}
	backtrack(i+1);
	in.push_back(cur[i]);
	backtrack(i+1);
	in.pop_back();
}

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int n, m, k;
	scanf("%d", &n);
	for(int i=1; i<=n; i++) {
		scanf("%d", &k);
		cur.clear();
		while(k-->0) {
			scanf(" %s", straux);
			str = string(straux);
			if (!p2id.count(str)) p2id[str] = p2id.size();
			cur.push_back(p2id[str]);
		}
		sort(cur.begin(), cur.end());
		in.clear();
		backtrack(0);
	}
	scanf("%d", &m);
	for(int i=1; i<=m; i++){
		scanf("%d", &k);
		cur.clear();
		while(k-->0) {
			scanf(" %s", straux);
			str = string(straux);
			if (!p2id.count(str)) p2id[str] = p2id.size();
			cur.push_back(p2id[str]);
		}
		sort(cur.begin(), cur.end());
		printf("%d\n", ans[cur]);
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}
