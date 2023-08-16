class Solution {
private:
    vector<int> nums;
    vector<int> prefix, suffix;
    vector<int> ans;
    void dc(int lo, int hi, int k) {
        if (lo == hi) {
            if (k == 1) ans[lo] = nums[lo];
            prefix[lo] = suffix[lo] = nums[lo];
            return;
        }

        int mid = (lo + hi) >> 1;
        dc(lo, mid, k);
        dc(mid+1, hi, k);

        for (int i = mid, pref = -1e5; i >= lo; i--) {
            pref = max(pref, nums[i]);
            prefix[i] = pref;
        }
        for (int j = mid+1, suf = -1e5; j <= hi; j++) {
            suf = max(suf, nums[j]);
            suffix[j] = suf;
        }

        int i = mid-k+2;
        if (i < lo) i = lo;
        int j = i+k-1;
        for (; i <= mid && j <= hi; i++, j++) {
            ans[i] = max(prefix[i], suffix[j]);
        }
    }
public:
    vector<int> maxSlidingWindow(vector<int>& nums, int k) {
        int n = nums.size();
        this->nums = nums;
        prefix.resize(n);
        suffix.resize(n);
        ans.resize(n-k+1);
        dc(0, n-1, k);
        return ans;
    }
};
