class Solution {
public:
    bool uniqueOccurrences(vector<int>& arr) {
        int minVal = 1e4, maxVal = -1e4;
        for (int num : arr) {
            minVal = min(minVal, num);
            maxVal = max(maxVal, num);
        }
        vector<int> freq(maxVal-minVal+1, 0);
        vector<int> freqFreq(1, 0);
        for (int num : arr) {
            int &f = freq[num-minVal];

            freqFreq[f]--;

            f++;

            if (f >= freqFreq.size()) {
                freqFreq.push_back(0);
            }
            freqFreq[f]++;
        }
        for (int ff : freqFreq) {
            if (ff > 1) {
                return false;
            }
        }
        return true;
    }
};
