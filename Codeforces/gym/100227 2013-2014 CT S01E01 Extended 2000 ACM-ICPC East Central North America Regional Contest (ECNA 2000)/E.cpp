#include <bits/stdc++.h>
using namespace std;
#define black 1
#define white 2
#define pb push_back
typedef pair<int, int> ii;
typedef vector<pair<int, int> > vii;

int m[70][70];
ii p[40];

vii black_plays;
vii white_plays;
vii king_plays;

ii operator +(ii a, ii b) {
	ii ans = ii(a.first + b.first, a.second + b.second);
	return ans;
}

ii operator *(int k, ii b) {
	ii ans = ii(k*b.first, k*b.second);
	return ans;
}

int getcolor(ii pos) {
	if (pos.first < 1 || pos.first > 64 ||
		pos.second < 1 || pos.second > 64) return 0;
	
	return abs(m[pos.first][pos.second]);
}

int getenemy(ii pos) {
	if (getcolor(pos) == black) return white;
	if (getcolor(pos) == white) return black;
	return 0;
}

bool isblack(ii pos) {
	if (pos.first < 1 || pos.first > 64 ||
		pos.second < 1 || pos.second > 64) return false;
	
	return abs(m[pos.first][pos.second]) == black;
}

bool isempty(ii pos) {
	if (pos.first < 1 || pos.first > 64 ||
		pos.second < 1 || pos.second > 64) return false;
	return m[pos.first][pos.second] == 0;
}

bool iswhite(ii pos) {
	if (pos.first < 1 || pos.first > 64 ||
		pos.second < 1 || pos.second > 64) return false;
	return abs(m[pos.first][pos.second]) == white;
}

bool isking(ii pos) {
	if (pos.first < 1 || pos.first > 64 ||
		pos.second < 1 || pos.second > 64) return false;
	return m[pos.first][pos.second] < 0;
}


bool canEat(int color) {
	int shift = 1;
	for (int r = 1; r <= 8; r++) {
		for (int c = 1+shift; c <= 8; c += 2) {
			ii pos = ii(r, c);
			if (getcolor(pos) != color) continue;
			vii plays;
			
			if (isking(pos)) plays = king_plays;
			else if (iswhite(pos)) plays = white_plays;
			else plays = black_plays;
			
			for (int i = 0; i < plays.size(); i++) {
				if (getenemy(pos) == getcolor(pos + plays[i]) && isempty(pos + 2*plays[i])) return true;
			}
			
		}
		shift = (shift+1)%2;
	}
	return false;
}

bool jumpViz(ii pa, ii pb, vii& plays) {
	for (int i = 0; i < plays.size(); i++) {
		if (getenemy(pa) == getcolor(pa + plays[i]) && (pa + 2*plays[i] == pb) && isempty(pb)) {
			m[pb.first][pb.second] = m[pa.first][pa.second];
			m[pa.first][pa.second] = 0;
			
			pa = pa+plays[i];
			m[pa.first][pa.second] = 0;
			
			return true;
		}
	}
	return false;
}

bool dirViz(ii pa, ii pb, vii& plays) {
	for (int i = 0; i < plays.size(); i++) {
		if ((pa + plays[i] == pb) && isempty(pb)) {
			m[pb.first][pb.second] = m[pa.first][pa.second];
			m[pa.first][pa.second] = 0;
			
			return true;
		}
	}
	return false;
}

int main() {
	int cnt = 0, shift = 1, color;
	int invalid;
	char tmp;
	for (int r = 1; r <= 8; r++) {
		for (int c = 1 + shift; c <= 8; c+= 2) {
			p[++cnt] = ii(r, c);
		}
		shift = (shift+1)%2;
	}
	black_plays.pb(ii(1, 1)); black_plays.pb(ii(1, -1));
	white_plays.pb(ii(-1, 1)); white_plays.pb(ii(-1, -1));

	king_plays.pb(ii(1, 1)); king_plays.pb(ii(1, -1));
	king_plays.pb(ii(-1, 1)); king_plays.pb(ii(-1, -1));
	
	int b, w, k;
	while (scanf("%d %d", &b, &w) != EOF && b > 0) {
		memset(m, 0, sizeof(m));
		
		while (b--) {
			scanf("%d", &k);
			ii t = p[abs(k)];
			m[t.first][t.second] = black;
			if (k < 0) m[t.first][t.second] *= -1;
		}
		
		while (w--) {
			scanf("%d", &k);
			ii t = p[abs(k)];
			m[t.first][t.second] = white;
			if (k < 0) m[t.first][t.second] *= -1;
		}

		scanf("%d %c", &cnt, &tmp);
		if(tmp == 'W') color = white;
		else color = black;
		
		invalid = -1;
		
		for (int cont = 1; cont <= cnt; cont++) {
			int prev = -1;
			//printf("\n");
		
			while(true) {
				
				/*for (int i = 1; i <= 8; i++) {
					//for (int j = 1; j <= 8; j++) printf("%d ", m[i][j]);
					//printf("\n");
				}*/
		
				scanf("%d%c", &k, &tmp);
				if (prev == -1) {
					prev = k;
					continue;
				}
				
				if (invalid == -1) {
					// Check this play
					ii pa = p[prev];
					ii pb = p[k];
					
					if (iswhite(pa) && isempty(pb) && color == white) {
						vii myplays;
						if (isking(pa)) myplays = king_plays;
						else myplays = white_plays;
						if (canEat(color)) {
							if (jumpViz(pa, pb, myplays)) {
			
							} else invalid = cont;
						} else if (dirViz(pa, pb, myplays)) {
							
						} else invalid = cont;
					} else if (isblack(pa) && isempty(pb) && color == black) {
						vii myplays;
						if (isking(pa)) myplays = king_plays;
						else myplays = black_plays;
						
						if (canEat(color)) {
							if (jumpViz(pa, pb, myplays)) {
			
							} else invalid = cont;
						} else if (dirViz(pa, pb, myplays)) {
							
						} else invalid = cont;
						
					} else invalid = cont;
				
				}
				if (tmp != '-') {
					ii pa = p[k];
					if (getcolor(pa) == white && pa.first == 1) {
						m[pa.first][pa.second] = -1*white;
					} else if (getcolor(pa) == black && pa.first == 8) {
						m[pa.first][pa.second] = -1*black;
					}
					break;
				} else prev = k;
			}
			color = color%2 + 1;
		}
		
		if (invalid == -1) printf("All moves valid\n");
		else printf("Move %d is invalid\n", invalid);
	}
}