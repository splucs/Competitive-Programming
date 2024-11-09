class Solution {
public:
    long long minimumSteps(string s) {
        long long ans = 0;
        int black = 0;
        for (char c : s) {
            if (c == '1') {
                black++;
            } else {
                ans += black;
            }
        }
        return ans;
    }
};
