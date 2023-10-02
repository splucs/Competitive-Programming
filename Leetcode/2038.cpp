class Solution {
public:
    bool winnerOfGame(string colors) {
        int aStreak = 0, bStreak = 0;
        int aRemovable = 0, bRemovable = 0;
        for (char c : colors) {
            if (c == 'A') {
                bStreak = 0;
                aStreak++;
                if (aStreak >= 3) aRemovable++;
            } else {
                aStreak = 0;
                bStreak++;
                if (bStreak >= 3) bRemovable++;
            }
        }
        return aRemovable > bRemovable;
    }
};
