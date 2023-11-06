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
        veb->erase(ans);
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
