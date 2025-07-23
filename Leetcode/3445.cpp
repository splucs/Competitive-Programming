#define INF 0x3f3f3f3f
class Solution {
public:
    int maxDifference(string s, int k) {
        int n = s.size();
        vector<vector<vector<int>>> minDiff(n);
        int ans = -INF;
        for (int a = 0; a < 5; a++) for (int b = 0; b < 5; b++) {
            int fa = 0, fb = 0, lasta = -1, lastb = -1;
            vector<vector<int>> diff = {{0, INF}, {INF, INF}};
            for (int i = 0; i < n; i++) {
                if (s[i]-'0' == a) {
                    fa++;
                    lasta = i;
                }
                if (s[i]-'0' == b) {
                    fb++;
                    lastb = i;
                }
                int pa = fa & 1;
                int pb = fb & 1;
                minDiff[i] = diff;
                diff[pa][pb] = min(diff[pa][pb], fa - fb);

                int j = min(i-k+1, min(lasta, lastb));
                if (j >= 0) {
                    ans = max(ans, fa - fb - minDiff[j][pa^1][pb]);
                }
            }
        }
        return ans;
    }
};
