class Solution {
public:
    int longestArithSeqLength(vector<int>& nums) {
        int n = nums.size();
        vector<unordered_map<int, int>> end(n);
        int ans = 0;
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                int d = nums[i] - nums[j];
                int cur = 1 + end[j][d];
                end[i][d] = cur;
                ans = ans > cur ? ans : cur;
             }
        }
        return ans + 1;
    }
};
