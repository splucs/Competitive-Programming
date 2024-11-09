class Solution {
public:
    string largestNumber(vector<int>& nums) {
        // Corner case
        bool allZeroes = true;
        for (int num : nums) {
            if (num != 0) {
                allZeroes = false;
                break;
            }
        }
        if (allZeroes) {
            return "0";
        }

        vector<string> numsStr;
        numsStr.reserve(nums.size());
        for (int num : nums) {
            numsStr.push_back(to_string(num));
        }
        sort(numsStr.begin(), numsStr.end(), [&](const string& a, const string& b) {
            string ab = a + b;
            string ba = b + a;
            return ba < ab;
        });
        string ans = "";
        for (const string& numStr : numsStr) {
            ans += numStr;
        }
        return ans;
    }
};
