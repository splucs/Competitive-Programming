class Solution {
public:
    int maxTwoEvents(vector<vector<int>>& events) {
        sort(events.begin(), events.end());
        priority_queue<pair<int, int>> pq;
        int maxPrev = 0, ans = 0;
        for (const vector<int> event : events) {
            int st = event[0], en = event[1], val = event[2];
            while(!pq.empty() && -pq.top().first < st) {
                maxPrev = max(maxPrev, pq.top().second);
                pq.pop();
            }
            ans = max(ans, maxPrev + val);
            pq.push(make_pair(-en, val));
        }
        return ans;
    }
};
