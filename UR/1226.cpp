#include <cstdio>

typedef long long int ull;

typedef struct bignum{
	int num[25];
	int tam;
} bignum;

bignum convert(ull n){
	bignum res;
	res.tam=0;
	ull aux=n;
	while(aux>0){
		res.tam++;
		aux/=10;
	}
	aux=n;
	for(int i=res.tam-1; i>=0; i--){
		res.num[i]=aux%10;
		aux/=10;
	}
	return res;
}

ull convert_to_normal(bignum* n){
	ull res = 0, expo=1;
	for(int i = n->tam-1; i>=0; i--){
		res+=n->num[i]*expo;
		expo*=10;
	}
	return res;
}

bignum operator*(int k, bignum n){
	int carry=0, aux;
	for(int i = n.tam-1; i>=0; i--){
		aux = n.num[i];
		n.num[i]=(aux*k + carry)%10;
		carry = (aux*k + carry)/10;
	}
	if (carry>0){
		int aux;
		for(int i=0; i<=n.tam; i++){
			aux = n.num[i];
			n.num[i]=carry;
			carry=aux;
		}
		n.tam++;
	}
	return n;
}

bignum operator +(bignum a, bignum b){
	bignum res;
	int k, carry=0;
	if(a.tam>b.tam) k = a.tam-1;
	else k = b.tam-1;
	a.tam--;
	b.tam--;
	res.tam=k+1;
	while(a.tam>=0 || b.tam>=0){
		res.num[k]=carry;
		if(a.tam>=0) res.num[k]+=a.num[a.tam--];
		if(b.tam>=0) res.num[k]+=b.num[b.tam--];
		carry = res.num[k]/10;
		res.num[k]%=10;
		k--;
	}
	if (carry>0){
		int aux;
		for(int i=0; i<=res.tam; i++){
			aux = res.num[i];
			res.num[i]=carry;
			carry=aux;
		}
		res.tam++;
	}
	return res;
}

bool ispos(bignum* p){
	return p->tam>0;
}
bignum vet, pd[20][2][2];

bignum solve(bignum* vet, int n, int lastisone, int ismax){
	if (vet->tam==n) return convert(1);
	if (ispos(&pd[n][lastisone][ismax])) return pd[n][lastisone][ismax];
	bignum res=convert(0);
	int cont = 0;
	for(int i=0; i<=(ismax==1?vet->num[n]-1:9); i++){
		if(!(i==4 || i==1 || (lastisone && i==3))) cont++;
	}
	if(!ismax){
		res=res+solve(vet, n+1, 1, 0);
	}
	else{
		if(vet->num[n]!=4 && !(lastisone && vet->num[n]==3)) res=res+solve(vet, n+1, vet->num[n]==1, 1);
		if(vet->num[n]>1) res=res+solve(vet, n+1, 1, 0);
	}
	if(cont>0) res=res + (cont*solve(vet, n+1, 0, 0));
	pd[n][lastisone][ismax]=res;
	return res;
}
bool isvalid(bignum* n){
	for(int i=0; i<n->tam; i++){
		if(n->num[i]==4) return false;
	}
	for(int i=0; i<n->tam-1; i++){
		if(n->num[i]==1 && n->num[i+1]==3) return false;
	}
	return true;
}

ull chinese_to_normal(bignum n){
	for(int i=0; i<n.tam; i++){
		pd[i][0][0]=pd[i][1][0]=pd[i][0][1]=pd[i][1][1]=convert(0);
	}
	n = solve(&n, 0, 0, 1);
	return convert_to_normal(&n)-1;
}

int main(){
	ull N, razao;
	bignum x, aux;
	while(scanf("%llu", &N)!=EOF){
		razao = 4*N;
		x = convert(1);
		while(chinese_to_normal(x)!=N){
			while(chinese_to_normal(x + convert(razao))>N) razao/=2;
			x=x+convert(razao);
			//printf("x = %llu, razao = %llu, convert = %llu\n", convert_to_normal(&x), razao, chinese_to_normal(x));
			if(razao==0) break;
		}
		while(!isvalid(&x)){
			razao = convert_to_normal(&x);
			razao--;
			x = convert(razao);
		}
		printf("%llu\n", convert_to_normal(&x));
	}
	return 0;
}