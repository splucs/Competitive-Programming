class Solution {
public:
    int maximumSum(vector<int>& nums) {
        vector<vector<int>> bySum(82);
        for (int num : nums) {
            int digitSum = 0;
            for (int cur = num; cur > 0; cur /= 10) {
                digitSum += cur%10;
            }
            bySum[digitSum].push_back(num);
        }
        int ans = -1;
        for (vector<int>& sameSum : bySum) {
            int n = sameSum.size();
            if (n < 2) {
                continue;
            }
            sort(sameSum.begin(), sameSum.end());
            ans = max(ans, sameSum[n-2] + sameSum[n-1]);
        }
        return ans;
    }
};
