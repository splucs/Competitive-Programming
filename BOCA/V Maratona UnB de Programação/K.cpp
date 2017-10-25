#include <bits/stdc++.h>
using namespace std;

char voyal[5] = {'a','e','i','o','u'};

int main(){
	int N,v;
	string s,ans;
	while(cin>>N){
		getline(cin,s);
		for (int i=0;i<N;i++){
			getline(cin,s);
			ans = "";
			v = 0;
			for (int j=0;j<s.size();j++){
				if (s[j]==' ')ans.push_back(' ');
				else {
					ans.push_back(s[j]);
					ans.push_back(voyal[v]);
					v = (v+1)%5;
				}
			}
			cout<<ans<<endl;
		}
	}
}