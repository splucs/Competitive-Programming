class Solution {
public:
    long long countInterestingSubarrays(vector<int>& nums, int modulo, int k) {
        vector<int> cnt(1, 0);
        long long ans = 0;
        for (const int num : nums) {
            cnt.back()++;
            if (num % modulo == k) {
                int m = cnt.size();
                cnt.push_back(m >= modulo ? cnt[m-modulo] : 0);
            }
            int m = cnt.size();
            if (k < m) {
                ans += cnt[m-k-1];
            }
        }
        return ans;
    }
};
