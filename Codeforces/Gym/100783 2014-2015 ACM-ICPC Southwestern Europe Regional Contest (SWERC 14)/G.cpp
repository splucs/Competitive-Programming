#include <bits/stdc++.h>
using namespace std;
#define MAXN 1009
#define MAXM 3309

typedef pair<int, int> ii;

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
		int sum = 0;
		while(i > 0){
			sum = comp(sum, ft[i]);
			i -= (i & -i);
		}
		return sum;
	}
	void update(int i, int v) {
		while(i < (int)ft.size()) {
			ft[i] = comp(v, ft[i]);
			i += (i & -i);
		}
	}
	int rsq(int i, int j){
		if (j < i) swap(i, j);
		return rsq(j) - rsq(i-1);
	}
};

ii pol1[MAXN], pol2[MAXN];
int N1, N2;

bool analyse(){
	//printf("analysing...\n");
	FenwickTree hor1(MAXM), hor2(MAXM), ver1(MAXM), ver2(MAXM);
	int vet1[MAXN], vet2[MAXN];
	vet1[0] = vet2[0] = 0;
	for(int i=0; i<N1-1; i++){
		ver1.update(pol1[i].first, 1);
		hor1.update(pol1[i].second, 1);
	}
	for(int i=0; i<N2-1; i++){
		ver2.update(pol2[i].first, 1);
		hor2.update(pol2[i].second, 1);
	}
	for(int i=1; i<N1; i++){
		if (pol1[i].first == pol1[i-1].first){
			vet1[i] = hor1.rsq(pol1[i].second, pol1[i-1].second);
		}
		else{
			vet1[i] = ver1.rsq(pol1[i].first, pol1[i-1].first);
		}
	}
	for(int i=1; i<N2; i++){
		if (pol2[i].first == pol2[i-1].first){
			vet2[i] = hor2.rsq(pol2[i].second, pol2[i-1].second);
		}
		else{
			vet2[i] = ver2.rsq(pol2[i].first, pol2[i-1].first);
		}
	}
	if (N1 != N2) return false;
	for(int i=0; i<N1; i++){
		//printf("vet1[%d] = %d, vet2[%d] = %d\n", i, vet1[i]/2, i, vet2[i]/2);
		if (vet1[i] != vet2[i]) return false;
	}
	return true;
}

void rotatepol2(){
	//printf("rotating...\n");
	int maxM = 3100, x, y;
	for(int i=0; i<N2; i++){
		x = pol2[i].first;
		y = pol2[i].second;
		pol2[i] = ii(maxM-y, x);
		//printf("(%d,%d)\n", pol2[i].first, pol2[i].second);
	}
	N2--;
	int l = 0;
	for(int i=1; i<N2; i++){
		if (pol2[i].second < pol2[l].second || (pol2[i].second == pol2[l].second && pol2[i].first < pol2[l].first)) l = i;
	}
	for(int i = 0; i<l; i++){
		pol2[i+N2] = pol2[i];
	}
	for(int i=0; i<N2; i++){
		pol2[i] = pol2[i+l];
	}
	pol2[N2++] = pol2[0];
}

int getBottomLeft()
{
	
}

int main()
{
	scanf("%d", &N1);
	for(int i=0; i<N1; i++){
		scanf("%d %d", &pol1[i].first, &pol1[i].second);
		pol1[i].first++, pol1[i].second++;
	}
	pol1[N1++] = pol1[0];
	scanf("%d", &N2);
	for(int i=0; i<N2; i++){
		scanf("%d %d", &pol2[i].first, &pol2[i].second);
		pol2[i].first++, pol2[i].second++;
	}
	//printf("in read\n");
	pol2[N2++] = pol2[0];
	bool possible = false;
	for(int i=0; i<4 && !possible; i++){
		rotatepol2();
		if (analyse()) possible = true;
	}
	if (possible) printf("yes\n");
	else printf("no\n");
	return 0;
}