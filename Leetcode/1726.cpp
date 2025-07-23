class Solution {
public:
    int tupleSameProduct(vector<int>& nums) {
        unordered_map<int, int> mults;
        int n = nums.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < i; j++) {
                mults[nums[i]*nums[j]]++;
            }
        }
        int ans = 0;
        for (pair<int, int> mult : mults) {
            int cnt = mult.second;
            ans += 4*cnt*(cnt-1);
        }
        return ans;
    }
};
