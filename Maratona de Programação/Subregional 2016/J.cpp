#include <cstdio>
#include <vector>
#include <algorithm>
#define INF (1<<30)
#define MAXN 100009
using namespace std;


struct ath{
	int id;
	int m1, n1;
	int m2, n2;
	double i1, j1, i2, j2;
} aths[MAXN];

bool compm1(ath a, ath b){
	if (a.m1 == b.m1) return a.n1 < b.n1;
	return a.m1 < b.m1;
}

bool compm2(ath a, ath b){
	if (a.m2 == b.m2) return a.n2 > b.n2;
	return a.m2 > b.m2;
}

class ConvexHullTrick{
	private:
		vector<int> m, n;
		vector<double> p;
		vector<int> ids;
		bool max;
	public:
		ConvexHullTrick(bool mx){ max = mx; }
		double inter(double nm, double nn, double lm, double ln){
			return (ln-nn)/(nm-lm);
		}
		void push(int i){
			int nm, nn;
			if (max){
				nm = aths[i].m1;
				nn = aths[i].n1;
				while(!p.empty() && ((nm == m.back() && nn >= n.back())
				|| p.back() >= inter(nm, nn, m.back(), n.back()))){
					m.pop_back();
					n.pop_back();
					p.pop_back();
					ids.pop_back();
				}
			}
			else{
				nm = aths[i].m2;
				nn = aths[i].n2;
				while(!p.empty() && ((nm == m.back() && nn <= n.back())
				|| p.back() >= inter(nm, nn, m.back(), n.back()))){
					m.pop_back();
					n.pop_back();
					p.pop_back();
					ids.pop_back();
				}
			}
			p.push_back(p.empty()? 0.0 : inter(nm, nn, m.back(), n.back()));
			m.push_back(nm);
			n.push_back(nn);
			ids.push_back(i);
		}
		void fill(){
			for(int i=0, id; i<(int)ids.size(); i++){
				id = ids[i];
				if (max){
					aths[id].i1 = p[i];
					aths[id].j1 = (i+1 == (int)ids.size()?
					INF : p[i+1]);
				}
				else{
					aths[id].i2 = p[i];
					aths[id].j2 = (i+1 == (int)ids.size()?
					INF : p[i+1]);
				}
			}
		}
		
};

int N;

void fill1(){
	sort(aths, aths+N, &compm1);
	ConvexHullTrick cht(true);
	//printf("fill1:\n");
	for(int i=0; i<N; i++){
		//printf(" %d", aths[i].id);
		aths[i].i1 = aths[i].j1 = -1.0;
		cht.push(i);
	}
	//printf("\n");
	cht.fill();
	for(int i=1; i<N; i++){
		if (aths[i].m1 == aths[i-1].m1 && aths[i].n1 == aths[i-1].n1)
			aths[i].i1 = aths[i].j1 = aths[i-1].i1 = aths[i-1].j1 = -1.0;
	}
}

void fill2(){
	sort(aths, aths+N, &compm2);
	ConvexHullTrick cht(false);
	//printf("fill2:\n");
	for(int i=0; i<N; i++){
	//	printf(" %d", aths[i].id);
		aths[i].i2 = aths[i].j2 = -1.0;
		cht.push(i);
	}
	//printf("\n");
	cht.fill();
	for(int i=1; i<N; i++){
		if (aths[i].m2 == aths[i-1].m2 && aths[i].n2 == aths[i-1].n2)
			aths[i].i2 = aths[i].j2 = aths[i-1].i2 = aths[i-1].j2 = -1.0;
	}
}

bool hasgold(int id){
	//printf("athlete id %d\n", id);
	//printf("max from %.2f to %.2f\n", aths[id].i1, aths[id].j1);
	//printf("min from %.2f to %.2f\n", aths[id].i2, aths[id].j2);
	double i = max(aths[id].i1, aths[id].i2);
	double j = min(aths[id].j1, aths[id].j2);
	return j>i;
}

int main(){
	scanf("%d", &N);
	for(int i=0; i<N; i++){
		scanf("%d %d %d %d", &aths[i].n1, &aths[i].m1, &aths[i].n2, &aths[i].m2);
		aths[i].id = i;
	}
	fill1();
	fill2();
	int ans = 0;
	for(int i=0; i<N; i++){
		if (hasgold(i)) ans++;
	}
	printf("%d\n", ans);
	return 0;
}
