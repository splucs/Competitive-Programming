#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

long long int valordec(string num){
	long long int cont=1, valor=0;
	for (int i = num.size()-1; i >= 0; --i)
	{
		valor+=(num[i]-'0')*cont;
		cont*=10;
	}
	return valor;
}

long long int valorhex(string num){
	long long int cont=1, valor=0;
	for (int i = num.size()-1; i >= 0; --i)
	{
		if (num[i]>='0' && num[i]<='9')
			valor+=(num[i]-'0')*cont;
		else if (num[i]>='A' && num[i]<='Z')
			valor+=(num[i]-'A'+10)*cont;
		else valor+=(num[i]-'a'+10)*cont;
		cont*=16;
	}
	return valor;
}

string dec(long long int valor){
	int vet[50], n=0;
	string ans;
	while(valor>0){
		vet[n++]=valor%10;
		valor/=10;
	}
	for (int i = 0; i < n; ++i)
	{
		ans.push_back((char)vet[n-1-i]+'0');
	}
	return ans;
}

string hex(long long int valor){
	int vet[50], n=0;
	string ans;
	while(valor>0){
		vet[n++]=valor%16;
		valor/=16;
	}
	for (int i = 0; i < n; ++i)
	{
		if (vet[n-1-i]<=9)
			ans.push_back((char)vet[n-1-i]+'0');
		else ans.push_back((char)vet[n-1-i]-10+'A');
	}
	return ans;
}

int main(){
	string num, aux;
	long long int valor;
	while(true){
		cin>>num;
		if (num[0]=='-') break;
		if (num[1]=='x'){
			num.replace (0,  2,  "");
			valor = valorhex(num);
			printf("%s\n", dec(valor).c_str());
		}
		else{
			valor = valordec(num);
			printf("0x%s\n", hex(valor).c_str());
		}
	}
	return 0;
}
