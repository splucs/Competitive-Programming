#include <bits/stdc++.h>
using namespace std;
#define EPS 1e-9

int prox[52];
double probs[2][2][52];
int n;

void verify(int i,int j,double prob){
	if (j<0)j = 0;
	if (j>n) j=n+1;
	int index = prox[j];
	if (index==-1)probs[(i+1)%2][1][j]+=prob;
	else probs[(i+1)%2][0][index] += prob;
}

void simulate(int i){
	double prob;
	for (int j=0;j<=n+1;j++){
		prob = probs[i%2][0][j]*0.5;
		verify(i,j+1,prob);
		verify(i,j+2,prob);
		probs[(i+1)%2][0][j] += probs[i%2][1][j];
		probs[i%2][1][j] = 0;
		probs[i%2][0][j] = 0;
		//cout<<probs[(i+1)%2][0][j]<<" ";
	}//cout<<endl;
}

int main(){
	int t,c,dist;
	char op;
	cin>>c;
	while (c-->0){
		cin>>n>>t;
		prox[0]=0,prox[n+1] = n+1;
		for (int i=1;i<=n;i++){
			cin>>op;
			if (op=='0')prox[i] = i;
			else if (op=='L')prox[i] = -1;
			else {
				cin>>dist;
				prox[i] = op=='+'?i+dist:i-dist;
			}
			for (int j=0;j<4;j++)probs[j/2][j%2][i] = 0;
		}
		for (int j=0;j<4;j++)probs[j/2][j%2][n+1] = 0;
		probs[1][1][0] = probs[0][1][0] = probs[1][0][0] = 0;
		probs[0][0][0] = 1;
		for (int i=0;i<t;i++)simulate(i);
		
		double ans = probs[t%2][0][n+1];
		if (abs(ans-0.5)<EPS)cout<<"Push. 0.5000"<<endl;
		else if (ans>0.5)printf("Bet for. %.4lf\n",ans);
		else printf("Bet against. %.4lf\n",ans);
	}
}