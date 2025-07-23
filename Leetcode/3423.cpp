class Solution {
private:
    inline int abs(int x) {
        return x < 0 ? -x : x;
    }
public:
    int maxAdjacentDistance(vector<int>& nums) {
        int prev = nums.back();
        int ans = 0;
        for (int num : nums) {
            ans = max(ans, abs(num - prev));
            prev = num;
        }
        return ans;
    }
};
