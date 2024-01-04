class Solution {
public:
    int minOperations(vector<int>& nums) {
        unordered_map<int, int> cnt;
        for (int num : nums) {
            cnt[num]++;
        }
        int ans = 0;
        for (pair<int, int> entry : cnt) {
            int v = entry.second;
            if (v <= 1) {
                return -1;
            }
            ans += (v+2)/3;
        }
        return ans;
    }
};
