class Solution {
public:
    int maximumLength(vector<int>& nums, int k) {
        int n = nums.size(), ans = 0;
        // last[i] = max sequence seen so far where the last element
        // has parity i and parity between adjacent elements is b
        vector<int> last;
        for (int b = 0; b < k; b++) {
            last.assign(k, 0);
            for (int i = 0; i < n; i++) {
                int p = nums[i] % k;
                last[p] = 1 + last[(b-p+k)%k];
                ans = max(ans, last[p]);
            }
        }
        return ans;
    }
};
