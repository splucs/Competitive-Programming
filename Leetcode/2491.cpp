class Solution {
public:
    long long dividePlayers(vector<int>& skill) {
        int sum = 0;
        int n = skill.size();
        for (int i = 0; i < n; i++) {
            sum += skill[i];
        }
        if ((sum<<1) % n != 0) {
            return -1;
        }
        int teamSkill = (sum<<1)/n;

        sort(skill.begin(), skill.end());
        long long ans = 0;
        for (int i = 0, j = n-1; i < j; i++, j--) {
            if (skill[i] + skill[j] != teamSkill) {
                return -1;
            }
            ans += skill[i]*skill[j];
        }
        return ans;
    }
};
