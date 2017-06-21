#include <cstdio>
#include <cstring>

bool addOne(bool* vet, bool* res, int C){
	bool carry=true;
	for(int i=C-1; i>=0; i--){
		res[i] = (vet[i] != carry);
		carry = (vet[i] && carry);
	}
	return !carry;
}

bool removeOne(bool* vet, bool* res, int C){
	bool carry = true;
	for(int i=C-1; i>=0; i--){
		res[i] = (vet[i] != carry);
		carry = (!vet[i] && carry);
	}
	return !carry;
}

int main(){
	int N, C;
	char vet[5009];
	bool hor[5009], ver[5009];
	bool aux[5009];
	scanf("%d", &N);
	while(N-->0){
		scanf(" %s", vet);
		C=strlen(vet)-1;
		for(int i=0; i<C; i++){
			hor[i]=(vet[i+1]=='q' || vet[i+1]=='r');
			ver[i]=(vet[i+1]=='q' || vet[i+1]=='p');
		}
		if(addOne(ver, aux, C)){
			printf("m");
			for(int i=0; i<C; i++){
				if (aux[i] && hor[i]) printf("q");
				else if (aux[i]) printf("p");
				else if (hor[i]) printf("r");
				else printf("s");
			}
			printf(" ");
		}
		else printf("<none> ");
		if(removeOne(ver, aux, C)){
			printf("m");
			for(int i=0; i<C; i++){
				if (aux[i] && hor[i]) printf("q");
				else if (aux[i]) printf("p");
				else if (hor[i]) printf("r");
				else printf("s");
			}
			printf(" ");
		}
		else printf("<none> ");
		if(removeOne(hor, aux, C)){
			printf("m");
			for(int i=0; i<C; i++){
				if (ver[i] && aux[i]) printf("q");
				else if (ver[i]) printf("p");
				else if (aux[i]) printf("r");
				else printf("s");
			}
			printf(" ");
		}
		else printf("<none> ");
		if(addOne(hor, aux, C)){
			printf("m");
			for(int i=0; i<C; i++){
				if (ver[i] && aux[i]) printf("q");
				else if (ver[i]) printf("p");
				else if (aux[i]) printf("r");
				else printf("s");
			}
			printf("\n");
		}
		else printf("<none>\n");
	}
	return 0;
}