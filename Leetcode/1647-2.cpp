#define NUM_LETTERS 26
class Solution {
public:
    int minDeletions(string s) {
        int n = s.size();
        vector<int> freq(NUM_LETTERS, 0);
        for (char c : s) freq[c-'a']++;

        sort(freq.begin(), freq.end());

        int ans = 0;
        int carry = n+1;
        for (int i = NUM_LETTERS-1; i >= 0; i--) {
            int f = freq[i];
            if (carry > f) {
                carry = f;
            } else {
                ans += f-carry;
            }

            if (carry > 0) {
                carry--;
            }
        }
        return ans;
    }
};
