#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

typedef long long ll;
typedef pair<ll, int> ii;

int main() {
	freopen("input.txt", "r", stdin);
	freopen("output.txt", "w", stdout);
	
	int n;
	scanf("%d", &n);
	ll ans = 0, v;
	char type;
	set<ii> dkilled;
	for(int i=2; i<n; i++){
		scanf(" %c %I64d", &type, &v);
		if (type == 'p') {
			while((ll)dkilled.size() >= v) {
				ans -= dkilled.begin()->first;
				dkilled.erase(dkilled.begin());
			}
		}
		else {
			ans += v;
			dkilled.insert(ii(v, i));
		}
	}
	scanf(" %c %I64d", &type, &v);
	if ((ll)dkilled.size() < v){
		printf("-1\n");
		return 0;
	}
	else{
		printf("%I64d\n%u\n", ans, dkilled.size());
		vector<int> index;
		while(!dkilled.empty()) {
			index.push_back(dkilled.begin()->second);
			dkilled.erase(dkilled.begin());
		}
		sort(index.begin(), index.end());
		for(int i=0; i<(int)index.size(); i++) {
			printf("%d ", index[i]);
		}
		printf("\n");
	}
	
	fclose(stdin);
	fclose(stdout);
	return 0;
}