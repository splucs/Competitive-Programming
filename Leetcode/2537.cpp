class Solution {
public:
    long long countGood(vector<int>& nums, int k) {
        unordered_map<int, int> freq;
        int n = nums.size(), curGood = 0;
        long long ans = 0;
        for (int i = 0, j = 0; j < n; j++) {
            curGood += freq[nums[j]]++;
            for (; curGood >= k; i++) {
                curGood -= --freq[nums[i]];
            }
            ans += i;
        }
        return ans;
    }
};
