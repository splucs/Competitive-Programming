class Solution {
public:
    string longestDiverseString(int a, int b, int c) {
        vector<pair<int, char>> cnt = {{a, 'a'}, {b, 'b'}, {c, 'c'}};
        sort(cnt.begin(), cnt.end());
        string ans = "";
        while (cnt[2].first > cnt[1].first) {
            cnt[2].first--;
            ans += cnt[2].second; 
            if (cnt[2].first > 0) {
                cnt[2].first--;
                ans += cnt[2].second; 
            }
            if (cnt[1].first == 0) {
                return ans;
            }
            cnt[1].first--;
            ans += cnt[1].second; 
            if (cnt[1].first < cnt[0].first) {
                swap(cnt[0], cnt[1]);
            }
        }
        if (cnt[1].first > cnt[2].first) {
            cnt[1].first--;
            ans += cnt[1].second; 
        }
        while (cnt[1].first > cnt[0].first) {
            cnt[2].first--;
            cnt[1].first--;
            ans += cnt[2].second; 
            ans += cnt[1].second; 
        }
        while (cnt[0].first > 0) {
            cnt[2].first--;
            cnt[1].first--;
            cnt[0].first--;
            ans += cnt[2].second; 
            ans += cnt[1].second; 
            ans += cnt[0].second; 
        }
        return ans;
    }
};
