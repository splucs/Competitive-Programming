class Solution {
public:
    int numberOfSubstrings(string s) {
        int lastA = -1, lastB = -1, lastC = -1;
        int ans = 0;
        for (int i = 0; i < (int)s.size(); i++) {
            if (s[i] == 'a') {
                lastA = i;
            }
            if (s[i] == 'b') {
                lastB = i;
            }
            if (s[i] == 'c') {
                lastC = i;
            }
            int lastAll = min(min(lastA, lastB), lastC);
            ans += lastAll+1;
        }
        return ans;
    }
};
