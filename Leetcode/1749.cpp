#define INF 0x3f3f3f3f
#define abs(x) (x < 0 ? -x : x)

class Solution {
public:
    int maxAbsoluteSum(vector<int>& nums) {
        int maxSum = -INF, minSum = INF;
        int ans = 0;
        for (int num : nums) {
            maxSum = max(num, num+maxSum);
            minSum = min(num, num+minSum);
            ans = max(ans, max(abs(maxSum), abs(minSum)));
        }
        return ans;
    }
};
