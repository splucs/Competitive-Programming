#include <cstdio>
#include <vector>
#include <cstring>
#include <algorithm>
#include <string>
using namespace std;
#define MAXN 1009

int N, order[MAXN], m;
vector<string> prob;

bool comp(int a, int b){
	char ca, cb;
	for(int i=0; i<(int)max(prob[a].size(), prob[b].size()); i++){
		ca = (i < (int)prob[a].size() ? prob[a][i] : 'Z'+1);
		cb = (i < (int)prob[b].size() ? prob[b][i] : 'Z'+1);
		if (ca != cb) return ca < cb;
	}
	return a < b;
}

int main(){
	scanf("%d", &N);
	char c;
	prob.assign(N+1, string());
	for(int i=1; i<=N; i++){
		order[i] = i;
		scanf("%d", &m);
		for(int j=0; j<m; j++){
			scanf(" %c", &c);
			prob[i].push_back(c);
		}
		sort(prob[i].begin(), prob[i].end());
	}
	sort(&order[1], &order[1+N], &comp);
	for(int i=1; i<=N; i++){
		printf("%d\n", order[i]);
	}
	return 0;
}