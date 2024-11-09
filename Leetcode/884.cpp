class Solution {
private:
    unordered_map<string, int> getFreq(const string& sentence) {
        unordered_map<string, int> freq;
        for(int st = 0, en = 0; st < (int)sentence.size();) {
            en = sentence.find(' ', st);
            if (en == string::npos) {
                en = sentence.size();
            }
            freq[sentence.substr(st, en-st)]++;
            st = en+1;
        }
        return freq;
    }
public:
    vector<string> uncommonFromSentences(string s1, string s2) {
        unordered_map<string, int> freq1 = getFreq(s1);
        unordered_map<string, int> freq2 = getFreq(s2);
        vector<string> ans;
        for (pair<const string, int> f : freq1) {
            const string& word = f.first;
            const int cnt = f.second;
            if (freq2[word] == 0 && cnt == 1) {
                ans.push_back(word);
            }
        }
        for (pair<const string, int> f : freq2) {
            const string& word = f.first;
            const int cnt = f.second;
            if (freq1[word] == 0 && cnt == 1) {
                ans.push_back(word);
            }
        }
        return ans;
    }
};
