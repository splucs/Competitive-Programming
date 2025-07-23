class Solution {
private:
    inline int digitSum(int i) {
        int sum = 0;
        for(; i > 0; i /= 10) {
            sum += i%10;
        }
        return sum;
    }
public:
    int countLargestGroup(int n) {
        vector<int> groupSize(40, 0);
        for (int i = 1; i <= n; i++) {
            groupSize[digitSum(i)]++;
        }
        int ans = 0;
        int maxG = 0;
        for (int g : groupSize) {
            if (maxG < g) {
                maxG = g;
                ans = 0;
            }
            if (maxG == g) {
                ans++;
            }
        }
        return ans;
    }
};
