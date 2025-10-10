class Solution {
public:
    string largestGoodInteger(string num) {
        int largest = -1;
        int ans = num.size();
        for (int i = 2; i < (int)num.size(); i++) {
            if (num[i] != num[i-2] || num[i] != num[i-1]) {
                continue;
            }
            if (largest < num[i]-'0') {
                largest = num[i]-'0';
                ans = i-2;
            }
        }
        return num.substr(ans, 3);
    }
};
