#include <iostream>
#include <string>
#include <cstdio>
using namespace std;

int valordec(string num){
	int cont=1, valor=0;
	for (int i = num.size()-1; i >= 0; --i)
	{
		valor+=(num[i]-'0')*cont;
		cont*=10;
	}
	return valor;
}

int valorbin(string num){
	int cont=1, valor=0;
	for (int i = num.size()-1; i >= 0; --i)
	{
		valor+=(num[i]-'0')*cont;
		cont*=2;
	}
	return valor;
}

int valorhex(string num){
	int cont=1, valor=0;
	for (int i = num.size()-1; i >= 0; --i)
	{
		if (num[i]>='0' && num[i]<='9')
			valor+=(num[i]-'0')*cont;
		else valor+=(num[i]-'a'+10)*cont;
		cont*=16;
	}
	return valor;
}

string dec(int valor){
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

string hex(int valor){
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
		else ans.push_back((char)vet[n-1-i]-10+'a');
	}
	return ans;
}

string bin(int valor){
	int vet[50], n=0;
	string ans;
	while(valor>0){
		vet[n++]=valor%2;
		valor/=2;
	}
	for (int i = 0; i < n; ++i)
	{
		ans.push_back((char)vet[n-1-i]+'0');
	}
	return ans;
}

int main()
{
	int N, valor;
	cin >> N;
	string num, base;
	for(int caso=1; caso<=N; caso++){
		cin>> num >> base;
		if (base.compare("dec")==0){
			valor = valordec(num);
			printf("Case %d:\n%s hex\n%s bin\n\n", caso, hex(valor).c_str(), bin(valor).c_str());
		}
		else if (base.compare("hex")==0){
			valor = valorhex(num);
			printf("Case %d:\n%s dec\n%s bin\n\n", caso, dec(valor).c_str(), bin(valor).c_str());
		}
		else if (base.compare("bin")==0){
			valor = valorbin(num);
			printf("Case %d:\n%s dec\n%s hex\n\n", caso, dec(valor).c_str(), hex(valor).c_str());
		}
	}
	return 0;
}