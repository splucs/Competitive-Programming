class Solution {
public:
    int isPrefixOfWord(string sentence, string searchWord) {
        int ans = 1, i = 0;
        for (char c : sentence) {
            if (c == ' ') {
                i = 0;
                ans++;
                continue;
            }
            if (i == -1) {
                continue;
            }
            if (searchWord[i] == c) {
                i++;
            } else {
                i = -1;
            }
            if (i == searchWord.size()) {
                return ans;
            }
        }
        return -1;
    }
};
