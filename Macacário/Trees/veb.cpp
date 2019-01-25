#include <vector>
#include <cstdio>
using namespace std;

/*
 * Van Emde Boas Tree
 */

class VEB {
private:
	VEB* ups;
	vector<VEB*> los;
	int minx, maxx, k, tk;
#define upper(x) ((x)>>tk)
#define lower(x) ((x)&((1<<tk)-1))
#define index(x, y) (((x)<<tk)^(y))
public:
	VEB(int _k = 20) : k(_k), tk(k>>1) {
		minx = -1, maxx = -1;
		ups = NULL;
		if (k == 1) return;
		ups = new VEB(k-tk);
		los.resize(1<<(k-tk), NULL);
	}
	~VEB() {
		delete ups;
		for(int i = 0; i < (int)los.size(); i++)
			if (los[i]) delete los[i];
	}
	int min() { return minx; }
	int max() { return maxx; }
	bool count(int x) {
		int up = upper(x), lo = lower(x);
		if (x == minx || x == maxx) return true;
		if (k == 1 || !los[up]) return false;
		return los[up]->count(lo);
	}
	int succ(int x) {
		int up = upper(x), lo = lower(x);
		if (k == 1) return x == 0 && maxx == 1 ? 1 : -1;
		if (minx != -1 && x < minx) return minx;
		int mlo = los[up] ? los[up]->max() : -1;
		if (mlo != -1 && lo < mlo)
			return index(up, los[up]->succ(lo));
		up = ups->succ(up);
		if (up == -1) return -1;
		return index(up, los[up]->min());
	}
	int precc(int x) {
		int up = upper(x), lo = lower(x);
		if (k == 1) return x == 1 && minx == 0 ? 0 : -1;
		if (maxx != -1 && x > maxx) return maxx;
		int mlo = los[up] ? los[up]->min() : -1;
		if (mlo != -1 && lo > mlo)
			return index(up, los[up]->precc(lo));
		up = ups->precc(up);
		if (up == -1)
			return minx != -1 && x > minx ? minx : -1;
		return index(up, los[up]->max());
	}
	void insert(int x) {
		if (minx == -1) {
			minx = maxx = x; return;
		}
		if (x < minx) swap(x, minx);
		if (x > maxx) maxx = x;
		if (k == 1 || x == minx) return;
		int up = upper(x), lo = lower(x);
		if (!los[up] || los[up]->min() == -1) {
			ups->insert(up);
			los[up] = new VEB(tk);
		}
		los[up]->insert(lo);
	}
	int removemin() {
		if (minx == -1) return -1;
		int ans = minx;
		if (minx == maxx) {
			minx = maxx = -1; return ans;
		}
		if (k == 1) { minx = maxx; return ans; }
		int up = ups->min();
		minx = index(up, los[up]->removemin());
		if (los[up]->min() == -1) ups->removemin();
		return ans;
	}
	void erase(int x) {
		if (x == -1) return;
		int up = upper(x), lo = lower(x);
		if (x == minx) removemin();
		else if (k == 1 && x == maxx) maxx = minx;
		else {
			los[up]->erase(lo);
			if (los[up]->min() == -1) ups->erase(up);
			if (x == maxx && los[up]->max() != -1)
				maxx = index(up, los[up]->max());
			else if (x == maxx) maxx = precc(x);
		}
	}	
};

/*
 * TEST MATRIX
 */

/*
	void print(int h) {
		for(int i = 0; i < h; i++) printf("| ");
		printf("min: %d max: %d\n", minx, maxx);

		for(int i = 0; i < h; i++) printf("| ");
		printf("ups:%s\n", ups ? "" : " NULL");
		if (ups) ups->print(h+1);

		for(int j = 0; j < (int)los.size(); j++) {
			for(int i = 0; i < h; i++) printf("| ");
			printf("los[%d]:%s\n", j, los[j] ? "" : " NULL");
			if (los[j]) los[j]->print(h+1);
		}
	}
*/
#include <set>
#include <cstdlib>
#include <ctime>

bool test(int ntests, int k) {
	srand(time(NULL));
	VEB veb(k);
	set<int> control;
	vector<int> present;
	for(int test = 1; test <= ntests; test++) {
		//printf("test %d:\n", test);
		int op = rand()%(2*control.size() > (1<<(k-1)) ? 2 : 3);
		if (control.size() == (1u<<k) || (op == 0 && !control.empty())) {
			int i, x;
			if (rand() % 2) {
				i = rand()%present.size();
				x = present[i];
				//printf("removing %d...\n", x);
				veb.erase(x);
				//printf("removed %d\n", x);
			}
			else {
				x = *control.begin();
				i = 0;
				while(present[i] != x) i++;
				//printf("removing %d (min)...\n", x);
				int y = veb.removemin();
				//printf("removed %d (min)\n", y);
				if (x != y) {
					printf("failed test %d, removed min %d, but found %d\n", test, x, y);
					return false;
				}
			}
			control.erase(x);
			swap(present[i], present.back());
			present.pop_back();
		}
		else {
			int x;
			do {
				x = rand()%(1<<k);
			} while(control.count(x));
			control.insert(x);
			//printf("adding %d...\n", x);
			veb.insert(x);
			present.push_back(x);
			//printf("added %d\n", x);
		}
		//printf("-->\n");
		//veb.print(1);
		//printf("<--\n");
		for(int x = 0; x < (1<<k); x++) {
			bool res1 = control.count(x);
			bool res2 = veb.count(x);
			if (res1 != res2) {
				printf("failed test %d, count(%d): control %d veb %d", test, x, res1, res2);
				return false;
			}
		}
		for(int x = 0; x < (1<<k); x++) {
			if (x > 0) {
				set<int>::iterator it = control.lower_bound(x);
				int prec = veb.precc(x);
				if (it == control.begin()) {
					if (prec != -1) {
						printf("failed test %d, prec(%d)=%d should not exist\n", test, x, prec);
						return false;
					}
				}
				else {
					it--;
					if (*it != prec) {
						printf("failed test %d, precControl(%d)=%d precVeb(%d)=%d\n", test, x, *it, x, prec);
						return false;
					}
				}
			}
		}
		for(int x = 0; x < (1<<k); x++) {
			if (x+1 < (1<<k)) {
				set<int>::iterator it = control.upper_bound(x);
				int suc = veb.succ(x);
				if (it == control.end()) {
					if (suc != -1) {
						printf("failed test %d, suc(%d)=%d should not exist\n", test, x, suc);
						return false;
					}
				}
				else {
					if (*it != suc) {
						printf("failed test %d, sucControl(%d)=%d sucVeb(%d)=%d\n", test, x, *it, x, suc);
						return false;
					}
				}
			}
		}
	}
	printf("all tests passed\n");
	return true;
}

int main() {
	test(1000, 16);
}