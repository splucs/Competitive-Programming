#include <bits/stdc++.h>
using namespace std;
typedef double ld;
#define EPS 1e-9
typedef vector<vector<ld> > matrix;

int D;

void switchLines(matrix & a, int i, int j){
	ld tmp;
	int m = (int)a[i].size();
	for(int k=0; k<m; k++){
		tmp = a[i][k];
		a[i][k] = a[j][k];
		a[j][k] = tmp;
	}
}

void lineSumTo(matrix & a, int i, int j, ld c){
	int m = (int)a[0].size();
	for(int k=0; k<m; k++){
		a[j][k] += c*a[i][k];
	}
}

bool gauss(matrix & a, matrix & b){
	int n = (int)a.size();
	int m = (int)a[0].size();
	ld p;
	for(int i = 0, l; i < min(n, m); i++){
		l = i;
		while(l < n && abs(a[l][i])<EPS) l++;
		if (l == n) return false;
		switchLines(a, i, l);
		switchLines(b, i, l);
		for(int j=i+1; j<n; j++){
			p = -a[j][i]/a[i][i];
			lineSumTo(a, i, j, p);
			lineSumTo(b, i, j, p);
		}
	}
	for(int i=min(n, m)-1; i>=0; i--){
		for(int j=0; j<i; j++){
			p = -a[j][i]/a[i][i];
			lineSumTo(a, i, j, p);
			lineSumTo(b, i, j, p);
		}
	}
	return true;
}

void buildMatrix(matrix &a,matrix &b, ld val ,int x){
	vector<ld> temp;
	
	int p = 1;
	
	for (int i=0;i<=D;i++){
		temp.push_back(p);
		p*=x;
	}
	a.push_back(temp);
	temp.clear();
	temp.push_back(val);
	b.push_back(temp);
}

void printMatrix(matrix a){
	cout<<"matrix:\n\n";
	for (int i=0;i<(int)a.size();i++){
		for (int j=0;j<a[i].size();j++){
			cout<<a[i][j]<<" ";
		}
		cout<<endl;
	}
}

int main(){
	ld v[10];
	matrix a,b;
	bool poss;
	int ans;
	
	while (scanf("%d",&D)&&D>0){
		for (int i=0;i<D+3;i++){
			scanf("%lf",&v[i]);
		}for (int i=0;i<D+3;i++){
			ans = i;
			a.clear();
			b.clear();
			
			for (int j=0;j<D+3;j++){
				if (i==j)continue;
				buildMatrix(a,b,v[j],j);
			}
			//printMatrix(a);
			//printMatrix(b);
			gauss(a,b);
			//printMatrix(a);
			//printMatrix(b);
			poss = true;
			//for (int i=0;i<=D;i++)if (abs(a[D+1][i])>EPS)poss = false;
			if (abs(b[D+1][0])>0.01){
				poss = false;
				//printf("%.9lf\n",b[D+1][0]);
			}
			if (poss)break;
		}
		printf("%d\n",ans);
	}
}