class Solution {
private:
    vector<int> status, candies;
    vector<vector<int>> keys, containedBoxes;
    vector<bool> hasBox, hasKey;

    int ans = 0;
    void visitBox(int box) {
        if (!hasBox[box]) {
            return;
        }
        if (status[box] == 0 && !hasKey[box]) {
            return;
        }
        if (candies[box] == 0) {
            return;
        }

        status[box] = 1;
        ans += candies[box];
        candies[box] = 0;

        for (int key : keys[box]) {
            hasKey[key] = true;
            visitBox(key);
        }

        for (int box : containedBoxes[box]) {
            hasBox[box] = true;
            visitBox(box);
        }
    }
public:
    int maxCandies(vector<int>& _status, vector<int>& _candies, vector<vector<int>>& _keys, vector<vector<int>>& _containedBoxes, vector<int>& initialBoxes) {
        status.swap(_status);
        candies.swap(_candies);
        keys.swap(_keys);
        containedBoxes.swap(_containedBoxes);
        hasKey.assign(status.size(), false);
        hasBox.assign(status.size(), false);

        for (int box : initialBoxes) {
            hasBox[box] = true;
        }
        for (int box : initialBoxes) {
            visitBox(box);
        }
        return ans;
    }
};
