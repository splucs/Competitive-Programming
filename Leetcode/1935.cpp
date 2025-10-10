class Solution {
public:
    int canBeTypedWords(string text, string brokenLetters) {
        int isBroken = 0;
        for (char c : brokenLetters) {
            isBroken |= (1 << (c-'a'));
        }
        int numBroken = 0;
        int ans = 0;
        for (char c : text) {
            if (c == ' ') {
                if (numBroken == 0) {
                    ans++;
                }
                numBroken = 0;
                continue;
            }

            if (isBroken & (1 << (c-'a'))) {
                numBroken++;
            }
        }
        if (numBroken == 0) {
            ans++;
        }
        return ans;
    }
};
