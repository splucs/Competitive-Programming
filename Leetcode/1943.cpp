class Solution {
public:
    vector<vector<long long>> splitPainting(vector<vector<int>>& segments) {
        map<int, long long> delta;
        for (const vector<int>& segment : segments) {
            int st = segment[0], en = segment[1], mix = segment[2];
            delta[st] += mix;
            delta[en] -= mix;
        }

        long long sum = 0;
        int lastPos = 0;
        vector<vector<long long>> ans;
        for (auto entry : delta) {
            int pos = entry.first;
            long long mix = entry.second;
            if (sum != 0) {
                ans.push_back({lastPos, pos, sum});
            }
            lastPos = pos;
            sum += mix;
        }
        return ans;
    }
};
