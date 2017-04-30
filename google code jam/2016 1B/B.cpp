#include <bits/stdc++.h>
using namespace std;
#define MAXN 19

typedef long long ll;
int C[MAXN], J[MAXN], Ca[MAXN], Ja[MAXN], N, gr;
ll pten[MAXN], dif, mindif;
char S1[MAXN], S2[MAXN];

void print(int* vet) {
	for(int i=0; i<N; i++){
		if (vet[i] != -1) printf("%d", vet[i]);
		else printf("?");
	}
}

void backtrack(int i);

void update(int i) {
	dif += (C[i]-J[i])*(pten[N-1-i]);
	if (J[i] > C[i]) gr = 1;
	if (J[i] < C[i]) gr = -1;
	backtrack(i+1);
	gr = 0;
	dif -= (C[i]-J[i])*(pten[N-1-i]);
}

void backtrack(int i) {
	/*for(int j=0; j<i; j++) printf(" ");
	printf("i=%d, gr=%d, curdif = %lld: ", i, gr, dif);
	print(C);
	printf(" ");
	print(J);
	printf("\n");*/
	if (i == N){
		if (abs(dif) < mindif){
			mindif = abs(dif);
			for(int j=0; j<N; j++){
				Ca[j] = C[j];
				Ja[j] = J[j];
			}
		}
		return;
	}
	if (gr != 0){
		bool cJ = false, cC = false;
		if (gr > 0){
			if (C[i] == -1) C[i] = 9, cC = true;
			if (J[i] == -1) J[i] = 0, cJ = true;
		}
		else {
			if (C[i] == -1) C[i] = 0, cC = true;
			if (J[i] == -1) J[i] = 9, cJ = true;
		}
		dif += (C[i]-J[i])*(pten[N-1-i]);
		backtrack(i+1);
		dif -= (C[i]-J[i])*(pten[N-1-i]);
		if (cC) C[i] = -1;
		if (cJ) J[i] = -1;
	}
	else if (C[i] == -1 && J[i] == -1){
		for(int m=0; m<3; m++){
			J[i] = m/2;
			C[i] = m%2;
			update(i);
			J[i] = -1;
			C[i] = -1;
		}
	}
	else if (J[i] == -1) {
		for(int j=-1; j<=1; j++){
			J[i] = C[i]+j;
			if (J[i] >= 0 && J[i] <= 9) update(i);
			J[i] = -1;
		}
	}
	else if (C[i] == -1) {
		for(int j=-1; j<=1; j++){
			C[i] = J[i]+j;
			if (C[i] >= 0 && C[i] <= 9) update(i);
			C[i] = -1;
		}
	}
	else {
		update(i);
	}
}

int main()
{
	int T;
	scanf("%d", &T);
	pten[0] = 1;
	for(int i=1; i<MAXN; i++) {
		pten[i] = 10*pten[i-1];
	}
	for(int caseNo = 1; caseNo <= T; caseNo++) {
		scanf(" %s %s", S1, S2);
		N = strlen(S1);
		mindif = pten[MAXN-1];
		for(int i=0; i<N; i++) {
			if (S1[i] == '?') C[i] = -1;
			else C[i] = S1[i] - '0';
			if (S2[i] == '?') J[i] = -1;
			else J[i] = S2[i] - '0';
		}
		backtrack(0);
		printf("Case #%d: ", caseNo);
		print(Ca);
		printf(" ");
		print(Ja);
		printf("\n");
	}
	return 0;
}