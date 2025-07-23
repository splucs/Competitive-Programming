class Solution {
private:
    bool canZero(vector<int>& nums, vector<vector<int>>& queries, int k) {
        int n = nums.size();
        vector<int> sum(n, 0);
        for (int q = 0; q < k; q++) {
            int l = queries[q][0];
            int r = queries[q][1];
            int val = queries[q][2];
            sum[l] += val;
            if (r+1 < n) {
                sum[r+1] -= val;
            }
        }
        for (int i = 0; i < n; i++) {
            if (i > 0) {
                sum[i] += sum[i-1];
            }
            if (nums[i] > sum[i]) {
                return false;
            }
        }
        return true;
    }
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        if (!canZero(nums, queries, queries.size())) {
            return -1;
        }
        int hi = queries.size();
        int lo = -1;
        while(hi > lo + 1) {
            int mid = (hi + lo)/2;
            if (canZero(nums, queries, mid)) hi = mid;
            else lo = mid;
        }
        return hi;
    }
};
