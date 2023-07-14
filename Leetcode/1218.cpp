class Solution {
public:
    int longestSubsequence(vector<int>& arr, int difference) {
        int maxVal = maxValue(arr);
        vector<int> maxSeq(maxVal+1, 0);
        int ans = 0;
        for (int val : arr) {
            int last = val-difference;
            if (last < 0 || last > maxVal) {
                maxSeq[val] = 1;
                continue;
            }
            int maxSeqLast = maxSeq[last];
            if (maxSeq[val] < 1 + maxSeq[last]) {
                maxSeq[val] = 1 + maxSeq[last];
            }
            if (ans < maxSeq[val]) ans = maxSeq[val];
        }
        return ans;
    }
    int maxValue(vector<int>& arr) {
        int ans = 0;
        for (int& val : arr) {
            val += 1e4;
            if (ans < val) ans = val;
        }
        return ans;
    }
};
