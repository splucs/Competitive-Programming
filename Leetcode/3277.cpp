class Solution {
public:
    vector<int> maximumSubarrayXor(vector<int>& nums, vector<vector<int>>& queries) {
        int n = nums.size(), q = queries.size();

        vector<vector<int>> queriesByLen(n);
        for (int t = 0; t < q; t++) {
            int i = queries[t][0], j = queries[t][1];
            queriesByLen[j-i].push_back(t);
        }

        vector<int> ans(q), score(n), maxScore(n);
        for (int len = 0; len < n; len++) {
            for (int i = 0; i < n-len; i++) {
                if (len == 0) {
                    score[i] = nums[i];
                    maxScore[i] = nums[i];
                } else {
                    score[i] = score[i+1]^score[i];
                    maxScore[i] = max(score[i], max(maxScore[i+1], maxScore[i]));
                }
            }

            for (int t : queriesByLen[len]) {
                ans[t] = maxScore[queries[t][0]];
            }
        }
        return ans;
    }
};
