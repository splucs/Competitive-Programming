#include <bits/stdc++.h>

using namespace std;

typedef pair<int, int> ii;

ii solvre(string s){
	int p = 0;
	int a = 0;
	for(int i = 0; i<(int) s.length(); i++){
		if(s[i]=='('){
			a++;
		}else a--;
		p = min(p, a);
	}
	return ii(a-p, -p);
}

int main(){
	int n;
	vector<pair<int, ii> > pos, neg;
	vector<ii> ans;
	string s;
	cin>>n;
	for(int i = 0; i<n; i++){
		cin>>s;
		ii aux = solvre(s);
		int a = aux.first;
		int f = aux.second;
		if(a>=f){
			pos.push_back(make_pair(f, ii(a-f, i+1)));
		}else{
			neg.push_back(make_pair(-a, ii(a-f, i+1)));
		}
	}
	sort(pos.begin(), pos.end());
	sort(neg.begin(), neg.end());

	int atual = 0;
	for(int i = 0; i<(int) pos.size(); i++){
		if(atual<pos[i].first){
            printf("NO\n");
            return 0;
		}
		atual += pos[i].second.first;
		ans.push_back(pos[i].second);
	}
	for(int i = 0; i<(int) neg.size(); i++){
        int p = -neg[i].second.first - neg[i].first;
        if(atual<p){
            printf("NO\n");
            return 0;
        }
		atual += pos[i].second.first;
		ans.push_back(neg[i].second);
	}
	int aux = 0;
	for(int i = 0; i<n; i++){
		aux += ans[i].first;
		if(aux<0){
			printf("NO\n");
			exit(0);
		}
	}
	if(aux!=0){
		printf("NO\n");
		return 0;
	}
	printf("YES\n");
	for(int i = 0; i<n; i++){
		if(i!=0) printf(" ");
		printf("%d", ans[i].second);
	}
	printf("\n");

}
