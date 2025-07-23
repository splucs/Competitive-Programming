class Solution {
private:
    long long numChildren(vector<int>& candies, int pileSize) {
        long long ans = 0;
        for (int candy : candies) {
            ans += candy/pileSize;
        }
        return ans;
    }
public:
    int maximumCandies(vector<int>& candies, long long k) {
        int hi = 1e7 + 1;
        int lo = 0;
        while (hi > lo + 1) {
            int mid = (hi + lo) >> 1;
            if (numChildren(candies, mid) >= k) lo = mid;
            else hi = mid;
        }
        return lo;
    }
};
