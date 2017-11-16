#include <bits/stdc++.h>
using namespace std;

int len[13] = {0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31};

int countJulian(int day, int month, int year) {
	int curday = 4;
	int curmonth = 10;
	int curyear = 1582;
	int ans = 0;
	while(curyear < year || curmonth < month || curday < day) {		
		
		ans++;
		curday++;
		if (curday > len[curmonth]) {
			if (curmonth != 2 || (curyear % 4 != 0) || curday == 30) {
				curday = 1;
				curmonth++;
			}
		}
		if (curmonth > 12) {
			curmonth = 1;
			curyear++;
		}
		
		while (curyear != year && curday == 1 && curmonth == 1) {
			if (curyear % 4 == 0) ans += 366;
			else ans += 365;
			curyear++;
		}
	}
	return ans;
}

bool mean(int y) {
	if (y % 400 == 0) return true;
	if (y % 100 == 0) return false;
	if (y % 4 == 0) return true;
	return false;
}

void countGregorian(int cnt, int & day, int & month, int & year) {
	day = 15;
	month = 10;
	year = 1582;
	while(cnt --> 0) {
		
		while (day == 1 && month == 1) {
			if (mean(year) && cnt > 366) {
				cnt -= 366;
				year++;
			}
			else if (!mean(year) && cnt > 365) {
				cnt -= 365;
				year++;
			}
			else break;
		}
		
		day++;
		if (day > len[month]) {
			if (month != 2 || !mean(year) || day == 30) {
				day = 1;
				month++;
			}
		}
		if (month > 12) {
			month = 1;
			year++;
		}
	}
}

int main() {
	int year, month, day;
	while(scanf(" %d-%d-%d", &year, &month, &day) != EOF) {
		int cnt = countJulian(day, month, year);
		countGregorian(cnt, day, month, year);
		printf("%d-%02d-%02d\n", year, month, day);
	}
	return 0;
}