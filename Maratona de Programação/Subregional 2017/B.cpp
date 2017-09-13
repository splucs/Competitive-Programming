#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009
#define MAXLOOP 50000000

int N,T,A0,X,Y;
int used[1000009];

int main(){
	int mask = 0,k,cnt,p;
	cin>>N>>T>>A0>>X>>Y;
	for (int i=0;i<T;i++){
		cin>>k;
		mask|=(1<<k);
	}
	
	memset(used, -1, sizeof(used));
	int acum = 0, F = -1, I = -1;
	for (int i=0;i<MAXLOOP;i++){
		acum = (acum + A0)%X;
		//printf("%d %d\n", A0, acum);
		if (acum == 0 && i+1 >= Y) {
			F = i; I = 0;
			break;
		}
		
		if (used[acum] < 0) {
			used[acum] = i;
		} else if (i-used[acum] >= Y) {
			F = i; I = used[acum]+1;
			break;
		}
		
		p = A0&mask;
		cnt = 0;
		A0>>=1;
		while(p>0){cnt++,p-=p&(-p);}
		A0 = A0|((cnt%2)<<(N-1));
		//cout<<A0<<endl;
	}
	if (F == -1) {
		cout << "impossivel" << endl;
	} else cout << I << " " << F << endl;
}
