#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int end[MAXN], begin[MAXN], lis[MAXN], arr[MAXN], n;
vector<int> M[MAXN];

int LIS(){
	int L=1, l, h, m;
	M[1].push_back(0);
	lis[0] = 1;
	end[0] = begin[0] = -1;
	for(int i=1; i<n; i++){
		if (arr[i]<=arr[M[1].back()]){
			M[1].push_back(i);
			lis[i] = 1;
			end[0] = begin[0] = -1;
			continue;
		}
		l = 1; h = L+1;
		while(h>l+1){
			m = (l+h)/2;
			if (arr[M[m].back()]<arr[i]) l = m;
			else h = m;
		}
		if (h>L) L=h;
		begin[i] = M[h].empty() ? 0 : begin[M[h].back()];
		while(arr[M[h-1][begin[i]]] >=  arr[i]) begin[i]++;
		M[h].push_back(i);
		lis[i] = h;
		end[i] = M[h-1].size();
	}
	return L;
}

typedef pair<int, int> ii;
typedef pair<int, ii> iii;
iii p[MAXN];
int ma[MAXN], mi[MAXN];

int main(){
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	scanf("%d", &n);
	for(int i=0; i<n; i++) {
		scanf("%d %d", &p[i].first, &p[i].second.first);
		p[i].second.first*=-1;
		p[i].second.second = i;
	}
	sort(p, p+n);
	for(int i=0; i<n; i++){
		arr[i] = -p[i].second.first;
		//printf("arr[%d] = %d\n", i, arr[i]);
		ma[i+1] = 0;
		mi[i+1] = MAXN;
	}
	int L = LIS();
	/*for(int l=1; l<=L; l++) {
		printf("l=%d:", l);
		for(int i=0; i<(int)M[l].size(); i++){
			int j = M[l][i];
			printf(" %d(%d-%d)", j, begin[j], end[j]);
		}
		printf("\n");
	}*/
	set<int> vis, ex;
	ma[L] = M[L].size();
	mi[L] = 0;
	for(int l=L, j; l>0; l--){
		j = M[l][mi[l]];
		if (ma[l] - mi[l] == 1) ex.insert(p[j].second.second+1);
		//printf("mi[%d]=%d ma[%d]=%d\n", l, mi[l], l, ma[l]);
		for(int i=mi[l]; i<ma[l]; i++){
			j = M[l][i];
			vis.insert(p[j].second.second+1);
			ma[l-1] = max(ma[l-1], end[j]);
			mi[l-1] = min(mi[l-1], begin[j]);
		}
	}
	printf("%u", vis.size());
	for(set<int>::iterator it = vis.begin(); it!=vis.end(); it++){
		printf(" %d", *it);
	}
	printf("\n");
	printf("%u", ex.size());
	for(set<int>::iterator it = ex.begin(); it!=ex.end(); it++){
		printf(" %d", *it);
	}
	printf("\n");
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}