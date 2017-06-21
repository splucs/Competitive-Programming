//questao 1
#include <cstdio>
#include <cstring>
long long int pow(int b, int e){
	if (e == 0) return 1;
	else return b*pow(b, e - 1);
}

int main(){
	long long int A, B, C;
	char SM[9], SI[9];
	bool modelA, modelB, original;
	while (true){
		scanf("%s", SM);
		scanf(" %s", SI);
		scanf("%lld", &C);
		if (strcmp(SM, "*") == 0 && strcmp(SI, "*") == 0 && C==0) break;
		modelA = (SM[3] >= 'A' && SM[3] <= 'Z');
		modelB = (SI[3] >= 'A' && SI[3] <= 'Z');
		A = B = 0;
		original=true;
		if (SM[3]>='A' && SM[3]<='Z' && SM[4]>='0' && SM[4]<='9') original=false;
		if (SM[4]>='A' && SM[4]<='Z' && SM[3]>='0' && SM[3]<='9') original=false;
		if (modelA){
		//	printf("modelA=true ");
			for (int i = 0; i < 5; i++){
				if (SM[i]=='A' || SM[i]=='C' || SM[i]=='M' || SM[i]=='I' || SM[i]=='P') original=false;
				if(SM[i] <= 'B') SM[i] -= 1;
				else if(SM[i] <= 'H') SM[i] -= 2;
				else if(SM[i] <= 'L') SM[i] -= 3;
				else if(SM[i] <= 'O') SM[i] -= 4;
				else SM[i] -= 5;
				A += (SM[i] - 'A')*pow(21, 4 - i) * 100;
			}
			A += (SM[5] - '0')*10;
			A += (SM[6] - '0');
		}
		else{
		//	printf("modelA=false ");
			for (int i = 0; i < 3; i++){
				A += (SM[i] - 'A')*pow(26, 2 - i) * 10000;
			}
			A += (SM[3] - '0') * 1000;
			A += (SM[4] - '0') * 100;
			A += (SM[5] - '0') * 10;
			A += (SM[6] - '0');
			A -= 25 * (26 * 26 + 26 + 1) * ((long long int)10000) + 10000;
		}
		if (SI[3]>='A' && SI[3]<='Z' && SI[4]>='0' && SI[4]<='9') original=false;
		if (SI[4]>='A' && SI[4]<='Z' && SI[3]>='0' && SI[3]<='9') original=false;
		if (modelB){
			//printf("modelB=true ");
			for (int i = 0; i < 5; i++){
				if (SI[i]=='A' || SI[i]=='C' || SI[i]=='M' || SI[i]=='I' || SI[i]=='P') original=false;
				if (SI[i] <= 'B') SI[i] -= 1;
				else if (SI[i] <= 'H') SI[i] -= 2;
				else if (SI[i] <= 'L') SI[i] -= 3;
				else if (SI[i] <= 'O') SI[i] -= 4;
				else SI[i] -= 5;
				B += (SI[i] - 'A')*pow(21, 4 - i) * 100;
			}
			B += (SI[5] - '0') * 10;
			B += (SI[6] - '0');
		}
		else{
			//printf("modelB=false ");
			for (int i = 0; i < 3; i++){
				B += (SI[i] - 'A')*pow(26, 2 - i) * 10000;
			}
			B += (SI[3] - '0') * 1000;
			B += (SI[4] - '0') * 100;
			B += (SI[5] - '0') * 10;
			B += (SI[6] - '0');
			B -= 25 * (26 * 26 + 26 + 1) * ((long long int)10000) + 10000;
		}
		//printf("SM = |%s| SI = |%s| A=%lld B=%lld\n", SM, SI, A, B);
		if (C >= B - A && B-A>0 && original) printf("Y\n");
		else printf("N\n");
	}
	return 0;
}