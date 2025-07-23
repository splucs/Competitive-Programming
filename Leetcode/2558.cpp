class Solution {
public:
    long long pickGifts(vector<int>& gifts, int k) {
        priority_queue<int> pq(gifts.begin(), gifts.end());
        while (k --> 0) {
            int gift = pq.top(); pq.pop();
            gift = sqrt(gift);
            pq.push(gift);
        }
        long long ans = 0;
        while (!pq.empty()) {
            ans += pq.top(); pq.pop();
        }
        return ans;
    }
};
