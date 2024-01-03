class Solution {
public:
    int numberOfBeams(vector<string>& bank) {
        int prev = 0;
        int ans = 0;
        for (string &row : bank) {
            int devices = 0;
            for (char c : row) {
                if (c == '1') devices++;
            }
            if (devices == 0) {
                continue;
            }
            ans += devices*prev;
            prev = devices;
        }
        return ans;
    }
};
