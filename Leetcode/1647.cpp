#define NUM_LETTERS 26
class Solution {
public:
    int minDeletions(string s) {
        int n = s.size();
        vector<int> freq(NUM_LETTERS, 0);
        for (char c : s) freq[c-'a']++;

        vector<int> spectrum(n+1, 0);
        for (int i = 0; i < NUM_LETTERS; i++) {
            spectrum[freq[i]]++;
        }

        int ans = 0;
        int carry = 0;
        for (int i = n; i > 0; i--) {
            carry += spectrum[i];
            if (carry > 0) {
                carry--;
            }
            ans += carry;
        }
        return ans;
    }
};
