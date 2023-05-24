class Solution {
public:
    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        int n = nums1.size();
        vector<pair<int, int> > pairs(n);
        for(int i = 0; i < n; i++) {
            pairs[i] = make_pair(nums2[i], nums1[i]);
        }
        sort(pairs.begin(), pairs.end());

        long long sum = 0, ans = 0;
        priority_queue<int, vector<int>, greater<int> > topk;
        for (int i = n-1; i >= 0; i--) {
            int val = pairs[i].second;
            sum += val;
            topk.push(val);

            if (topk.size() > k) {
                val = topk.top();
                sum -= val;
                topk.pop();
            }

            if (topk.size() == k) {
                long long cur = pairs[i].first*sum;
                if (cur > ans) ans = cur;
            }
        }
        return ans;
    }
};

