#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;
#define MAXN 109

int n;
set<int> vals[MAXN];

void intersect(set<int> &v,set<int> &s){
	set<int>::iterator it = v.begin();
	set<int>::iterator it2 = s.begin(),aux;
	
	int u,u1;
	while (it2!=s.end() && it!=v.end()){
		u = (*it), u1 = (*it2);
		if (u==u1)it++,it2++;
		else if (u1<u)it2++;
		else{
			aux = it;
			aux++;
			v.erase(it);
			it = aux;
		}
	}
	while (it!=v.end()){
		aux = it;
		aux++;
		v.erase(it);
		it = aux;
	}
}

map<ll,ll> pd;

ll solve(int idx,ll mask){
	//cout<<idx<<" "<<mask<<endl;
	if (idx==n)return 1;
	
	if (pd.count(mask))return pd[mask];
	
	set<int>::iterator it;
	ll ans = 0;
	for (it = vals[idx].begin();it!=vals[idx].end();it++){
		ll u = (*it);
		if (((1ll<<u)&mask)==0)ans += solve(idx+1,mask|(1ll<<u));
	}
	return pd[mask] = ans;
}

int main(){
	string s1,s2;
	int k,c1,c2;
	bool poss;
	ll ans;
	vector<int> pos[30];
	set<int> aux;
	
	while (cin>>n){
		cin>>s1>>s2;
		k = s1.size()/n;
		ans = 1;
		poss = true;
		
		for (int i=0;i<n;i++){
			for (int j=0;j<n;j++)vals[i].insert(j);
		}
		
		
		for (int j=0;j<k && poss;j++){
			
			for (int i=j*n;i<(j+1)*n;i++){
				c1 = s1[i]-'a';
				pos[c1].push_back(i-j*n);
			}
			for (int i=j*n;i<(j+1)*n;i++){
				c2 = s2[i]-'a';
				aux.clear();
				for (int p=0;p<pos[c2].size();p++){
					aux.insert(pos[c2][p]);
					//cout<<pos[c2][p];
				}//cout<<endl;
				intersect(vals[i-j*n],aux);
			}
			for (int i=0;i<30;i++)pos[i].clear();
		}
		/*for (int i=0;i<n;i++){
			cout<<i<<": ";
			for (set<int>::iterator it = vals[i].begin();it!=vals[i].end();it++){
				cout<<(*it)<<" ";
			}cout<<endl;
		}*/
		pd.clear();
		printf("%I64d\n",solve(0,0));
	}
}