#include <bits/stdc++.h>
using namespace std;
#define MAXN 200001

int nxt[MAXN];
vector<int> ans;

int main(){
	int n,a;
	int vals[MAXN],qtt,degree[MAXN];
	
	while (scanf("%d",&n)!=EOF){
		ans.clear();
		qtt = 0;
		
		for (int i=1;i<=2*n;i++)degree[i] = 0;
		for (int i=1;i<=2*n;i++){
			scanf("%d",&a);
			nxt[i] = a;
			degree[a]++;
		}for (int i=1;i<=2*n;i++){
			if (degree[i]==0)vals[qtt++] = i;
		}for (int i=0;i<qtt;i++){
			int u = vals[i];
			ans.push_back(u);
			degree[u] = -1;
			if (degree[nxt[u]]>=0){
				degree[nxt[u]] = -1;
				int v = nxt[nxt[u]];
				degree[v]--;
				if (degree[v]==0)vals[qtt++] = v;
			}
		}for (int i=1;i<=2*n;i++){
			if (degree[i]>=0){
				int u = i;
				
				while (true){
					if (degree[u]>=0){
						degree[u] = degree[nxt[u]] = -1;
						ans.push_back(u);
						u = nxt[nxt[u]];
					}else
						u = nxt[u];
					if (u==i||nxt[u]==i)break;
				}
			}
		}
		for (int i=0;i<(int)ans.size();i++){
			printf("%d ",ans[i]);
		}printf("\n");
	}
}