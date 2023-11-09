#define MOD 1000000007
class Solution {
public:
    int countHomogenous(string s) {
        int n = s.size();
        int ans = 0;

        for (int i = 0, cnt = 0; i < n; i++) {
            cnt++;
            if (i+1 == n || s[i+1] != s[i]) {
                ans = (ans + ((cnt*(cnt+1LL))>>1)) % MOD;
                cnt = 0;
            }
        }
        return ans;
    }
};
