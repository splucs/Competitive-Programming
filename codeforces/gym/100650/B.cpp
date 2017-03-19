#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

int N, D, des[MAXN];
string str;
map<string, int> str2id;
string id2str[MAXN];
vector<int> adj[MAXN], ans[MAXN];

void merge(int a, int b)
{
	while (ans[a].size() < ans[b].size()+1) ans[a].push_back(0);
	for(int i=0; i<(int)ans[b].size(); i++){
		ans[a][i+1]+=ans[b][i];
	}
}

void dfs(int u)
{
	if (ans[u].size() > 0) return;
	ans[u].push_back(1);
	for(int i=0, v; i<(int)adj[u].size(); i++){
		v = adj[u][i];
		dfs(v);
		merge(u, v);
	}
}

bool comp(int a, int b){
	if (des[a] != des[b]) return des[a] > des[b];
	return id2str[a] < id2str[b];
}

int main()
{
	int T, ids, u, v, k;
	scanf("%d", &T);
	for(int t=1; t<=T; t++)
	{
		str2id.clear();
		scanf("%d %d", &N, &D);
		ids = 0;
		for(int i=0; i<MAXN; i++){
			adj[i].clear();
			ans[i].clear();
			id2str[i].clear();
		}
		for(int i=1; i<=N; i++){
			cin >> str >> k;
			if (!str2id.count(str)){
				str2id[str] = ids++;
				//cout << str << " " << str2id[str] << endl;
				id2str[str2id[str]] = str;
			}
			u = str2id[str];
			for(int i=0; i<k; i++){
				cin >> str;
				if (!str2id.count(str)){
					str2id[str] = ids++;
				//cout << str << " " << str2id[str] << endl;
					id2str[str2id[str]] = str;
				}
				v = str2id[str];
				adj[u].push_back(v);
			}
		}
		for(int i=0; i<ids; i++){
			dfs(i);
			if (D < (int)ans[i].size()){
				des[i] = ans[i][D];
			}
			else des[i] = 0;
			
			/*printf("%d:", i);
			for(int j=0; j<(int)ans[i].size(); j++){
				printf(" %d", ans[i][j]);
			}
			printf("\n");*/
		}
		int max1=-1, max2=-1, max3=-1;
		for(int i=ids-1; i>=0; i--){
			if (des[i] > max1) max1 = des[i];
		}
		for(int i=ids-1; i>=0; i--){
			if (des[i] > max2 && des[i] < max1) max2 = des[i];
		}
		for(int i=ids-1; i>=0; i--){
			if (des[i] > max3 && des[i] < max2 && des[i] < max1) max3 = des[i];
		}
		if (max1 == 0) max1 = -1;
		if (max2 == 0) max2 = -1;
		if (max3 == 0) max3 = -1;
		vector<int> idans;
		for(int i=0; i<ids; i++){
			if (des[i] == max1 || des[i] == max2 || des[i] == max3)
				idans.push_back(i);
		}
		sort(idans.begin(), idans.end(), &comp);
		printf("\nTree %d:\n", t);
		for(int i=0; i<(int)idans.size(); i++){
			if (i >= 3 && des[idans[i]] != des[idans[i-1]]) break;
			cout << id2str[idans[i]] << " " << des[idans[i]] << endl;
		}
	}
	return 0;
	
}