#define INF 0x3f3f3f3f
class Solution {
public:
    int maximumDifference(vector<int>& nums) {
        int minNum = INF;
        int ans = -1;
        for (int num : nums) {
            ans = max(ans, num - minNum);
            minNum = min(minNum, num);
        }
        return ans > 0 ? ans : -1;
    }
};
