class Solution {
public:
    int minTaps(int n, vector<int>& ranges) {
        vector<pair<int, int>> taps(n+1);
        for (int i = 0; i < n+1; i++) {
            int lo = i-ranges[i];
            if (lo < 0) lo = 0;
            int hi = i+ranges[i];
            if (hi > n) hi = n;
            taps[i] = make_pair(lo, hi);
        }
        sort(taps.begin(), taps.end());

        int ans = 0;
        int coveredUpTo = 0;
        for (int i = 0; i < n+1 && coveredUpTo < n;) {
            if (taps[i].first > coveredUpTo) {
                return -1;
            }
            int newCover = coveredUpTo;
            for (; i < n+1 && taps[i].first <= coveredUpTo; i++) {
                newCover = max(newCover, taps[i].second);
            }
            ans++;
            coveredUpTo = newCover;
        }
        return ans;
    }
};
