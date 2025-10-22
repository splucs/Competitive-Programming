class Solution {
public:
    int finalValueAfterOperations(vector<string>& operations) {
        int ans = 0;
        for (const string& op : operations) {
            if (op[1] == '+') {
                ans++;
            } else {
                ans--;
            }
        }
        return ans;
    }
};
