class Solution {
private:
    vector<int> longestIncreasingSubsequence(vector<int> &nums) {
        vector<int> lis, ans(nums.size());
        for (int i = 0; i < (int)nums.size(); i++) {
            int lo = -1, hi = lis.size();
            while (hi > lo + 1) {
                int mid = (hi+lo) >> 1;
                if (lis[mid] >= nums[i]) hi = mid;
                else lo = mid;
            }
            ans[i] = hi;
            if (hi == lis.size()) {
                lis.push_back(nums[i]);
            } else {
                lis[hi] = nums[i];
            }
        }
        return ans;
    }
public:
    int minimumMountainRemovals(vector<int>& nums) {
        vector<int> forwardLis = longestIncreasingSubsequence(nums);
        reverse(nums.begin(), nums.end());
        vector<int> backwardLis = longestIncreasingSubsequence(nums);
        reverse(backwardLis.begin(), backwardLis.end());

        int n = nums.size();
        int ans = n;
        for (int i = 0; i < n; i++) {
            if (forwardLis[i] > 0 && backwardLis[i] > 0) {
                ans = min(ans, n-1-forwardLis[i]-backwardLis[i]);
            }
        }
        return ans;
    }
};
