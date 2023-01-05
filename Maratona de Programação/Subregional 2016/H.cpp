#include <stdio.h>
#include <string>
#include <iostream>

using namespace std;


int main(){
	string s, vog="";
	
	cin>>s;
	
	int l=s.size();
	for(int i=0; i<l; i++){
		if(s[i]=='a' ||
			s[i]=='e' ||
			s[i]=='i' ||
			s[i]=='o' ||
			s[i]=='u'){
				vog+=s[i];
		}
	}
	
	//cout<<vog<<endl;
	
	l=vog.size();
	string ct="";
	for(int i=l-1; i>=0; i--){
		ct+=vog[i];
	}
	
	//cout<<ct<<endl;
	
	if(vog == ct){
		cout<<"S"<<endl;
	}
	else{
		cout<<"N"<<endl;
	}
	
	return 0;
}
