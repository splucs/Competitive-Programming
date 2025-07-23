class Solution {
public:
    int minOperations(vector<int>& nums, int k) {
        priority_queue<int, vector<int>, greater<int>> pq(nums.begin(), nums.end());
        int ans = 0;
        while(pq.size() >= 2 && pq.top() < k) {
            ans++;
            int x = pq.top(); pq.pop();
            int y = pq.top(); pq.pop();
            pq.push(min(min(min(x, y)*2, k) + max(x, y), k));
        }
        return ans;
    }
};
