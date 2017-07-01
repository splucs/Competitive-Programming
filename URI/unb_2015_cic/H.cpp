#include <bits/stdc++.h>
using namespace std;

pair<int, string> arr[20];

int main() {
	int N;
	while(scanf(" %d ", &N) != EOF) {
		for(int i=0; i<N; i++){
			cin >> arr[i].second >> arr[i].first;
		}
		sort(arr, arr+N);
		for(int i=0; i<N; i++){
			if (i > 0) printf(" ");
			printf("%s", arr[i].second.c_str());
		}
		printf("\n");
	}
	return 0;
}