class Solution {
public:
    int minimumDeletions(string word, int k) {
        vector<int> freq(26, 0);
        for (char c : word) {
            freq[c-'a']++;
        }

        int ans = word.size();
        for (int i = 0; i < 26; i++) {
            if (freq[i] == 0) {
                continue;
            }

            int minFreq = freq[i];
            int curAns = 0;
            for (int j = 0; j < 26; j++) {
                if (freq[j] < minFreq) {
                    curAns += freq[j];
                } else if (freq[j] > minFreq) {
                    curAns += max(0, freq[j]-minFreq-k);
                }
            }
            ans = min(ans, curAns);
        }
        return ans;
    }
};
