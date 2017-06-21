#include <cstdio>

long long int res[11][2100];
int H, W;

class Binary{
public:
	Binary(){
		for (int i = 0; i < W; ++i) digits[i]=false;
	}
	Binary(int n){
		for (int i = 0; i < W; ++i) digits[i]=false;
		int j=0;
		while(n>0){
			digits[j++]=(n%2!=0);
			n/=2;
		}
	}
	bool intersect(bool* vet){
		for (int i = 0; i < W; ++i)
		{
			if (digits[i] && vet[i]) return true;
			if (!digits[i] && !vet[i]){
				if (i+1<W && !digits[i+1] && !vet[i+1]) i++;
				else return true;
			}
		}
		return false;
	}
	void addOne(){
		bool carry=true;
		for (int i = 0; i < W; ++i)
		{
			if (!carry) return;
			carry=digits[i];
			digits[i]=!digits[i];
		}
	}
	bool digits[11];
};

bool verifyEnd(int num){
	Binary bin = Binary(num);
	for (int i = 0; i < W; ++i)
	{
		if (!bin.digits[i]){
			if (i+1<W && !bin.digits[i+1])
				bin.digits[i+1]=true;
			else return false;
		}
	}
	return true;
}

int pow2(int n){
	if (n==0) return 1;
	int k = pow2(n/2);
	k = k*k;
	if (n%2!=0) k*=2;
	return k;
}

long long int calculate(int column, int num){
	if (res[column][num]>=0) return res[column][num];
	if (column==H-1){
		if (verifyEnd(num)) res[column][num]=1;
		else res[column][num]=0;
		return res[column][num];
	}
	Binary in = Binary(num);
	Binary out = Binary();
	long long int sum=0;
	for (int n = 0; n < pow2(W); ++n, out.addOne())
	{
		if (in.intersect(out.digits)) continue;
		sum+=calculate(column+1, n);
	}
	res[column][num]=sum;
	return sum;
}

int main()
{
	while(true){
		scanf("%d %d", &H, &W);
		if (H==0 && W==0) break;
		for (int i = 0; i < H; ++i){
			for (int j = 0; j < pow2(W); ++j){
				res[i][j]=-1;
			}
		}
		printf("%lld\n", calculate(0,0));
	}
	return 0;
}