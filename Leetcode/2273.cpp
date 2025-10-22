class Solution {
private:
    vector<int> getFreq(const string &s) {
        vector<int> freq(26, 0);
        for (char c : s) {
            freq[c-'a']++;
        }
        return freq;
    }
public:
    vector<string> removeAnagrams(vector<string>& words) {
        vector<string> ans;
        ans.push_back(words[0]);
        vector<int> prev = getFreq(words[0]), cur;
        int n = words.size();
        for (int i = 1; i < n; i++) {
            cur = getFreq(words[i]);
            if (cur == prev) {
                continue;
            }
            ans.push_back(words[i]);
            prev = cur;
        }
        return ans;
    }
};
