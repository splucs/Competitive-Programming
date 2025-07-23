class Solution {
private:
    int gcd(int x, int y) {
        return y == 0 ? x : gcd(y, x%y);
    }
public:
    int countPairs(vector<int>& nums, int k) {
        int ans = 0, n = nums.size();
        for (int j = 0; j < n; j++) {
            int di = k/gcd(j, k);
            for (int i = 0; i < j; i += di) {
                if (nums[i] == nums[j]) {
                    ans++;
                }
            }
        }
        return ans;
    }
};
