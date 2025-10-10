#define MAX_BITS 32
class Solution {
public:
    int subarrayBitwiseORs(vector<int>& arr) {
        int n = arr.size();
        vector<vector<int>> last(n, vector<int>(MAX_BITS, -1));
        unordered_set<int> ans;

        for (int i = 0; i < n; i++) {
            for (int b = 0; b < MAX_BITS; b++) {
                if ((1<<b) & arr[i]) {
                    last[i][b] = i;
                } else if (i > 0) {
                    last[i][b] = last[i-1][b];
                }
            }

            for (int j = i, mask = 0; j != -1;) {
                mask |= arr[j];
                ans.insert(mask);

                int nxt = -1;
                for (int b = 0; b < MAX_BITS; b++) {
                    if ((1<<b) & mask) {
                        continue;
                    }
                    nxt = max(nxt, last[j][b]);
                }
                j = nxt;
            }
        }

        return ans.size();
    }
};
