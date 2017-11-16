#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

typedef pair<int, int> ii;
int v[MAXN];
vector<ii> ans;

int main(){
	int N;
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%d", &v[i]);
	}
	bool possible = true;
	for(int i=N-1, j=N-1; i>=0; i--){
		while (v[i] > 0 && j >= 0){
			ans.push_back(ii(i+1, j+1));
			j--;
			v[i]--;
		}
		if (i > j) possible = false;
	}
	if (!possible) printf("NO\n");
	else{
		printf("YES\n");
		for(int i=0; i<(int)ans.size(); i++){
			printf("%d %d\n", ans[i].first, ans[i].second);
		}
	}
	return 0;
}