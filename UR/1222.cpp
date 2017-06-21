#include <cstdio>
#include <string>
#include <iostream>
using namespace std;

int main(int argc, char const *argv[])
{
	int N, L, C, found, last, size, l;
	string conto;
	while(scanf(" %d %d %d ", &N, &L, &C)!=EOF){
		last=-1;
		l=1;
		getline(cin, conto);
		size=-1;
		found = conto.find(' ', 0);
		while(found!=string::npos){
			size += found-last;
			if (size>C){
				l++;
				size=found-last-1;
			}
			last = found;
			found = conto.find(' ', found+1);
		}
		found = conto.size();
		size += found-last;
		if (size>C){
			l++;
			size=found-last-1;
		}
		if (l%L==0) printf("%d\n", l/L);
		else printf("%d\n", l/L+1);
	}
	return 0;
}