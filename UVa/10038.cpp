#include <cstdio>
#include <cstring>
#define foreach(x, y) for(int x=0; x<y; x++)

int abs(int x){
	if (x>0) return x;
	else return -x;
}

int main(){
	int n, vet[3009];
	bool appeared[3009], jolly;
	while(scanf(" %d", &n)!=EOF){
		jolly=true;
		memset(appeared, false, sizeof appeared);
		foreach(i, n){
			scanf(" %d", vet+i);
		}
		foreach(i, n-1){
			if (abs(vet[i]-vet[i+1])<n) appeared[abs(vet[i]-vet[i+1])]=true;
		}
		for(int i=1; i<n && jolly; i++){
			if (!appeared[i]) jolly=false;
		}
		if (jolly) printf("Jolly\n");
		else printf("Not jolly\n");
	}
	return 0;
}