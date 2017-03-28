#include <bits/stdc++.h>
using namespace std;
typedef unsigned long long int ull;

int main(){
	ull x,y,k;
	int bits,ans=0;
	bool first,second;
	scanf("%I64u%I64u",&x,&y);
	for (int N=1;N<=63;N++){
		first = true;
		for (int M=1;M<=63;M++){
			bits = 0;
			k=0;
			second = false;
			while (true){
				k<<=N;
				k += ((1llu<<N)-1), bits+=N;
				if (k>y||bits>63) break;
				if ((first||second)&&k>=x) ans++;
				k<<=M,bits+=M;
				if (k>y||bits>63)break;
				if (k>=x) ans++;
				second = true;
			}first = false;
		}
	}
	printf("%d\n",ans);
}