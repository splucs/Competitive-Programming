class Solution {
public:
    int numberOfArrays(vector<int>& differences, int lower, int upper) {
        long long cur = 0, minDiff = 0, maxDiff = 0;
        for (int diff : differences) {
            cur += diff;
            minDiff = min(minDiff, cur);
            maxDiff = max(maxDiff, cur);
        }
        int range = upper - lower;
        long long diffRange = maxDiff - minDiff;
        if (range < diffRange) {
            return 0;
        }
        return range - diffRange + 1;
    }
};
