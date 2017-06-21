#include <bits/stdc++.h>
using namespace std;
typedef long long int ll;

int main(){
	char val[27],p,cur;
	vector<string> words;
	string s,aux;
	ll n,acum,ans;
	
	cin>>n;
	for (int i=0;i<n;i++){
		cin>>s;
		aux="";
		cur = 'a';
		for (int j=0;j<27;j++)val[j] = '.';
		for (int j=0;j<s.length();j++){
			p = s[j]-'a';
			if (val[p]=='.')val[p] = cur++;
			aux.push_back(val[p]);
		}
		words.push_back(aux);
	}
	sort(words.begin(),words.end());
	acum = 1;
	ans = 0;
	//for (int i=0;i<words.size();i++)cout<<words[i]<<endl;
	for (int i=1;i<words.size();i++){
		if (words[i]==words[i-1])acum++;
		else {
			ans += (acum*(acum-1))/2;
			acum=1;
		}
	}ans += (acum*(acum-1))/2;
	cout<<ans<<endl;
}