class Solution {
public:
    double new21Game(int n, int k, int maxPts) {
        vector<double> p(n+1);
        double sum = 0.0;
        for (int i = n; i >= 0; i--) {
            if (i >= k) p[i] = 1;
            else p[i] = sum/maxPts;

            sum += p[i];
            if (i+maxPts <= n) {
                sum -= p[i+maxPts];
            }
        }
        return p[0];
    }
};
