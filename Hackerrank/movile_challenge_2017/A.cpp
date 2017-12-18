#include <bits/stdc++.h>
using namespace std;
#define MAXN 10009

typedef pair<int, int> ii;

int main() {
	int N;
	scanf("%d", &N);
	for(int m = 0; m < N; m++) {
		vector<ii> arr;
		int money, events, ticket;
		scanf("%d %d", &money, &events);
		for(int j=1; j<=events; j++) {
			scanf("%d", &ticket);
			arr.push_back(ii(ticket, j));
		}
		sort(arr.begin(), arr.end());
		for(int i = 0, j = events-1; i < events; i++) {
			while(j > 0 && arr[i].first + arr[j].first > money) j--;
			if (arr[i].first + arr[j].first == money) {
				i = arr[i].second;
				j = arr[j].second;
				if (i > j) swap(i, j);
				printf("%d %d\n", i, j);
				break;
			}
		}
	}
	return 0;
}