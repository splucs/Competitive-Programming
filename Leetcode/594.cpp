class Solution {
public:
    int findLHS(vector<int>& nums) {
        sort(nums.begin(), nums.end());
        int prev = -1, prevCnt = 0, prevDiff = -1, prevDiffCnt = 0;
        int ans = 0;
        for (int num : nums) {
            if (num == prev) {
                prevCnt++;
                continue;
            }
            if (prevDiff == prev - 1 && prevDiffCnt > 0) {
                ans = max(ans, prevCnt + prevDiffCnt);
            }
            prevDiffCnt = prevCnt;
            prevDiff = prev;
            prevCnt = 1;
            prev = num;
        }
        if (prevDiff == prev - 1 && prevDiffCnt > 0) {
            ans = max(ans, prevCnt + prevDiffCnt);
        }
        return ans;
    }
};
