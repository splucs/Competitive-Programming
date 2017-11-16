#include <bits/stdc++.h>
using namespace std;

int main(){
	string s;
	char c;
	int b = 0;
	
	while (cin>>s){
		c = s[s.size()-1];
		if (c=='-')b=max(0,b-1);
		else b++;
	}
	cout<<b<<endl;
}