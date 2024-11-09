class Solution {
public:
    int largestCombination(vector<int>& candidates) {
        vector<int> freq(32, 0);
        for (int cand : candidates) {
            for (int i = 0; cand > 0; i++, cand >>= 1) {
                if (cand & 1) {
                    freq[i]++;
                }
            }
        }
        return *max_element(freq.begin(), freq.end());
    }
};
