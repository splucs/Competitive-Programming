#define INF 0x3f3f3f3f
class Solution {
public:
    int maximumEnergy(vector<int>& energy, int k) {
        int ans = -INF, n = energy.size();
        for (int i = n-1; i >= 0; i--) {
            if (i+k < n) {
                energy[i] += energy[i+k];
            }
            ans = max(ans, energy[i]);
        }
        return ans;
    }
};
