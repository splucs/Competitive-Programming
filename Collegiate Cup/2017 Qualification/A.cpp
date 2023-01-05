#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

typedef pair<int, int> ii;
int N, K, v[MAXN];
set<ii> lo, hi;
ii mid;

void print(){
	printf("lo:");
	for(set<ii>::iterator it = lo.begin(); it!=lo.end(); it++) {
		printf(" %d", it->first);
	}
	printf("\nmid: %d\n", mid.first);
	printf("hi:");
	for(set<ii>::iterator it = hi.begin(); it!=hi.end(); it++) {
		printf(" %d", it->first);
	}
	printf("\n");
}

int main() 
{
	scanf("%d %d", &N, &K);
	for(int i=1; i<=N; i++) {
		scanf("%d", &v[i]);
	}
	for(int i=1; i<=K; i++){
		hi.insert(ii(v[i], i));
	}
	for(int i=1; i<=K/2; i++){
		lo.insert(*hi.begin());
		hi.erase(hi.begin());
	}
	mid = *hi.begin();
	hi.erase(hi.begin());
	ii ans = mid, tmp;
	for(int i=2; i<=N-K+1; i++){
		int j = i+K-1;
		ii del = ii(v[i-1], i-1);
		if (lo.count(del)){
			lo.erase(del);
			lo.insert(mid);
		}
		else if (hi.count(del)){
			hi.erase(del);
			hi.insert(mid);
		}
		mid = ii(v[j], j);
		while(K > 1 && (lo.rbegin()->first > mid.first || hi.begin()->first < mid.first)){
			if (lo.rbegin()->first > mid.first){
				tmp = *lo.rbegin();
				lo.erase(tmp);
				lo.insert(mid);
				mid = tmp;
			}
			if (hi.begin()->first < mid.first){
				tmp = *hi.begin();
				hi.erase(tmp);
				hi.insert(mid);
				mid = tmp;
			}
		}
		ans = max(ans, mid);
	}
	printf("%d\n", ans.first);
	return 0;
}