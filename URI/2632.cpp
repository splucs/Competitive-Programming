#include <bits/stdc++.h>
using namespace std;

int xb, xt, yb, yt, xc, yc, r, dmg;

void getR(char *s, int lev){
	dmg = r = 0;
	if (strcmp(s, "fire") == 0) {
		dmg = 200;
		if (lev == 1) r = 20;
		if (lev == 2) r = 30;
		if (lev == 3) r = 50;
	}
	if (strcmp(s, "water") == 0) {
		dmg = 300;
		if (lev == 1) r = 10;
		if (lev == 2) r = 25;
		if (lev == 3) r = 40;
	}
	if (strcmp(s, "earth") == 0) {
		dmg = 400;
		if (lev == 1) r = 25;
		if (lev == 2) r = 55;
		if (lev == 3) r = 70;
	}
	if (strcmp(s, "air") == 0) {
		dmg = 100;
		if (lev == 1) r = 18;
		if (lev == 2) r = 38;
		if (lev == 3) r = 60;
	}
}

bool intersects() {
	if (xc >= xb && xc <= xt){
		if (yc <= yt + r && yc >= yb - r) return true;
		else return false;
	}
	else if (yc >= yb && yc <= yt){
		if (xc <= xt + r && xc >= xb - r) return true;
		else return false;
	}
	else {
		if (hypot(xc - xb, yc - yb) <= (double)r) return true;
		if (hypot(xc - xt, yc - yb) <= (double)r) return true;
		if (hypot(xc - xb, yc - yt) <= (double)r) return true;
		if (hypot(xc - xt, yc - yt) <= (double)r) return true;
		return false;
	}
	return false;
}

int main() {
	int T, w, h, level;
	char magic[10];
	scanf("%d", &T);
	while(T-->0) {
		scanf("%d %d %d %d", &w, &h, &xb, &yb);
		yt = yb + h;
		xt = xb + w;
		scanf(" %s %d %d %d", magic, &level, &xc, &yc);
		getR(magic, level);
		if (intersects()) printf("%d\n", dmg);
		else printf("0\n");
	}
	return 0;
}