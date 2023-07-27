class Solution {
private:
    bool can(int n, long long t, vector<int>& batteries) {
        long long sum = n*t;
        for (int battery : batteries) {
            if (battery > t) sum -= t;
            else sum -= battery;
        }
        return sum <= 0;
    }
public:
    long long maxRunTime(int n, vector<int>& batteries) {
        long long lo = 0;
        long long hi = 1e14 + 1;
        while (hi > lo + 1) {
            long long mid = (hi+lo)>>1;
            if (can(n, mid, batteries)) lo = mid;
            else hi = mid;
        }
        return lo;
    }
};
