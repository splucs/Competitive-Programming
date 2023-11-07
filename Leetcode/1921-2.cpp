class Solution {
public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        int n = dist.size();

        // time[i] = time it takes for i-th monster to arrive.
        vector<int> time(n);
        int maxTime = 0;
        for (int i = 0; i < n; i++) {
            time[i] = (dist[i]+speed[i]-1)/speed[i];

            if (maxTime < time[i]) {
                maxTime = time[i];
            }
        }

        // bucket sort
        vector<int> bucket(maxTime+1, 0);
        for (int t : time) bucket[t]++;
        time.clear();
        for (int t = 0; t <= maxTime; t++) {
            int cnt = bucket[t];
            for (int i = 0; i < cnt; i++) {
                time.push_back(t);
            }
        }

        for (int t = 0; t < n; t++) {
            if (t >= time[t]) {
                return t;
            }
        }
        return n;
    }
};
