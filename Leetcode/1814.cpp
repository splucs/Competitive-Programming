#define MOD 1000000007

class Solution {
private:
    inline int rev(int num) {
        int ans = 0;
        for(; num > 0; num /= 10) {
            ans = (ans*10) + (num%10);
        }
        return ans;
    }
public:
    int countNicePairs(vector<int>& nums) {
        unordered_map<int, int> cnt;
        for (int num : nums) {
            cnt[num-rev(num)]++;
        }
        int ans = 0;
        for (pair<int, int> entry : cnt) {
            int n = entry.second;
            ans = (ans + ((n*1ll*(n-1))>>1)) % MOD;
        }
        return ans;
    }
};
