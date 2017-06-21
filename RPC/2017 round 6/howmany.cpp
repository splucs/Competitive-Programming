#include <bits/stdc++.h>
using namespace std;
#define MAXN 1000009

const int neutral = 0;
int comp(int a, int b){
	return a+b;
}

class FenwickTree {
private:
	vector<int> ft;
public:
	FenwickTree(int n) {
		ft.assign(n + 1, 0);	//1-indexed
	}
	int rsq(int i) { // returns RSQ(1, i)
	    i++;
		int sum = neutral;
		while(i > 0){
			sum = comp(sum, ft[i]);
			i -= (i & -i);
		}
		return sum;
	}
	int rsq(int i, int j){
		return rsq(j) - rsq(i - 1);
	}
	void update(int i, int v) {
	    i++;
		while(i < (int)ft.size()) {
			ft[i] = comp(v, ft[i]);
			i += (i & -i);
		}
	}
};

typedef long long ll;

FenwickTree ft(1);

int vet[MAXN], id[MAXN];

bool compid(int i, int j){
    if (vet[i] == vet[j]) return i > j;
    else return vet[i] < vet[j];
}

int main(){
    int N;
    while(true) {
        scanf("%d", &N);
        if (N==0) break;
        for(int i=0; i<N; i++){
            scanf("%d", &vet[i]);
            id[i] = i;
        }
        sort(id, id+N, compid);
        ll ans = 0;
        ft = FenwickTree(N);
        for(int i=0; i<N; i++){
            int j = id[i];
            ans += ft.rsq(j+1, N-1);
            ft.update(j, 1);
        }
        printf("%lld\n", ans);
    }
    return 0;
}
