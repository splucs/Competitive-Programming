class Solution {
public:
    string removeDuplicateLetters(string s) {
        vector<int> freq(256, 0);
        for (char c : s) freq[c]++;

        string ans;
        vector<bool> seen(256, 0);
        for (char c : s) {
            if (seen[c]) {
                freq[c]--;
                continue;
            }

            while (ans.size() > 0 && freq[ans.back()] > 1 && ans.back() > c) {
                freq[ans.back()]--;
                seen[ans.back()] = false;
                ans.pop_back();
            }
            ans.push_back(c);
            seen[c] = true;
        }
        return ans;
    }
};
