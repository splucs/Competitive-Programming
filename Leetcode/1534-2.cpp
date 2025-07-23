class FenwickTree {
private:
	vector<int> ft;
public:
	FenwickTree(int n) { ft.assign(n + 1, 0); }
	int rsq(int i) { // returns RSQ(1, i)
		int sum = 0;
		for(; i > 0; i -= (i & -i))
			sum += ft[i];
		return sum;
	}
	int rsq(int i, int j) {
		return rsq(j) - rsq(i - 1);
	}
	void update(int i, int v) {
		for(; i > 0 && i < (int)ft.size(); i += (i & -i))
			ft[i] += v;
	}
};

class Solution {
private:
    inline int abs(int x) {
        return x > 0 ? x : -x;
    }
public:
    int countGoodTriplets(vector<int>& arr, int a, int b, int c) {
        int n = arr.size(), maxElem = 0;
        for (int i = 0; i < n; i++) {
            arr[i]++; // FenwickTree is 1-indexed
            maxElem = max(maxElem, arr[i]);
        }
        FenwickTree ft(maxElem);

        int ans = 0;
        for (int j = n-1; j > 0; j--) {
            for (int i = j-1; i >= 0; i--) {
                if (abs(arr[i]-arr[j]) > a) {
                    continue;
                }
                int maxK = min(min(arr[j] + b, arr[i] + c), maxElem);
                int minK = max(max(arr[j] - b, arr[i] - c), 0);
                if (maxK < minK) {
                    continue;
                }
                ans += ft.rsq(minK, maxK);
            }
            ft.update(arr[j], 1);
        }
        return ans;
    }
};
