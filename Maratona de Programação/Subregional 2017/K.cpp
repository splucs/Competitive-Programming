#include <bits/stdc++.h>
using namespace std;
#define MAXINT 10000
typedef long long int ll;
typedef vector<vector<ll> > matrix;

matrix id(int n){
	matrix a;
	a.resize(n);
	for (int i=0;i<n;i++){
		a[i].assign(n,0);
		a[i][i] = 1;
	}return a;
}

matrix operator *(matrix a,matrix b){
	int n = (int)a.size();
	int m = (int)b.size();
	int p = (int)b[0].size();
	matrix c;
	c.resize(n);
	for (int i=0;i<n;i++){
		c[i].assign(p,0);
		for (int j=0;j<p;j++){
			for (int k=0;k<m;k++){
				c[i][j]=(c[i][j]+a[i][k]*b[k][j])%MAXINT;
			}
		}
	}
	return c;
}

matrix matrixExp(matrix a,int n){
	if (n==0)return id(a.size());
	matrix c = matrixExp(a,n/2);
	c = c*c;
	if (n%2!=0)c = c*a;
	return c;
}

int main(){
	int A,B,N,K;
	ll ans;
	cin>>A>>B>>N>>K;
	matrix a;
	a.resize(2);
	for (int i=0;i<2;i++)a[i].assign(2,0);
	a[0][0] = (2*A)%MAXINT;
	a[0][1] = ((B-A*A)+MAXINT)%MAXINT;
	a[1][0] = 1;
	a = matrixExp(a,N-1);
	ans = (a[0][1]*2+a[0][0]*2*A)%MAXINT;
	if (A*A>B||(A*A<B && N%2==0))ans = ((ans-1)+MAXINT)%MAXINT;
	
	while (K>1)ans/=10,K--;
	cout<<ans%10<<endl;
}
