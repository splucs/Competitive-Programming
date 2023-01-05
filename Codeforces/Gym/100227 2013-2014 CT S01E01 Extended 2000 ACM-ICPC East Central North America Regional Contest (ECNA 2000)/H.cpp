#include <bits/stdc++.h>
using namespace std;

string text,s1;

bool verify(int s,int m){
	char aux;
	int j;
	
	for (int i=0;i<(int)text.size();i+=m){
		int u = min(m,(int)text.size()-i);
		for (int j=0;j<u/2;j++){
			int first = i+j, last = i+u-j-1;
			aux = text[first];
			text[first] = text[last];
			text[last] = aux;
		}for (int j=0;j<u;j++)text[i+j] = ((text[i+j]-'A')+26-s)%26+'A';
	}//cout<<text<<endl;
	for (int i=0;i<(int)text.size();i++){
		for (j=0;j<s1.size();j++)if (i+j>=text.size()||text[i+j]!=s1[j])break;
		if (j==s1.size())return true;
	}
	return false;
}

int main(){
	int t,n,s,m;
	bool done;
	string aux;
	
	cin>>t;
	while (t-->0){
		cin>>n;
		done = false;
		text = "";
		int len = 0;
		while (len<n && cin>>s1){
			len+=s1.size();
			text+=s1;
		}
		cin>>s1;
		for (s=1;s<=25&&!done;s++){
			for (m=5;m<=min(20,n);m++){
				aux = text;
				//cout<<s<<" "<<m<<endl;
				if (verify(s,m)){
					cout<<s<<" "<<m<<endl;
					done = true;
					break;
				}
				text = aux;
			}
		}if (!done)cout<<"Crib is not encrypted."<<endl;
	}
}