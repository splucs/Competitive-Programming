#include <bits/stdc++.h>
using namespace std;
#define MAXN 100009

int N;
typedef long long ll;
ll ans = 0, M, K;
typedef pair<int, ll> ii;
vector<ii> arr;

int main() {
	scanf("%d %I64d %I64d", &N, &K, &M);
	for(int i=0, a; i<N; i++) {
		scanf("%d", &a);
		if (arr.empty() || arr.back().first != a) {
			arr.push_back(ii(a, 1));
		}
		else arr.back().second++;
		while(!arr.empty() && arr.back().second >= K) {
			arr.back().second -= K;
			ans += M;
			if (arr.back().second == 0) arr.pop_back();
		}
	}
	int i = 0, j = arr.size()-1;
	vector<ii> cpy = arr;
	while(i<j && arr[i].first == arr[j].first && arr[i].second + arr[j].second >= K) {
		while (arr[i].second + arr[j].second >= K) {
			ll d = min(arr[i].second, K);
			arr[i].second -= d;
			arr[j].second -= K-d;
			ans += M-1;
		}
		if (arr[i].second == 0) i++;
		if (arr[j].second == 0) j--;
	}
	if (i == j) {
		ans += (M*arr[i].second)/K;
		if ((M*arr[i].second)%K == 0) {
			arr.clear();
			for(int it=0; it<(int)cpy.size(); it++) {
				if (it != i) arr.push_back(cpy[it]);
			}
			cpy.clear();
			cpy.swap(arr);
			for(int i=0; i<(int)cpy.size(); i++) {
				if (arr.empty() || arr.back().first != cpy[i].first) {
					arr.push_back(cpy[i]);
				}
				else arr.back().second+=cpy[i].second;
				while(!arr.empty() && arr.back().second >= K) {
					arr.back().second -= K;
					ans++;
					if (arr.back().second == 0) arr.pop_back();
				}
			}
		}
	}
	printf("%I64d\n", N*M - ans*K);
	return 0;
}