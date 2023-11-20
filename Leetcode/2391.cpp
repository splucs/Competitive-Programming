class Solution {
public:
    int garbageCollection(vector<string>& garbage, vector<int>& travel) {
        int n = garbage.size();
        int sinceM = 0, sinceP = 0, sinceG = 0;
        int ans = 0;
        for (int i = 0; i < n; i++) {
            ans += garbage[i].size();
            for (char c : garbage[i]) {
                switch (c) {
                case 'M':
                    ans += sinceM;
                    sinceM = 0;
                    break;
                case 'P':
                    ans += sinceP;
                    sinceP = 0;
                    break;
                case 'G':
                    ans += sinceG;
                    sinceG = 0;
                    break;
                }
            }
            if (i+1 < n) {
                sinceM += travel[i];
                sinceP += travel[i];
                sinceG += travel[i];
            }
        }
        return ans;
    }
};
