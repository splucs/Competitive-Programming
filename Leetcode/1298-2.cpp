#define canProcessBox(box) (hasBox[box] && (status[box] == 1 || hasKey[box]) && candies[box] > 0)
class Solution {
public:
    int maxCandies(vector<int>& status, vector<int>& candies, vector<vector<int>>& keys, vector<vector<int>>& containedBoxes, vector<int>& initialBoxes) {
        int n = status.size();
        vector<bool> hasKey(n, false), hasBox(n, false);

        vector<int> q;
        q.reserve(n);
        int ans = 0;
        for (int box : initialBoxes) {
            hasBox[box] = true;
            if (canProcessBox(box)) {
                q.push_back(box);
                ans += candies[box];
                candies[box] = 0;
            }
        }

        for (int t = 0; t < (int)q.size(); t++) {
            int box = q[t];
            for (int key : keys[box]) {
                hasKey[key] = true;
                if (canProcessBox(key)) {
                    q.push_back(key);
                    ans += candies[key];
                    candies[key] = 0;
                }
            }
            for (int cbox : containedBoxes[box]) {
                hasBox[cbox] = true;
                if (canProcessBox(cbox)) {
                    q.push_back(cbox);
                    ans += candies[cbox];
                    candies[cbox] = 0;
                }
            }
        }
        return ans;
    }
};
