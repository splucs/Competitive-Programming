class Solution {
public:
    int minOperations(string s) {
        int ans = 0;
        for (char c : s) {
            if (c != 'a') {
                ans = max(ans, 'z'-c+1);
            }
        }
        return ans;
    }
};
