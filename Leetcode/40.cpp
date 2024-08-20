class Solution {
private:
    vector<int> candUniq, candFreq;
    vector<vector<bool>> deadEnd;
    vector<vector<int>> ans;
    vector<int> cur;

    bool recurse(int i, int t) {
        if (t == 0) {
            ans.push_back(cur);
            return false;
        }
        if (i == -1) {
            return true;
        }

        if (deadEnd[i][t]) {
            return true;
        }

        deadEnd[i][t] = true;
        int cnt, newt;
        for (cnt = 0, newt = t; cnt <= candFreq[i] && newt >= 0; cnt++) {
            if (!recurse(i-1, newt)) {
                deadEnd[i][t] = false;
            }
            newt -= candUniq[i];
            cur.push_back(candUniq[i]);
        }
        while (cnt --> 0) {
            cur.pop_back();
        }
        return deadEnd[i][t];
    }
public:
    vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
        vector<int> freq(target+1, 0);
        for (int cand : candidates) {
            if (cand <= target) {
                freq[cand]++;
            }
        }
        for (int f = 0; f <= target; f++) {
            if (freq[f] > 0) {
                candUniq.push_back(f);
                candFreq.push_back(freq[f]);
            }
        }
        deadEnd.assign(candUniq.size(), vector<bool>(target+1, false));

        recurse(candUniq.size()-1, target);
        return ans;
    }
};
