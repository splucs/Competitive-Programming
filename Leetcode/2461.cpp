class Solution {
public:
    long long maximumSubarraySum(vector<int>& nums, int k) {
        int i = 0;
        long long sum = 0, ans = 0;
        unordered_map<int, int> freq;
        int repeated = 0;
        for (int i = 0, j = -k; i < (int)nums.size(); i++, j++) {
            sum += nums[i];
            freq[nums[i]]++;
            if (freq[nums[i]] == 2) {
                repeated++;
            }
            if (j >= 0) {
                sum -= nums[j];
                freq[nums[j]]--;
                if (freq[nums[j]] == 1) {
                    repeated--;
                }
            }
            if (i >= k-1 && repeated == 0) {
                ans = max(ans, sum);
            }
        }
        return ans;
    }
};
