#include <bits/stdc++.h>
using namespace std;
typedef pair<int,int> ii;
typedef vector<vector<int> > matrix;

int f[11];

int mdc(int a,int b){
	if (b==0)return a;
	return mdc(b,a%b);
}

void switchLines(matrix &a,int i,int j){
	ii tmp;
	int m = (int)a[i].size();
	for (int k=0;k<m;k++){
		tmp = a[i][k];
		a[i][k] = a[j][k];
		a[j][k] = tmp;
	}
}

void lineSumTo(matrix &a,int i,int j,ii c){
	int m = (int)a[0].size();
	int num,den,mp;
	for (int k=0;k<m;k++){
		num = a[j][k].first*c.second*a[i][k].second+a[i][k].first*c.first*a[j][k].second;
		den = a[i][k].second*c.second*a[j][k].second;
		int md = mdc(num,den);
		if (den/md<0)den = -den,num = -num;
		a[j][k] = ii(num/md,den/md);
	}
}

bool gauss(matrix &a,matrix &b){
	int n = (int)a.size();
	int m = (int)b.size();
	int num,den;
	ii p;
	for (int i=0,l;i<min(m,n);i++){
		l = i;
		while (l<n && a[l][i].first==0) l++;
		if (l==n) return false;
		switchLines(a,i,l);
		switchLines(b,i,l);
		for (int j=i+1;j<n;j++){
			num = a[j][i].first*a[i][i].second;
			den = a[j][i].second*a[i][i].first;
			int md = mdc(num,den);
			p = ii(-num/md,den/md);
			lineSumTo(a,i,j,p);
			lineSumTo(b,i,j,p);
		}
	}for (int i=min(n,m)-1;i>=0;i--){
		for (int j=0;j<i;j++){
			num = a[j][i].first*a[i][i].second;
			den = a[j][i].second*a[i][i].first;
			int md = mdc(num,den);
			p = ii(num/md,den/md);
			lineSumTo(a,i,j,p);
			lineSumTo(b,i,j,p);
		}
	}
	return true;
}

int main(){
	int n,m,j;
	matrix mat,b;
	vector<ii> aux;
	while(cin>>n>>m&&(n!=0||m!=0)){
		mat.clear();
		for (int i=0;i<n+m;i++)cin>>f[i];
		for (int i=0;i<m+n;i++){
			aux.clear();
			for (j=0;j<n&&i>=j;j++)aux.push_back(ii(f[i-j],1));
			while (j<n)aux.push_back(ii(0,1)),j++;
			for (j=0;j<i;j++)aux.push_back(ii(0,1));
			aux.push_back(ii(1,1));
			while (j<n)aux.push_back(ii(0,1)),j++;
			mat.push_back(aux);
			aux.clear();
			aux.push_back(ii(0,1));
			b.push_back(aux);
		}
	}
	gauss(mat,b);
}