class Solution {
public:
    int longestPalindrome(vector<string>& words) {
        vector<vector<int>> freq(26, vector<int>(26, 0));
        int ans = 0;
        for (const string& word : words) {
            int i = word[0] - 'a', j = word[1] - 'a';
            if (freq[j][i] > 0) {
                freq[j][i]--;
                ans += 4;
            } else {
                freq[i][j]++;
            }
        }
        for (int i = 0; i < 26; i++) {
            if (freq[i][i] > 0) {
                ans += 2;
                break;
            }
        }
        return ans;
    }
};
