#include <bits/stdc++.h>
using namespace std;
#define N 13
#define M 14
#define MAXN 17000

int arr[N];
char suit[N],val[N];
int dp[MAXN];
int nextstate[MAXN];

int getNum(char u){
	if (u>='0'&&u<='9')return u-'0';
	if (u=='T')return 10;
	if (u=='J')return 11;
	if (u=='Q')return 12;
	if (u=='K')return 13;
	return 14;
}

int rem(int state,int val,int qtt){
	int auxstate = state;
	
	for (int i=0;i<N && qtt;i++){
		int id = 1<<i;
		if (auxstate&id)continue;
		if (arr[i]==val)auxstate|=id, qtt--;
	}
	return auxstate;
}

int recurse(int state){
	if (state==(1<<N)-1)return 0;
	
	if (dp[state]!=-1)return dp[state];
	
	//cout<<state<<endl;
	
	int qtt[M+1] = {};
	int canuse = ((1<<N)-1)&(~state);
	
	while (canuse>0){
		int id = canuse&-canuse;
		canuse-=id;
		qtt[arr[(int)log2(id)]]++;
	}
	
	int ans = N+1, auxstate, aux;
	
	for (int i=2;i<=M;i++){
		if (qtt[i]==0)continue;
		for (int j=1;j<=4;j++){
			if (qtt[i]<j)break;
			auxstate = rem(state,i,j);
			aux = 1+recurse(auxstate);
			if (aux<ans){ans = aux;nextstate[state] = auxstate;}
		}
		for (int j=2;j<=M;j++){
			if (i==j)continue;
			if (qtt[i]>2 && qtt[j]>1){
				auxstate = rem(state,i,3);
				auxstate = rem(auxstate,j,2);
				aux = 1+recurse(auxstate);
				if (aux<ans){ans = aux;nextstate[state] = auxstate;}
			}
		}int cnt = 0;
		auxstate = state;
		for (int j=i;j<=M;j++){
			if (qtt[j]==0)break;
			cnt++;
			auxstate = rem(auxstate,j,1);
			if (cnt>=5){
				aux = 1+recurse(auxstate);
				if (aux<ans){ans = aux;nextstate[state] = auxstate;}
			}
		}
	}
	return dp[state] = ans;
}

int main(){
	int t;
	cin>>t;
	while (t-->0){
		char u,v;
		
		for (int i=0;i<N;i++){
			cin>>u>>v;
			
			arr[i] = getNum(u);
			suit[i] = v;
			val[i] = u;
		}
		
		memset(dp,-1,sizeof(dp));
		memset(nextstate,-1,sizeof(nextstate));
		
		cout<<recurse(0)<<endl;
		
		int state = 0;
		while (state!=(1<<N)-1){
			int s1 = nextstate[state]&(~state);
			while (s1>0){
				int id = s1&-s1;
				s1-=id;
				id = log2(id);
				cout<<val[id]<<suit[id]<<" ";
			}
			cout<<endl;
			state = nextstate[state];
		}
	}
}