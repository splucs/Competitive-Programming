#include <bits/stdc++.h>
using namespace std;
#define MAXN 109

int num(char c){
	if (c>='a'&&c<='z')return c-'a'+1;
	return 0;
}

void encrypt(string s){
	int val[MAXN];
	char ans[MAXN];
	int n = s.size();
	val[0] = num(s[2]);
	for (int i=3;i<(int)s.size();i++){
		val[i-2] = (val[i-3]+num(s[i]))%27;
	}
	for (int i=0;i<n-2;i++){
		ans[i] = val[i]==0?' ':val[i]-1+'a';
	}
	ans[n-2] = 0;
	cout<<ans<<endl;
}

void decrypt(string s){
	int val[MAXN];
	char ans[MAXN];
	int n = s.size();
	val[0] = num(s[2]);
	for (int i=3;i<(int)s.size();i++){
		val[i-2] = (num(s[i])-num(s[i-1])+27)%27;
	}
	for (int i=0;i<n-2;i++){
		ans[i] = val[i]==0?' ':val[i]-1+'a';
	}
	ans[n-2] = 0;
	cout<<ans<<endl;
}

int main(){
	int n;
	string s;
	cin>>n;
	getline(cin,s);
	while (n-->0){
		getline(cin,s);
		if (s[0]=='e')encrypt(s);
		else decrypt(s);
	}
}