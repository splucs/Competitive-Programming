class Solution {
public:
    vector<int> findDiagonalOrder(vector<vector<int>>& nums) {
        int n = nums.size();
        int maxSum = 0;
        int cnt = 0;
        for (int i = 0; i < n; i++) {
            int m = nums[i].size();
            cnt += m;
            maxSum = max(maxSum, i+m-1);
        }

        vector<vector<int>> buckets(maxSum+1);
        for (int i = 0; i < n; i++) {
            int m = nums[i].size();
            for (int j = 0; j < m; j++) {
                buckets[i+j].push_back(nums[i][j]);
            }
        }

        vector<int> ans;
        ans.reserve(cnt);
        for (vector<int> &bucket : buckets) {
            for (int i = bucket.size()-1; i >= 0; i--) {
                ans.push_back(bucket[i]);
            }
        }
        return ans;
    }
};
