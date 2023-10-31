class Solution {
public:
    vector<int> findArray(vector<int>& pref) {
        for (int i = pref.size()-1; i; i--) {
            pref[i] = pref[i]^pref[i-1];
        }
        return pref;
    }
};
