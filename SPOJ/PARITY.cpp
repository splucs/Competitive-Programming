#include <bits/stdc++.h>
using namespace std;
#define MAXN 69

typedef unsigned long long ll;
map<ll, pair<int, ll> > half;
int N, K, M;
ll arr[MAXN], bits;
char buffer[MAXN];

int main() {
	
	scanf("%d %d", &N, &K);
	bits = 0;
	for(int i=0, b; i<N; i++) {
		scanf(" %s %d", buffer, &b);
		if (b == 1) bits |= (1ULL << i);
		M = strlen(buffer);
		reverse(buffer, buffer+M);
		arr[i] = 0;
		for(int j=0; j<M; j++) {
			if (buffer[j] == '1') arr[i] |= (1ULL << j);
		}
	}
	
	int M2 = M>>1;
	for(ll mask=0; mask<(1ULL<<M2); mask++) {
		ll cur = 0;
		for(int i=0; i<N; i++) {
			if (__builtin_parityll(arr[i] & mask)) cur |= (1ULL << i);
		}
		int cnt = __builtin_popcountll(mask);
		if (half.count(cur)) {
			half[cur] = min(half[cur], make_pair(cnt, mask));
		}
		else half[cur] = make_pair(cnt, mask);
	}
	
	bool found = false;
	ll ans;
	int anscnt;
	for(ll mask=(1ULL<<M2); mask<(1ULL<<M) && !found; mask+=(1ULL<<M2)) {
		ll cur = 0;
		for(int i=0; i<N; i++) {
			if (__builtin_parityll(arr[i] & mask)) cur |= (1ULL << i);
		}
		int cnt = __builtin_popcountll(mask);
		if (half.count(bits^cur)) {
			int cnt2 = half[bits^cur].first;
			ll mask2 = half[bits^cur].second;
			if (cnt + cnt2 <= K) {
				found = true;
				anscnt = cnt + cnt2;
				ans = mask | mask2;
			}
		}
	}
	
	if (!found) printf("-1\n");
	else {
		printf("%d\n", anscnt);
		for(int j=0; j<M; j++) {
			if (ans & (1ULL<<j)) printf("%d ", j);
		}
		printf("\n");
	}
	
	return 0;
}