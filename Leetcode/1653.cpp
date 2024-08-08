class Solution {
public:
    int minimumDeletions(string s) {
        int n = s.size();
        int totA = 0;
        for (char c : s) {
            if (c == 'a') {
                totA++;
            }
        }

        int ans = totA, seenA = 0, seenB = 0;
        for (char c : s) {
            if (c == 'a') {
                seenA++;
            } else {
                seenB++;
            }

            ans = min(ans, seenB + totA - seenA);
        }
        return ans;
    }
};
