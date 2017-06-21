#include <bits/stdc++.h>
#define INF 1e+30
#define MAXN 200009
#define EPS 1e-15
using namespace std;

int maxi;

typedef long long ll;

class CHTrick {
private:
	vector<int> vl, vr;
	vector<double> p;
	vector<int> ids;
public:
	CHTrick() {}
	double inter(int l1, int r1, int l2, int r2) {
		return (r1*1.0*(l2-r2) - r2*1.0*(l1-r1))/(r1-l1+l2-r2);
	}
	void push(int l, int r, int id) {
		while (!p.empty() && p.back() >= inter(l, r, vl.back(), vr.back())) {
			vl.pop_back(); vr.pop_back(); p.pop_back(); ids.pop_back();
		}
		//if(!n.empty() && fabs(nm - m.back())<EPS && nn <= n.back()) return;
		p.push_back(p.empty() ? -INF : inter(l, r,
			vl.back(), vr.back()));
		vl.push_back(l); vr.push_back(r); ids.push_back(id);
		//printf("line %d pushed\n", id);
	}
	int query(double dx) {
		if (p.empty()) return maxi;
		int high = p.size() - 1, low = 0, mid;
		if (dx > p[high]) return ids[high];
		while (high > low + 1) {
			mid = (high + low) / 2;
			if (dx < p[mid]) high = mid;
			else low = mid;
		}
		return ids[low];
	}
	void debug(){
		for(int i=0; i<(int)p.size(); i++){
			printf("from %.3f on, %d\n", p[i], ids[i]);
		}
	}
};

struct line{
	int l, r;
	int id;
	bool operator < (line o){
		if (o.r-o.l == r-l) return r < o.r;
		else return o.l-o.r < l-r;
	}
};
int l[MAXN], r[MAXN];

int main(){
	vector<line> lines;
	int N;
	scanf("%d", &N);
	maxi = 1;
	line nl;
	for(int i=1; i<=N; i++){
		scanf("%d %d", &l[i], &r[i]);
		if (r[i] < l[i]) swap(l[i], r[i]);
		if (l[i] > l[maxi]) maxi = i;
		if (l[i] != r[i]){
			nl.l = l[i];
			nl.r = r[i];
			nl.id = i;
			lines.push_back(nl);
		}
	}
	CHTrick cht;
	sort(lines.begin(), lines.end());
	for(int i=0; i<(int)lines.size(); i++) {
		//printf("line %d\n", lines[i].id);
		if (i+1 < (int)lines.size() && lines[i].l-lines[i].r == lines[i+1].l-lines[i+1].r) continue;
		cht.push(lines[i].l, lines[i].r, lines[i].id);
	}
	//cht.debug();
	int M, hp;
	scanf("%d", &M);
	for(int i=0; i<M; i++){
		scanf("%d", &hp);
		if (hp <= l[maxi]) printf("%d ", maxi);
		else{
			printf("%d ", cht.query(hp));
		}
	}
	printf("\n");
	return 0;
}