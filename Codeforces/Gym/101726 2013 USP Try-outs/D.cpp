#include <bits/stdc++.h>
#define pb push_back
#define FOR(x,n) for(int x=0;x<n;x++)
#define FOR1e(x,n) for(int x=1; x<=n; x++)
#define all(x) x.begin(), x.end()
using namespace std;
typedef long long ll;
typedef pair<int,int> ii;

char ha[2][5], hb[2][5], desk[5][5];

int getValue(char c) {
	if (c == 'A') return 13;
	if (c == 'K') return 12;
	if (c == 'Q') return 11;
	if (c == 'J') return 10;
	if (c == 'T') return 9;
	return (int)c-'1';
}

int straight(vector<ii> &hand) {
	bool ok = true;
	FOR1e(i, 4) {
		if (hand[i].first != hand[i-1].first + 1) ok = false;
	}
	if (ok) return hand[4].first;

	if (hand[4].first != 13 || hand[0].first != 1) return -1;

	ok = true;
	FOR1e(i, 3) {
		if (hand[i].first != hand[i-1].first + 1) ok = false;
	}

	if (ok) return hand[3].first;
	return -1;
}

int highest(vector<ii> &hand) {
	int fac = 1, ans = 0;
	FOR(i, 5) {
		ans += hand[i].first * fac;
		fac *= 15;
	}
	return ans;
}
int flush(vector<ii> &hand) {
	FOR(i, 5) {
		if (hand[i].second != hand[0].second) return -1;
	}
	return highest(hand);	
}

int four(vector<ii> &hand) {
	int cnt = 0;
	FOR(i, 5) {
		if (hand[i].first == hand[2].first) cnt++;
	}
	if (cnt >= 4) {
		if (hand[0].first != hand[2].first) return hand[2].first*15 + hand[0].first;
		else return hand[2].first*15 + hand[4].first;
	}
	return -1;
}

int fullhouse(vector<ii>& hand) {
	FOR(i, 3) {
		bool ok = true;
		FOR(j, 3) {
			if (hand[(j+i)%5].first != hand[i].first) ok = false;
		}
		if (hand[(i+3)%5].first != hand[(i+4)%5].first) ok = false;
		
		if (ok) return hand[i].first*15 + hand[(i+3)%5].first;
	}
	return -1;
}

int three(vector<ii>& hand) {
	FOR(i, 3) {
		bool ok = true;
		FOR(j, 3) {
			if (hand[(j+i)%5].first != hand[i].first) ok = false;
		}
		
		if (ok) {
			int a = max(hand[(i+3)%5].first, hand[(i+4)%5].first);
			int b = min(hand[(i+3)%5].first, hand[(i+4)%5].first);
			return hand[i].first*15*15 + a*15 + b;
		}
	}
	return -1;
}

int twopairs(vector<ii>& hand) {
	int sum = 0;
	FOR(i, 5) sum += hand[i].first;

	FOR(i, 2) {

		for (int j = i+2; j < 4; j++) {
			if (hand[i].first != hand[i+1].first) continue;
			if (hand[j].first != hand[j+1].first) continue;
			
			int a = max(hand[i].first, hand[j].first);
			int b = min(hand[i].first, hand[j].first);
			int rem = sum - 2*a - 2*b;
			return a*15*15 + b*15 + rem;
		}
	}
	return -1;
}

int onepair(vector<ii>& hand) {
	FOR(i, 5) {
		bool ok = true;
		FOR(j, 2) {
			if (hand[(j+i)%5].first != hand[i].first) ok = false;
		}
		
		if (ok) {
			vector<int> tmp;
			tmp.pb(hand[(i+2)%5].first);
			tmp.pb(hand[(i+3)%5].first);
			tmp.pb(hand[(i+4)%5].first);

			sort(all(tmp));
			return hand[i].first*15*15*15 + tmp[2]*15*15 + tmp[1]*15 + tmp[0];
		}
	}
	return -1;
}

ii memo[1000009];

ii getBest(vector<ii>& hand) {

//	if (f != -1 && s != -1) { return ii(9, s); }

	int fo = four(hand);
	if (fo != -1) { return ii(8, fo); }

	int fh = fullhouse(hand);
	if (fh != -1) { return ii(7, fh); }

//	if (f != -1) { return ii(6, f); }
	int s = straight(hand);
	if (s != -1) { return ii(5, s); }

	int tok = three(hand);
	if (tok != -1) { return ii(4, tok); }

	int tp = twopairs(hand);
	if (tp != -1) { return ii(3, tp); }

	int op = onepair(hand);
	if (op != -1) { return ii(2, op); }

	return ii(1, highest(hand));
}

ii getScore(vector<ii>& hand) {
	sort(all(hand));

	int hash = 0;
	FOR(i, 5) { hash = hand[i].first + 14*hash; }
	
	if (memo[hash] == ii(0,0)) {
		memo[hash] = getBest(hand);
	}

	int f = flush(hand);
	if (f == -1) return memo[hash];

	else {
		int s = straight(hand);
		if (s != -1) return ii(9, s);
		else if (memo[hash].first > 6) return memo[hash];
		return ii(6, f);
	}
}

int main() {
	int t;
	scanf("%d", &t);
	while (t--) {
		scanf("%s %s", ha[0], ha[1]);
		scanf("%s %s", hb[0], hb[1]);
		FOR(i, 5) scanf("%s", desk[i]);
		
		ii sa = ii(0,0), sb = ii(0,0);
		vector<int> vec, perm;
		vec.pb(0); vec.pb(0); vec.pb(1); vec.pb(1); vec.pb(1); vec.pb(1); vec.pb(1);
		perm = vec;
		do {
			vector<ii> hand;
			FOR(i, 2) if (perm[i]) hand.pb(ii(getValue(hb[i][0]), hb[i][1]));
			FOR(j, 5) if (perm[j + 2]) hand.pb(ii(getValue(desk[j][0]), desk[j][1]));

			sb = max(sb, getScore(hand));
		} while (next_permutation(perm.begin(), perm.end()));

		perm = vec;
		do {
			vector<ii> hand;
			FOR(i, 2) if (perm[i]) hand.pb(ii(getValue(ha[i][0]), ha[i][1]));
			FOR(j, 5) if (perm[j + 2]) hand.pb(ii(getValue(desk[j][0]), desk[j][1]));
			
			sa = max(sa, getScore(hand));
			if (sa > sb) break;
		} while (next_permutation(perm.begin(), perm.end()));
		
		if (sa == sb) printf("0\n");
		else if (sa > sb) printf("1\n");
		else printf("2\n");
	}
}