class Solution {
public:
    vector<int> getAverages(vector<int>& nums, int k) {
        int n = nums.size();
        vector<int> ans(n, -1);
        int den = 2*k+1;
        long long num = 0;
        for (int i = 0; i < n; i++) {
            num += nums[i];
            if (i >= den) num -= nums[i-den];

            if (i-den+1 >= 0) {
                ans[i-k] = num/den;
            }
        }
        return ans;
    }
};
