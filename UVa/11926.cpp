#include <cstdio>
#include <bitset>
using namespace std;
#define MAXN 1000009

int main(){
	int n, m, x, y, z;
	bitset<MAXN> bit;
	bool possible;
	while(scanf("%d %d", &n, &m), (n||m)){
		bit.reset();
		possible = true;
		for(int i=0; i<n; i++){
			scanf("%d %d", &x, &y);
			for(int j=x; j<y && possible; j++){
				if (bit[j]==1) possible = false;
				bit.set(j, 1);
			}
		}
		for(int i=0; i<m; i++){
			scanf("%d %d %d", &x, &y, &z);
			for(int j=0; possible && j*z + x <= 1000000; j++){
				for(int k = j*z + x; possible && k < j*z + y && k<=1000000; k++){
					if (bit[k]==1) possible = false;
					bit.set(k, 1);
				}
			}
		}
		if (possible) printf("NO CONFLICT\n");
		else printf("CONFLICT\n");
	}
	return 0;
}