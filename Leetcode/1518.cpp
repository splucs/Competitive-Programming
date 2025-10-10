class Solution {
public:
    int numWaterBottles(int numBottles, int numExchange) {
        int ans = numBottles;
        while (numBottles >= numExchange) {
            int newBottles = numBottles/numExchange;
            ans += newBottles;
            numBottles = (numBottles % numExchange) + newBottles;
        }
        return ans;
    }
};
