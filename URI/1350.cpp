#include <cstdio>
#include <map>
using namespace std;

map<int, map<int, bool> > adj;
int vet[1009];
int pos, neg;
bool consistent;

void solve(int a){
	if (!consistent) return;
	map<int, map<int, bool> >::iterator it;
	map<int, bool>::iterator itl;
	it = adj.find(a);
	bool inj;
	if (it==adj.end()) return;
	for(itl = it->second.begin(); itl!=it->second.end() && consistent; itl++){
		if (vet[itl->first]==-1){
			vet[itl->first] = (itl->second? vet[a]:!vet[a]);
			if (vet[itl->first]==1) pos++;
			else neg++;
			solve(itl->first);
		}
		else if (vet[itl->first] != (itl->second? vet[a]:!vet[a])) consistent=false;
	}
}

int main(){
	int N, x;
	bool t;
	char c[9];
	while(true){
		scanf("%d", &N);
		if (N==0) break;
		consistent=true;
		for(int i=1; i<=N; i++){
			scanf(" Sentence %d is %s", &x, c);
			if (c[0]=='t') t=true;
			else t=false;
			if (adj.count(i) && adj[i].count(x) && adj[i][x]!=t) consistent=false;
			else adj[i][x]=t;
			if (adj.count(x) && adj[x].count(i) && adj[x][i]!=t) consistent=false;
			else adj[x][i]=t;
			vet[i]=-1;
		}
		if (!consistent){
			printf("Inconsistent\n");
			adj.clear();
			continue;
		}
		x=0;
		for(int i=1; i<=N && consistent; i++){
			if (vet[i]==-1){
				pos=neg=0;
				vet[i]=1;
				pos++;
				solve(i);
				x+=(pos>neg?pos:neg);
			}
		}
		adj.clear();
		if (consistent) printf("%d\n", x);
		else printf("Inconsistent\n");
	}
	return 0;
}