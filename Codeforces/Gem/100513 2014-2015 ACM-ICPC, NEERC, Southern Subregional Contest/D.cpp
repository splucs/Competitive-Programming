#include <bits/stdc++.h>
using namespace std;

typedef long long ll;
typedef pair<ll, int> ii;
vector<ii> arr[2];
int N;
ll M;

int main() {
	scanf("%d %I64d", &N, &M);
	int vol, mins = 2*N, maxv = 0;
	ll cap, cursum, sum0 = 0;
	for(int i=0; i<N; i++) {
		scanf("%I64d %d", &cap, &vol);
		arr[vol].push_back(ii(cap, i));
		if (vol == 0) sum0 += cap;
	}
	sort(arr[0].begin(), arr[0].end());
	sort(arr[1].begin(), arr[1].end());
	int s0 = arr[0].size();
	int s1 = arr[1].size();
	cursum = sum0;
	for(int i=0, j = s1; i<=s0; cursum -= (i<s0?arr[0][i].first:0), i++) {
		while(cursum < M && j > 0) {
			j--;
			cursum += arr[1][j].first;
		}
		if (cursum >= M && s1-j + s0-i < mins) {
			mins = s1-j + s0-i;
			maxv = s1-j;
		}
		if (cursum >= M && s1-j + s0-i == mins && maxv < s1-j) {
			maxv = s1-j;
		}
	}
	cursum = sum0;
	printf("%d %d\n", mins, maxv);
	for(int i=0, j = s1; i<=s0; cursum -= (i<s0?arr[0][i].first:0), i++) {
		while(cursum < M && j > 0) {
			j--;
			cursum += arr[1][j].first;
		}
		if (cursum >= M && s1-j + s0-i == mins && s1-j == maxv) {
			for(; i<s0; i++) {
				printf("%d ", arr[0][i].second+1);
			}
			for(; j<s1; j++) {
				printf("%d ", arr[1][j].second+1);
			}
			printf("\n");
			break;
		}
	}
	return 0;
}