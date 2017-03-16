#include <iostream>
using namespace std;

typedef pair<int, int> ii;

ii floydCycleFinding(int x0) {
	// 1st part: finding k*start, hares speed is 2x tortoises
	int tortoise = f(x0), hare = f(f(x0)); // f(x0) is the node next to x0
	while (tortoise != hare) { tortoise = f(tortoise); hare = f(f(hare)); }
	// 2nd part: finding start, hare and tortoise move at the same speed
	int start = 0; hare = x0;
	while (tortoise != hare) { tortoise = f(tortoise); hare = f(hare); start++; }
	// 3rd part: finding period, hare moves, tortoise stays
	int period = 1; hare = f(tortoise);
	while (tortoise != hare) { hare = f(hare); period++; }
	return ii(start, period);
}