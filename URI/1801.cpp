#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;
typedef long long int ull;

int main()
{
	ull x, y, n, xmax, xsize, res=0, valid;
	int vetx[15], vety[15], conty[10], contx[10];
	char word[15];
	scanf(" %s", word);
	n=1;
	xsize=strlen(word);
	x=0;
	for(int i=0; i<10; i++) contx[i]=0;
	for(int i=xsize-1; i>=0; i--){
		vetx[i]=word[i]-'0';
		vety[i]=vetx[i];
		contx[word[i]-'0']++;
		x+=(word[i]-'0')*n;
		n*=10;
	}
	sort(vety, vety+xsize);
	n=1;
	xmax=0;
	for(int i=0; i<xsize; i++){
		xmax+=vety[i]*n;
		n*=10;
	}
	n=1;
	while(n*n - x <= xmax){
		y = n*n - x;
		if(y<0){
			n++;
			continue;
		}
		for(int i=0; i<10; i++) conty[i]=0;
		for(int i=0; i<xsize; i++){
			vety[i]=y%10;
			conty[y%10]++;
			y/=10;
		}
		if(y>0){
			n++;
			continue;
		}
		valid=true;
		for(int i=0; i<10 && valid; i++){
			if(contx[i]!=conty[i]) valid=false;
		}
		if(vety[xsize-1]==0) valid=false;
		if(valid) res++;
		n++;
	}
	printf("%d\n", res);
	return 0;
}