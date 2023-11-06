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
	int min() { return minx; }
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
};

class SeatManager {
private:
    VEB *veb;
public:
    SeatManager(int n) {
        veb = new VEB(17);
        for (int i = 1; i <= n; i++) {
            veb->insert(i);
        }
    }
    
    int reserve() {
        int ans = veb->min();
        veb->removemin();
        return ans;
    }
    
    void unreserve(int seatNumber) {
        veb->insert(seatNumber);
    }
};

/**
 * Your SeatManager object will be instantiated and called as such:
 * SeatManager* obj = new SeatManager(n);
 * int param_1 = obj->reserve();
 * obj->unreserve(seatNumber);
 */
