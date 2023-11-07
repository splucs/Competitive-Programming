class Solution {
public:
    int eliminateMaximum(vector<int>& dist, vector<int>& speed) {
        int n = dist.size();

        // time[i] = time it takes for i-th monster to arrive.
        vector<int> time(n);
        for (int i = 0; i < n; i++) {
            time[i] = (dist[i]+speed[i]-1)/speed[i];
        }

        sort(time.begin(), time.end());
        for (int t = 0; t < n; t++) {
            if (t >= time[t]) {
                return t;
            }
        }
        return n;
    }
};
