#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int N, R, B;
int id[MAXN], parb[MAXN], parr[MAXN];
char str[MAXN];

int main() {
	scanf("%d %d %d %s", &N, &R, &B, str+1);
	
	int k = 0;
	parb[0] = parr[0] = 0;
	
	stack<vector<int> > ans;
	
	for(int i=1; i<=N; i++) {
		++k;
		if (str[i] == 'B') parb[k] = 1;
		else parb[k] = 0;
		if (str[i] == 'R') parr[k] = 1;
		else parr[k] = 0;
		parb[k] += parb[k-1];
		parr[k] += parr[k-1];
		id[k] = i;
		if (k >= R+B && parb[k] - parb[k-R-B] == B && parr[k] - parr[k-R-B] == R) {
			vector<int> cur;
			for(int j=k; j>k-R-B; j--) {
				cur.push_back(id[j]);
			}
			k -= R+B;
			sort(cur.begin(), cur.end());
			ans.push(cur);
		}
	}
	
	if (k != 0) printf("NO\n");
	else {
		printf("YES\n%u\n", ans.size());
		while(!ans.empty()) {
			vector<int> & cur = ans.top();
			for(int i=0; i<(int)cur.size(); i++) {
				printf("%d ", cur[i]);
			}
			printf("\n");
			ans.pop();
		}
	}
	
	return 0;
}