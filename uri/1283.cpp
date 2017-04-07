#include <cstdio>
#define RESTO 1000000007

int pd[109][209][209], comb[309][209];

int C(int n, int k){
	if (comb[n][k]>=0) return comb[n][k];
	if (n==k || k==0) comb[n][k]=1;
	else if (k<0 || k>n) comb[n][k]=0;
	else comb[n][k]=(C(n-1, k-1)+C(n-1, k))%RESTO;
	return comb[n][k];
}

int calculate(int caixa, int levar, int aindatenho){
	if (caixa==1){
		if (2*levar<=aindatenho){
			return 0;
		}
		else{
			return 1;
		}
	}
	if (pd[caixa][levar][aindatenho]>=0){
		return pd[caixa][levar][aindatenho];
	}
	if (2*levar>aindatenho){
		pd[caixa][levar][aindatenho] = C(caixa+aindatenho-1, aindatenho);
		return pd[caixa][levar][aindatenho];
	}
	int res=0, m=(aindatenho>2*levar-1?2*levar-1:aindatenho);
	for(int nestacaixa=0; nestacaixa<=m; nestacaixa++){
		res+=calculate(caixa-1, 2*levar-nestacaixa, aindatenho-nestacaixa);
		res%=RESTO;
	}
	pd[caixa][levar][aindatenho]=res;
	return res;
}

int main(){
	int S, B;
	for (int b=1; b<=100; b++){
		for(int i=0; i<=200; i++){
			for(int j=0; j<=200; j++){
				pd[b][i][j]=-1;
			}
		}
	}
	for(int i=0; i<309; i++){
		for(int j=0; j<209; j++){
			comb[i][j]=-1;
		}
	}
	while(scanf("%d %d", &S, &B)!=EOF){
		printf("%d\n", calculate(B-1, 1, S));
	}
	return 0;
}