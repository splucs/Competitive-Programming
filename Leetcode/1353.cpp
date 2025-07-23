class Solution {
public:
    int maxEvents(vector<vector<int>>& events) {
        int maxn = 1;
        for (vector<int>& event : events) {
            int en = event[1];
            maxn = max(maxn, en);
        }
        vector<vector<int>> ends(maxn+1);
        for (vector<int>& event : events) {
            int st = event[0], en = event[1];
            ends[st].push_back(en);
        }

        int ans = 0;
        priority_queue<int, vector<int>, greater<int>> curEnds;
        for (int d = 1; d <= maxn; d++) {
            while(!curEnds.empty() && curEnds.top() < d) {
                curEnds.pop();
            }
            for (int en : ends[d]) {
                curEnds.push(en);
            }
            if (!curEnds.empty()) {
                curEnds.pop();
                ans++;
            }
        }
        return ans;
    }
};
