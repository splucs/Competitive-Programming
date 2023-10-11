class Solution {
public:
    vector<int> fullBloomFlowers(vector<vector<int>>& flowers, vector<int>& people) {
        vector<pair<int, int>> events;
        for (vector<int> &flower : flowers) {
            events.push_back(make_pair(flower[0], 1));
            events.push_back(make_pair(flower[1]+1, -1));
        }
        sort(events.begin(), events.end());

        int n = people.size();
        vector<int> idx(n);
        for (int i = 0; i < n; i++) idx[i] = i;
        sort(idx.begin(), idx.end(), [&](int i, int j) {
            return people[i] < people[j];
        });

        vector<int> ans(n);
        int bloomCount = 0;
        int evtCount = events.size();
        for (int it = 0, e = 0; it < n; it++) {
            int i = idx[it];
            int d = people[i];
            for (; e < evtCount && d >= events[e].first; e++) {
                bloomCount += events[e].second;
            }
            ans[i] = bloomCount;
        }

        return ans;
    }
};
