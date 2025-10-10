class Solution {
public:
    int longestSubarray(vector<int>& nums) {
        int maxVal = 0, maxSeq = 0;
        int lastVal = 0, seq = 0;
        for (int num : nums) {
            if (num == lastVal) {
                seq++;
                continue;
            }

            if (lastVal > maxVal || (lastVal == maxVal && maxSeq < seq)) {
                maxVal = lastVal;
                maxSeq = seq;
            }
            seq = 1;
            lastVal = num;
        }
        if (lastVal > maxVal || (lastVal == maxVal && maxSeq < seq)) {
            maxVal = lastVal;
            maxSeq = seq;
        }
        return maxSeq;
    }
};
