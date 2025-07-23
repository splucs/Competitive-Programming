class Solution {
private:
public:
    int minZeroArray(vector<int>& nums, vector<vector<int>>& queries) {
        int ans = 0, n = nums.size();
        vector<int> sum(n+1, 0);
        for (int i = 0; i < n; i++) {
            if (i > 0) {
                sum[i] += sum[i-1];
            }
            while (nums[i] > sum[i]) {
                if (ans == queries.size()) {
                    return -1;
                }
                vector<int>& q = queries[ans++];
                int l = q[0], r = q[1], val = q[2];
                if (r < i) {
                    continue;
                }
                sum[max(i, l)] += val;
                sum[r+1] -= val;
            }
        }
        return ans;
    }
};
