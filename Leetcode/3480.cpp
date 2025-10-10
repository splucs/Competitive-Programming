class Solution {
public:
    long long maxSubarrays(int n, vector<vector<int>>& conflictingPairs) {
        long long total = 0;
        int m = conflictingPairs.size();
        vector<long long> diff(m, 0);

        vector<vector<int>> pairs(n+1);
        for (int j = 0; j < m; j++) {
            int& u = conflictingPairs[j][0];
            int& v = conflictingPairs[j][1];
            if (u > v) {
                swap(u, v);
            }
            pairs[v].push_back(j);
        }

        vector<int> topPairs;
        for (int v = 1; v <= n; v++) {
            for (int j : pairs[v]) {
                topPairs.push_back(j);
            }
            // two rounds of bubble sort since we just want top 2
            for (int k = 0; k < 2; k++) {
                for (int jt = topPairs.size()-2; jt >= 0; jt--) {
                    int u1 = conflictingPairs[topPairs[jt]][0];
                    int u2 = conflictingPairs[topPairs[jt+1]][0];
                    if (u1 < u2) {
                        swap(topPairs[jt], topPairs[jt+1]);
                    }
                }
            }
            if (topPairs.size() > 2) {
                topPairs.resize(2);
            }

            int u1 = topPairs.size() > 0 ? conflictingPairs[topPairs[0]][0] : 0;
            int u2 = topPairs.size() > 1 ? conflictingPairs[topPairs[1]][0] : 0;
            total += v - u1;
            if (topPairs.size() > 0) {
                diff[topPairs[0]] += u1 - u2;
            }
        }

        long long maxDiff = 0;
        for (int j = 0; j < m; j++) {
            maxDiff = max(maxDiff, diff[j]);
        }
        return total + maxDiff;
    }
};
