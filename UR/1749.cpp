#include <cstdio>
#include <map>
using namespace std;

map<int, map<int, int> > adj, mapa;
int N, res, conju[2], called[50009];

void dfs(int n, int con){
	conju[con]++;
	called[n]=true;
	map<int, map<int, int> >::iterator itl;
	map<int, int>::iterator it;
	itl = adj.find(n);
	for(it = itl->second.begin(); it!=itl->second.end(); it++){
		if (!called[it->first]) dfs(it->first, !con);
	}
}

int main(){
	int X, Y;
	map<int, map<int, int> >::iterator itl, itlnext;
	map<int, int>::iterator it, itnext;
	while(scanf("%d", &N)!=EOF){
		for(int i=1; i<=N; i++){
			scanf("%d %d", &X, &Y);
			mapa[X][Y]=i;
			called[i]=0;
		}
		for(itl = mapa.begin(); itl!=mapa.end(); itl++){
			for(it = itl->second.begin(); it!=itl->second.end(); it++){
				for(itlnext = itl; itlnext!=mapa.end() && itlnext->first - itl->first <=5; itlnext++){
					for(itnext = itlnext->second.lower_bound(it->first-5); itnext!=itlnext->second.end() && itnext->first - it->first <=5; itnext++){
						if (25LL >= (it->first-(long long int)itnext->first)*(it->first-(long long int)itnext->first)
							+ (itl->first-(long long int)itlnext->first)*(itl->first-(long long int)itlnext->first))
							adj[it->second][itnext->second]=adj[itnext->second][it->second]=1;
					}
				}
			}
		}
		res=0;
		conju[0]=conju[1]=0;
		for(int i=1; i<=N; i++){
			if(!called[i]){
				dfs(i, 0);
				if (conju[0]>conju[1]) res+=conju[1];
				else res+=conju[0];
				conju[0]=conju[1]=0;
			}
		}
		printf("%d\n", res);
	}
	return 0;
}