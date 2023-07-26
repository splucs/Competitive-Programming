class Solution {
private:
    double calcTime(vector<int>& dist, int speed) {
        int n = dist.size();
        double time = 0;
        for (int i = 0; i < n-1; i++) {
            time += dist[i]/speed;
            if (dist[i]%speed) time += 1;
        }
        time += dist[n-1]*1.0/speed;
        return time;
    }
public:
    int minSpeedOnTime(vector<int>& dist, double hour) {
        int n = dist.size();
        if (hour <= n-1) {
            return -1;
        }

        int hi = 1e7;
        int lo = 0;
        while (hi > lo+1) {
            int mid = (hi+lo)>>1;
            if (hour >= calcTime(dist, mid)) hi = mid;
            else lo = mid;
        }
        return hi;
    }
};
