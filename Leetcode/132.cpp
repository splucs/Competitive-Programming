#define INF 0x3f3f3f3f

class Solution {
private:
    vector<int> odd, even;
    void preprocess(string &s) {
        int n = s.size();
        odd.assign(n, 0);
        even.assign(n, 0);
        for (int i = 0; i < n; i++) {
            int &o = odd[i];
            while (i-o-1 >= 0 && i+o+1 < n && s[i-o-1] == s[i+o+1]) {
                o++;
            }
            int &e = even[i];
            while (i-e >= 0 && i+e+1 < n && s[i-e] == s[i+e+1]) {
                e++;
            }
        }
    }
    bool isPalindrome(int i, int j) {
        int mid = (i+j)>>1;
        if ((j-i)&1) {
            return j-mid <= even[mid];
        }
        return j-mid <= odd[mid];
    }
public:
    int minCut(string s) {
        preprocess(s);
        int n = s.size();
        vector<int> dp(n, INF);
        for (int j = 0; j < n; j++) {
            if (isPalindrome(0, j)) {
                dp[j] = 0;
                continue;
            }
            for (int i = 0; i < j; i++) {
                if (isPalindrome(i+1, j)) {
                    dp[j] = min(dp[j], 1 + dp[i]);
                }
            }
        }
        return dp[n-1];
    }
};
