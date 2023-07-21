struct entry {
    int len;
    int cnt;
    entry() : len(0), cnt(0) {}
    entry(int _len, int _cnt) : len(_len), cnt(_cnt) {}
};

entry combine(entry &a, entry &b) {
    if (a.len == b.len) {
        return entry(a.len, a.cnt + b.cnt);
    }
    if (a.len > b.len) return a;
    return b;
}

struct fenwickTree {
    vector<entry> tree;
    fenwickTree(int n) {
        tree.resize(n+1);
    }
    void update(int i, entry e) {
        i++;
        for(; i > 0 && i < (int)tree.size(); i += (i & -i))
			tree[i] = combine(e, tree[i]);
    }
    entry query(int i) {
        i++;
        entry ans;
		for(; i; i -= (i & -i))
			ans = combine(ans, tree[i]);
		return ans;
    }
};

class Solution {
public:
    int findNumberOfLIS(vector<int>& nums) {
        int n = nums.size();

        // Calculate indexes in increasing order
        vector<int> idx(n);
        for (int i = 0; i < n; i++) {
            idx[i] = i;
        }
        sort(idx.begin(), idx.end(), [=](int i, int j) {
            if (nums[i] != nums[j]) {
                return nums[i] < nums[j];
            }
            // process latter elements first to account for strictly increasing LIS
            return i > j;
        });

        // Calculate LIS with FenwickTree
        fenwickTree ft(n);
        for (int it = 0; it < n; it++) {
            int i = idx[it];
            entry lis = ft.query(i);
            lis.len++;
            if (lis.len == 1) lis.cnt++;
            ft.update(i, lis);
        }
        return ft.query(n-1).cnt;
    }
};
