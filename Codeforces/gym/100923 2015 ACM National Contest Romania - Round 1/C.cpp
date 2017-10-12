#include <bits/stdc++.h>
using namespace std;
#define MAXN
#define EPS 1e-9
typedef vector<vector<double> > matrix;

int N;

void switchLines(matrix & a, int i, int j){
	double tmp;
	int m = (int)a[i].size();
	for(int k=0; k<m; k++){
		tmp = a[i][k];
		a[i][k] = a[j][k];
		a[j][k] = tmp;
	}
}

void lineSumTo(matrix & a, int i, int j, double c){
	int m = (int)a[0].size();
	for(int k=0; k<m; k++){
		a[j][k] += c*a[i][k];
	}
}

bool gauss(matrix & a, matrix & b){
	int n = (int)a.size();
	int m = (int)a[0].size();
	double p;
	for(int i = 0, l; i < min(n, m); i++){
		l = i;
		while(l < n && fabs(a[l][i])<EPS) l++;
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
		for (int j=0;j<n;j++)b[i][j]/=a[i][i];
		a[i][i] = 1;
	}
	return true;
}

int main(){
	int t,a;
	vector<double> aux,aux1;
	matrix A,B;
	
	freopen("bujor.in", "r", stdin);
	freopen("bujor.out", "w", stdout);
	
	scanf("%d",&t);
	while (t-->0){
		A.clear(), B.clear();
		scanf("%d",&N);
		for (int i=0;i<N;i++){
			aux.clear();
			aux1.clear();
			for (int j=0;j<N;j++){
				scanf("%d",&a);
				aux.push_back(a);
				aux1.push_back(i==j);
			}
			A.push_back(aux);
			B.push_back(aux1);
		}
		gauss(A,B);
		/*for (int i=0;i<N;i++){
			for (int j=0;j<N;j++){
				printf("%.9lf ",A[i][j]);
			}
			printf("\n");
		}*/
		
		for (int i=0;i<N;i++){
			for (int j=0;j<N;j++){
				printf("%.9lf ",B[i][j]);
			}
			printf("\n");
		}
	}
}