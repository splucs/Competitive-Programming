#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

int gcd(int a, int b) {
	if (b == 0) return a;
	return gcd(b, a%b);
}

bool a_lower_than_b0(ll a, ll b, ll b0, ll b1) {
	return a*b1 < b*b0;
}

char ans[100005];

int main() {
	int t, a, b;
	ll c, x, x0, y, y0, b0, b1;
	
	scanf("%d", &t);
	while(t--) {
		scanf("%d%*c%d", &a, &b);
		int n = 0;
		
		x0 = 0; y0 = 1; x = 1; y = 0;
		b0 = 1; b1 = 1;
		while(a != b0 || b != b1) {
			if ((a_lower_than_b0(a, b, b0, b1) && n%2 == 0) || ((!a_lower_than_b0(a, b, b0, b1) && n%2 == 1))) {
				ans[n++] = 'L';
				
				c = x;
				x = x0;
				x0 = c+x;
				
				c = y;
				y = y0;
				y0 = c+y0;
			} else {
				ans[n++]= 'R';
				
				c = x;
				x = x0+c;
				x0 = c;
				
				c = y;
				y = c+y0;
				y0 = c;
			}
			
			c = gcd(x, x0);
			c = gcd(c, y);
			c = gcd(c, y0);
			if (c > 0) {
				x /= c;
				y /= c;
				x0 /= c;
				y0 /= c;
			}

			b0 = x + x0;
			b1 = y + y0;
						
			c = gcd(b0, b1);
			b1 /= c;
			b0 /= c;
		}
		ans[n] = '\0';
		printf("%s\n", ans);
	}
	
	return 0;
}