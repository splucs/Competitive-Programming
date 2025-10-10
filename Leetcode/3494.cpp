class Solution {
public:
    long long minTime(vector<int>& skill, vector<int>& mana) {
        mana.insert(mana.begin(), 0);
        int n = skill.size();
        int m = mana.size();
        long long ans = 0, offset = 0;
        for (int j = 1; j < m; j++) {
            long long t = offset;
            long long p = offset;
            for (int i = 0; i < n; i++) {
                p += skill[i]*(long long)mana[j-1];
                if (t < p) {
                    offset += p-t;
                    t = p;
                }
                t += skill[i]*(long long)mana[j];
            }
            ans = max(ans, t);
        }
        return ans;
    }
};
