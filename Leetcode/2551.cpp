class Solution {
public:
    long long putMarbles(vector<int>& weights, int k) {
        int n = weights.size();
        vector<long long> barriers(n-1);
        for (int i = 0; i < n-1; i++) {
            barriers[i] = weights[i] + weights[i+1];
        }
        sort(barriers.begin(), barriers.end());

        long long minSum = 0, maxSum = 0;
        for (int i = 0, j = n-2; i < k-1; i++, j--) {
            minSum += barriers[i];
            maxSum += barriers[j];
        }
        return maxSum - minSum;
    }
};
