class FenwickTree {
private:
	vector<int> ft;
public:
	FenwickTree(int n) { ft.assign(n + 1, 0); }
	int rsq(int i) { // returns RSQ(1, i)
        i++;
		int sum = 0;
		for(; i > 0; i -= (i & -i))
			sum += ft[i];
		return sum;
	}
	int rsq(int i, int j) {
		return rsq(j) - rsq(i - 1);
	}
	void update(int i, int v) {
        i++;
		for(; i > 0 && i < (int)ft.size(); i += (i & -i))
			ft[i] += v;
	}
};

class Solution {
public:
    long long goodTriplets(vector<int>& nums1, vector<int>& nums2) {
        int n = nums1.size();

        vector<int> pos1(n);
        for (int i = 0; i < n; i++) {
            pos1[nums1[i]] = i;
        }
        
        vector<int> posIn1(n);
        for (int i = 0; i < n; i++) {
            posIn1[i] = pos1[nums2[i]];
        }
        
        FenwickTree smallerFt(n);
        vector<int> smaller(n);
        for (int i = 0; i < n; i++) {
            smaller[i] = smallerFt.rsq(posIn1[i]);
            smallerFt.update(posIn1[i], 1);
        }
        
        FenwickTree biggerFt(n);
        vector<int> bigger(n);
        for (int i = n-1; i >= 0; i--) {
            bigger[i] = biggerFt.rsq(posIn1[i], n-1);
            biggerFt.update(posIn1[i], 1);
        }

        long long ans = 0;
        for (int i = 0; i < n; i++) {
            ans += (long long) smaller[i] * (long long) bigger[i];
        }
        return ans;
    }
};
