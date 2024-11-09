class Solution {
public:
    long long maxKelements(vector<int>& nums, int k) {
        priority_queue<int> pq(nums.begin(), nums.end());
        long long score = 0;
        while (k --> 0) {
            int top = pq.top();
            pq.pop();
            score += top;
            top = (top+2)/3;
            pq.push(top);
        }
        return score;
    }
};
