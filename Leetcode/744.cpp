class Solution {
public:
    char nextGreatestLetter(vector<char>& letters, char target) {
        // low always point to <= target, hi always point to > target
        int lo = -1, hi = letters.size();

        // find the point were lo + 1 == hi
        while(hi > lo + 1) {
            int mid = (lo+hi)>>1;
            if (letters[mid] > target) hi = mid;
            else lo = mid;
        }

        // answer is pointed by hi
        if (hi >= letters.size()) return letters[0];
        return letters[hi];
    }
};
