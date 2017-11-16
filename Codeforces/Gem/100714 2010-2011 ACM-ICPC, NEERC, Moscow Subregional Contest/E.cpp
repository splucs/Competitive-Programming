#include <bits/stdc++.h>
using namespace std;
#define MAXN 101009
#define MAXM 1009
#define INF (1<<30)

typedef long long ll;

class FenwickTree {
private:
	vector<ll> ft1, ft2;
	ll rsq(vector<ll> & ft, int i) {
		ll sum = 0;
		while(i > 0){
			sum += ft[i];
			i -= (i & -i);
		}
		return sum;
	}
	void update(vector<ll> & ft, int i, ll v) {
		while(i < (int)ft.size()) {
			ft[i] += v;
			i += (i & -i);
		}
	}
public:
	FenwickTree() {
		ft1.assign(MAXM, 0);	//1-indexed
		ft2.assign(MAXM, 0);	//1-indexed
	}
	void update(int i, int j, ll v){
		i++;
		j++;
		if (i > j) return;
		update(ft1, i, v);
		update(ft1, j+1, -v);
		update(ft2, i, v*(i-1));
		update(ft2, j+1, -v*j);
	}
	ll rsq(int i){
		i++;
		return rsq(ft1, i)*i - rsq(ft2, i);
	}
	ll rsq(int i, int j){
		return rsq(j) - rsq(i-1);
	}
};

void test(int sl, int sr, int B, int N) {
	printf("sl=%d, sr=%d, B=%d, N=%d\n", sl, sr, B, N);
	for(int dx=0; dx<B; dx++) {
		int ans = 0;
		for(int j=dx, i; (i=j-B+1)<N; j+=B){
			if (i>sr || j<sl) continue;
			ans++;
		}
		printf("[%d]=%d ", dx, ans);
	}
	printf("\n");
}

int dceil(int a, int b) {
	if(a%b == 0) return a/b;
	else return a/b+1;
}

int l[MAXN], r[MAXN], sl[MAXN], sr[MAXN];
FenwickTree ft[MAXM];

int main(){
	multiset<int> s;
	int N, M, A, B;
	
	//read entry
	scanf("%d %d %d %d", &M, &N, &A, &B);
	for(int i=0; i<M; i++) {
		scanf("%d %d", &l[i], &r[i]);
		l[i]--; r[i]--;
	}

	//compute sl
	for(int i=0; i<M+A-1; i++){
		if (i>=A) s.erase(s.find(l[i-A]));
		if (i<M) s.insert(l[i]);
		if (!s.empty()) sl[i] = *s.begin();
	}
	s.clear();
	
	//compute sr
	for(int i=0; i<M+A-1; i++){
		if (i>=A) s.erase(s.find(r[i-A]));
		if (i<M) s.insert(r[i]);
		if (!s.empty()) sr[i] = *s.rbegin();
	}
	s.clear();
	
	//update fenwick trees
	for(int dy=0; dy<A; dy++) {
		printf("dy=%d\n", dy);
		for(int j=dy, i; (i=j-A+1) < M; j+=A){
			int pr = (sl[j]-1+B)%B, pl = (sr[j])%B;
			printf("j=%d, sl=%d, sr=%d, pl=%d, pr=%d\n", j, sl[j], sr[j], pl, pr);
			test(sl[i], sr[i], B, N);
			ft[dy].update(0, B-1, dceil(sr[i]-sl[i]+1, B));
			if (pr >= pl) {
				ft[dy].update(pl, pr, 1);
				printf("med = %d, (%d,%d)+=1\n\n", dceil(sr[i]-sl[i]+1, B), pl, pr);
			}
			else {
				ft[dy].update(0, pr-1, 1);
				ft[dy].update(pl+1, B-1, 1);
				printf("med = %d, (%d,%d)+=1 (%d,%d)+=1\n\n", dceil(sr[i]-sl[i]+1, B), 0, pr-1, pl+1, B-1);
			}
			
		}
	}
	
	//get ans
	ll ans = INF;
	for(int dy=0; dy<A; dy++) {
		for(int dx=0; dx<B; dx++) {
			ans = min(ans, ft[dy].rsq(dx, dx));
			//printf("ft[%d][%d]=%d ", dy, dx, ft[dy].rsq(dx, dx));
		}
		//printf("\n");
	}
	printf("%I64d\n", ans);
	return 0;
}