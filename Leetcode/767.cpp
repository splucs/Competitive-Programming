class Solution {
public:
    string reorganizeString(string s) {
        vector<int> cnt(256, 0);
        for (char c : s) cnt[c]++;

        priority_queue<pair<int, char>> pq;
        for (char c = 'a'; c <= 'z'; c++) {
            if (cnt[c] > 0) {
                pq.push(make_pair(cnt[c], c));
            }
        }

        pair<int, char> last = make_pair(0, 0);
        string ans;
        while (!pq.empty()) {
            pair<int, char> cur = pq.top();
            pq.pop();
            ans.push_back(cur.second);
            cur.first--;
            if (last.first > 0) {
                pq.push(last);
            }
            last = cur;
        }
        if (last.first > 0) return "";
        return ans;
    }
};
