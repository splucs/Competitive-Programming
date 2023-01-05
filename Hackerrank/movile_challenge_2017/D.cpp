#include <bits/stdc++.h>
using namespace std;
#define MAXN 50009

typedef pair<int, int> ii;

ii arr[MAXN];
int K, W, N;

int main() {
	scanf("%d %d %d", &K, &W, &N);
	for(int i = 0; i < N; i++) {
		scanf("%d", &arr[i].first);
	}
	for(int i = 0; i < N; i++) {
		scanf("%d", &arr[i].second);
	}
	sort(arr, arr+N);
	priority_queue<int> pq;
	int j = 0;
	while(K --> 0) {
		while(j < N && arr[j].first <= W) {
			pq.push(arr[j].second);
			j++;
		}
		if (pq.empty() || pq.top() <= 0) break;
		W += pq.top();
		pq.pop();
	}
	printf("%d\n", W);
	return 0;
}