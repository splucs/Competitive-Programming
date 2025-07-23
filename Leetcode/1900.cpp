#define INF 0x3f3f3f3f

class Solution {
private:
    vector<vector<vector<vector<int>>>> memo = vector<vector<vector<vector<int>>>>(29, vector<vector<vector<int>>>(29, vector<vector<int>>(29)));
public:
    vector<int> earliestAndLatest(int n, int firstPlayer, int secondPlayer) {
        if (secondPlayer < firstPlayer) {
            swap(firstPlayer, secondPlayer);
        }

        vector<int>& ans = memo[n][firstPlayer][secondPlayer];
        if (!ans.empty()) {
            return ans;
        }
        if (firstPlayer + secondPlayer - 1 == n) {
            return ans = {1, 1};
        }

        int numMatches = n/2, numWinners = (n+1)/2;
        int maxMask = 1 << numMatches;
        ans = {INF, -INF};
        vector<int> winners(numWinners);
        for (int mask = 0; mask < maxMask; mask++) {
            int it = 0, jt = numWinners;
            for (int i = 1; i <= numMatches; i++) {
                int j = n-i+1;
                if (mask & (1<<(i-1))) {
                    winners[it++] = i;
                } else {
                    winners[--jt] = j;
                }
            }
            if (n & 1) {
                winners[it++] = n/2 + 1;
            }

            int newFirst = -1, newSecond = -1;
            for (int i = 0; i < numWinners; i++) {
                if (winners[i] == firstPlayer) {
                    newFirst = i+1;
                }
                if (winners[i] == secondPlayer) {
                    newSecond = i+1;
                }
            }

            // first and second have to be among winners
            if (newFirst == -1 || newSecond == -1) {
                continue;
            }

            vector<int> cur = earliestAndLatest(numWinners, newFirst, newSecond);
            ans[0] = min(ans[0], 1 + cur[0]);
            ans[1] = max(ans[1], 1 + cur[1]);
        }
        return ans;
    }
};
