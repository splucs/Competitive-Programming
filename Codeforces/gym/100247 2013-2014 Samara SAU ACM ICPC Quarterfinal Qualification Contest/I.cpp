#include <bits/stdc++.h>
using namespace std;
#define MAXN 200009

typedef long long int ll;

ll t[MAXN], d[MAXN];
int n;

int main()
{
	scanf("%d", &n);
	for(int i=1; i<=n; i++){
		scanf("%I64d %I64d", &t[i], &d[i]);
	}
	ll hp = 0;
	int ans = 0;
	priority_queue<ll> past;
	t[0] = 0;
	for(int i=1; i<=n; i++){
		hp += t[i] - t[i-1];
		past.push(d[i]);
		hp -= d[i];
		while (hp < 0){
			hp += past.top();
			past.pop();
			ans++;
		}
	}
	printf("%d\n", ans);
	return 0;
}