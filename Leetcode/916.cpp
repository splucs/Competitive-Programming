#define up(word) for (char c : word) freq[c-'a']++;
#define down(word) for (char c : word) freq[c-'a']--;

class Solution {
public:
    vector<string> wordSubsets(vector<string>& words1, vector<string>& words2) {
        vector<int> minUniversal(26, 0), freq(26, 0);
        for (const string& word : words2) {
            up(word);
            for (int i = 0; i < 26; i++) {
                minUniversal[i] = max(minUniversal[i], freq[i]);
            }
            down(word);
        }

        vector<string> ans;
        for (const string& word : words1) {
            up(word);
            bool ok = true;
            for (int i = 0; i < 26 && ok; i++) {
                if (freq[i] < minUniversal[i]) {
                    ok = false;
                }
            }
            if (ok) {
                ans.push_back(word);
            }
            down(word);
        }
        return ans;
    }
};
