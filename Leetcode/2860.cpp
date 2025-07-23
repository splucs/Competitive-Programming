class Solution {
public:
    int countWays(vector<int>& nums) {
        int n = nums.size();
        vector<int> freq(n+1, 0);
        for (int num : nums) {
            freq[num]++;
        }

        int less = 0, ans = 0;
        for (int m = 0; m <= n; m++) {
            less += freq[m];
            if (freq[m] == 0 && less == m) {
                ans++;
            }
        }
        return ans;
    }
};
