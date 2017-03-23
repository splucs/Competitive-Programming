#include <cstdio>
#include <cmath>
#define MAXN 100009
#define MAXLOGN 20

//comparison function, can reclace with min, max, gcd
int comp (int a, int b){
	return min(a,b);
}

class SparseTable{
private:
	int SpT[MAXN][MAXLOGN];
	int size;
public:
	SparseTable(int* begin, int* end) {
		size = end - begin;
		for(int i=0; i<size; i++){
			SpT[i][0] = begin[i];
		}
		for(int j = 1; 1 << j <= size; j++){
			for(int i=0; i + (1<<j) <= size; i++){
				SpT[i][j] = comp(SpT[i][j-1], SpT[i+(1<<(j-1))][j-1]);
			}
		}
	}
	int query(int l, int r){
		int k = (int)floor(log((double)r-l+1) / log(2.0)); // 2^k <= (j-i+1)
		return comp(SpT[l][k], SpT[r-(1<<k)+1][k]);
	}
};