class Solution {
public:
    set<pair<int, int> > topk, rest;
    long long topkSum;
    int sz;

    long long maxScore(vector<int>& nums1, vector<int>& nums2, int k) {
        sz = k;
        long long ans = 0;

        vector<int> idx = indexesSortedByNums2(nums2);
        addNums1(nums1);

        for (int i : idx) {
            if (topk.size() < k) break;
            long long cur = nums2[i]*topkSum;
            if (cur > ans) ans = cur;
            eraseIndex(nums1, i);
        }
        return ans;
    }
    void addNums1(vector<int>& nums1) {
        int n = nums1.size();
        topkSum = 0;
        for(int i = 0; i < n; i++) {
            rest.insert(make_pair(nums1[i], i));
        }
        while (topk.size() < sz) {
            pair<int, int> p = *rest.rbegin();
            rest.erase(p);
            topk.insert(p);
            topkSum += p.first;
        }
    }
    void eraseIndex(vector<int>& nums1, int i) {
        pair<int, int> p = make_pair(nums1[i], i);
        if (rest.count(p)) {
            rest.erase(p);
        } else {
            topk.erase(p);
            topkSum -= p.first;

            if (!rest.empty()) {
                p = *rest.rbegin();
                rest.erase(p);
                topk.insert(p);
                topkSum += p.first;
            }
        }
    }
    vector<int> indexesSortedByNums2(vector<int>& nums2) {
        int n = nums2.size();
        vector<int> idx(n);
        for (int i = 0; i < n; i++) {
            idx[i] = i;
        }
        sort(idx.begin(), idx.end(), [&](int i, int j){
            return nums2[i] < nums2[j];
        });
        return idx;
    }
};
