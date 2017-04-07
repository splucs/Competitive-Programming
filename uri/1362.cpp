#include <cstdio>
#include <map>
#include <cstring>
using namespace std;

bool matched[70], called[70];
map<int, map<int, bool> > adj;

bool aug(const int n, const bool m){
	called[n]=true;
	if(!matched[n] && !m){
		matched[n]=true;
		return true;
	}
	map<int, map<int, bool> >::iterator itl;
	map<int, bool>::iterator it;
	itl = adj.find(n);
	for(it = itl->second.begin(); it!=itl->second.end(); it++){
		if (!called[it->first] && m!=it->second && aug(it->first, it->second)){
			adj[n][it->first] = adj[it->first][n] = m;
			matched[n]=true;
			return true;
		}
	}
	return false;
}

int main(){
	int T, N, M, x;
	bool possible;
	scanf("%d", &T);
	char word[5];
	for(int caso=1; caso<=T; caso++){
		scanf("%d %d", &N, &M);
		for(int i=0; i<M; i++){
			scanf(" %s", word);
			if(!strcmp("XXL", word)) x=0;
			else if(!strcmp("XL", word)) x=1;
			else if(!strcmp("L", word)) x=2;
			else if(!strcmp("M", word)) x=3;
			else if(!strcmp("S", word)) x=4;
			else if(!strcmp("XS", word)) x=5;
			for(int j=x*N/6; j<(x+1)*N/6; j++){
				adj[N+i][j]=adj[j][N+i]=false;
			}
			scanf(" %s", word);
			if(!strcmp("XXL", word)) x=0;
			else if(!strcmp("XL", word)) x=1;
			else if(!strcmp("L", word)) x=2;
			else if(!strcmp("M", word)) x=3;
			else if(!strcmp("S", word)) x=4;
			else if(!strcmp("XS", word)) x=5;
			for(int j=x*N/6; j<(x+1)*N/6; j++){
				adj[N+i][j]=adj[j][N+i]=false;
			}
		}
		for(int i=0; i<M+N; i++) matched[i]=false;
		possible = true;
		for(int i=N; i<M+N && possible; i++){
			for(int j=0; j<M+N; j++) called[j]=false;
			if (!matched[i] && !aug(i, true)) possible=false;
		}
		if(possible) printf("YES\n");
		else printf("NO\n");
		adj.clear();
	}
	return 0;
}