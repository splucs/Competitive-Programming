#include <cstdio>
#include <cstring>
#include <vector>
#include <algorithm>
using namespace std;

int commomArea[10];
int n, m, t, k, aux;

struct tower{
	vector<int> areas;
	int value;
} towers[20];

struct choice{
	int value;
	vector<int> towersChosen;
	choice() { value = 0; }
	choice(int v) { value = v; }
	bool operator < (const choice & other){
		if (value != other.value) return value < other.value;
		for(int i=0; i<k; i++){
			if (towersChosen[i] != other.towersChosen[i])
				return towersChosen[i] > other.towersChosen[i];	
		}
		return false;
	}
} current, temp;

void calculateValue(choice & c){
	int areasPresent[10];
	memset(&areasPresent, 0, sizeof areasPresent);
	int curTower;
	c.value = 0;
	for(int i=0; i<(int)c.towersChosen.size(); i++){
		curTower = c.towersChosen[i];
		c.value += towers[curTower].value;
		for(int j=0; j<(int)towers[curTower].areas.size(); j++){
			areasPresent[towers[curTower].areas[j]]++;
		}
	}
	for(int i=0; i<10; i++){
		if (areasPresent[i]>1) c.value -= (areasPresent[i]-1)*commomArea[i];
	}
}

choice iterate(int pos, int left){
	if (left==0){
		calculateValue(current);
		return current;
	}

	choice ans(0);

	for(int i=pos; i<n-left+1; i++){
		current.towersChosen.push_back(i);
		temp = iterate(i+1, left-1);
		current.towersChosen.pop_back();
		if (ans < temp) ans = temp;
	}

	return ans;
}

int main(){
	int tower[20], caseNo=1;
	choice ans;
	while(scanf("%d %d", &n, &k), (n||k)){
		for(int i=0; i<n; i++){
			scanf("%d", &towers[i].value);
			towers[i].areas.clear();
		}
		scanf("%d", &m);
		for(int i=0; i<m; i++){
			scanf("%d", &t);
			for(int j=0; j<t; j++){
				scanf("%d", &aux);
				aux--;
				towers[aux].areas.push_back(i);
			}
			scanf("%d", commomArea + i);
		}
		current.towersChosen.clear();
		ans = iterate(0, k);
		printf("Case Number  %d\nNumber of Customers: %d\nLocations recommended:", caseNo++, ans.value);
		for(int i=0; i<k; i++) printf(" %d", ans.towersChosen[i]+1);
		printf("\n\n");
	}
	return 0;
}