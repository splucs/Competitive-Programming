#include <bits/stdc++.h>
using namespace std;

map<string,int> vals;
string pattern;
string lyrics;
vector<int> b;
int cnt;

void addLyrics(string s,vector<int> &pot){
	string aux = "";
	for (int i=0;i<s.size();i++){
		aux = "";
		while (i<s.size()&&s[i]!=' ')aux.push_back(s[i++]);
		if (!vals.count(aux))vals[aux] = cnt++;
		pot.push_back(vals[aux]);
	}
}

void kmp(string s){
	int m = s.size();
	b.resize(m+1);
	b[0] = -1;
	for (int i=0,j=-1;i<m;){
		while (j>=0 && s[i]!=s[j])j = b[j];
		i++, j++;
		b[i] = j;
	}
}

int match(string P,string T){
	int n = T.size(), m = P.size();
	int cnt = 0;
	
	for (int i=0,j=0;i<n;){
		while (j>=0&&T[i]!=P[j]) j=b[j];
		i++,j++;
		if (j==m){
			cnt++;
			j = b[j];
		}
	}
	return cnt;
}

int readVals(string s){
	b.clear();
	int baddass = 0;
	pattern = s;
	lyrics = "";
	while (getline(cin,s)&& s != ""){
		lyrics+=s;
	}
	kmp(pattern);
	return match(pattern, lyrics);
}

int main(){
	
	int n,badass,index,bad;
	string s;
	
	while (getline(cin,s)&&s!="EOF"){
		
		bad = readVals(s);
		cin>>n;
		index = -1;
		getline(cin,s);
		//cout<<"here";
		
		for (int i=0;i<n;i++){
			getline(cin,s);
			badass = readVals(s);
			if (badass>bad){
				index = i+1, bad = badass;
			}
		}
		cout<<index<<endl;
	}
}