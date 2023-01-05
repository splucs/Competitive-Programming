/*
 * Date data structure
 */

int mnt[13] = {0, 31, 59, 90, 120, 151, 181, 212, 243, 273, 304, 334, 365};

struct Date {
	int d, m, y;
	Date() : d(1), m(1), y(1) {}
	Date(int d, int m, int y) : d(d), m(m), y(y) {}
	Date(int days) : d(1), m(1), y(1) { advance(days); }
	bool leap() { return (y%4 == 0 && y%100) || (y%400 == 0); }
	int mdays() { return mnt[m] - mnt[m-1] + (m == 2)*leap(); }
	int ydays() { return 365 + leap(); }
	int count() { // dist to 01/01/01
		return (d-1) + mnt[m-1] + (m > 2)*leap() +
			365*(y-1) + (y-1)/4 - (y-1)/100 + (y-1)/400;
	}
	int weekday() { return (count()+1) % 7; }
	void advance(int days) {
		days += count();
		d = m = 1, y = 1 + days/366;
		days -= count();
		while(days >= ydays()) days -= ydays(), y++;
		while(days >= mdays()) days -= mdays(), m++;
		d += days;
	}
};

/*
 * TEST MATRIX
 */

#include <cstdio>
#include <cassert>
#include <algorithm>
using namespace std;

Date advance1(Date date) {
	int d = date.d;
	int m = date.m;
	int y = date.y;
	int w = date.weekday();
	d++;
	int mcnt = mnt[m]- mnt[m-1];
	if (m == 2 && date.leap()) mcnt++;
	if (d > mcnt) {
		m++; d = 1;
	}
	if (m == 13) {
		y++; m = 1;
	}
	date.advance(1);
	assert(d == date.d);
	assert(m == date.m);
	assert(y == date.y);
	w = (w+1)%7;
	assert(w == date.weekday());
	return date;
}

void test() {
	Date date;
	for(int i = 0; i < 1000000; i++) {
		Date aux(i);
		assert(aux.d == date.d);
		assert(aux.m == date.m);
		assert(aux.y == date.y);
		date = advance1(date);
	}
	for(int t = 1; t <= 1000; t++) {
		int d1 = rand()%100000;
		int d2 = rand()%100000;
		if (d1 > d2) swap(d1, d2);
		Date date1(d1), date2(d2);
		Date aux = date1;
		for(int i = 0; i < d2-d1; i++) aux = advance1(aux);
		date1.advance(d2 - d1);
		assert(date1.d == date2.d);
		assert(date1.m == date2.m);
		assert(date1.y == date2.y);
		assert(aux.d == date2.d);
		assert(aux.m == date2.m);
		assert(aux.y == date2.y);
	}
}

int main() {
	test();
	int d, m, y;
	while (scanf("%d %d %d", &d, &m, &y) != EOF) {
		Date date(d, m, y);
		int lastw;
		for(int i = 0; i < 10; i++) {
			int w = date.weekday();
			printf("%02d/%02d/%04d %s\n", date.d, date.m, date.y, 
				w == 0 ? "Domingo" :
				w == 1 ? "Segunda-feira" :
				w == 2 ? "Terca-feira" :
				w == 3 ? "Quarta-feira" :
				w == 4 ? "Quinta-feira" :
				w == 5 ? "Sexta-feira" :
				w == 6 ? "Sabado" : "undefined"
			);
			if (i > 0) assert(w == (lastw+1)%7);
			lastw = w;
			date.advance(1);
		}
	}
	return 0;
}