class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        int n = nums.size();
        int m = maxVal(nums);
        vector<vector<int>> end(n, vector<int>(2*m+1, 1));
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                int d = nums[i] - nums[j] + m;
                int cur = 1 + end[j][d];
                end[i][d] = cur;
                ans = ans > cur ? ans : cur;
             }
        }
        return ans;
    }
    int maxVal(vector<int>& nums) {
        int ans = 0;
        for (int num : nums) {
            ans = ans > num ? ans : num;
        }
        return ans;
    }
};
