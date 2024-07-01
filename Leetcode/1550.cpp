class Solution {
public:
    bool threeConsecutiveOdds(vector<int>& arr) {
        int cnt = 0;
        for (int num : arr) {
            if (num & 1) {
                cnt++;
            } else {
                cnt = 0;
            }
            if (cnt >= 3) return true;
        }
        return false;
    }
};
