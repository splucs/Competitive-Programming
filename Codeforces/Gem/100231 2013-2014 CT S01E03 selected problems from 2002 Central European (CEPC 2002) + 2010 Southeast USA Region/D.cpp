#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009

struct stand{
	int k,da,db;
	stand(){}
	stand(int _k,int _da,int _db){
		k=_k,da=_da,db=_db;
	}
	
	bool operator<(stand other) const{
		return abs(da-db)>abs(other.da-other.db);
	}
};

int main(){
	int n,a,b,k,da,db,ans, p;
	stand s[MAXN];
	while (cin>>n>>a>>b && n!=0){
		ans = 0;
		for (int i=0;i<n;i++){
			cin>>k>>da>>db;
			s[i] = stand(k,da,db);
		}
		sort(s,s+n);
		for (int i=0;i<n;i++){
			k = s[i].k, da = s[i].da, db = s[i].db;
			if (da<db){
				p = min(k,a);
				a -= p;
				b -= k - p;
				ans+= da*p + db*(k-p);
			}else{
				p = min(k,b);
				b -= p;
				a -= k - p;
				ans+= db*p + da*(k-p);
			}
		}
		cout<<ans<<endl;
	}
}