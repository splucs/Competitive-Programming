/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem B. Battleship                                          */
/*                                                                */
/* Original idea        Anton Bannykh                             */
/* Problem statement    Anton Bannykh                             */
/* Test set             Anton Bannykh                             */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author               Anton Bannykh                             */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;
import static ru.ifmo.testlib.Outcome.Type.*;
import java.math.BigInteger;

public class Check implements Checker {
    public Outcome outcome(Outcome.Type type, final String format, final Object... args) {
        return new Outcome(type, String.format(format, args));
    }

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int li, lj;
        li = lj = -1;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (inf.nextInt() == 100) {
                    li = i;
                    lj = j;
                }
            }
        }

        char[][] field = new char[10][];
        for (int i = 0; i < field.length; ++i) {
            field[i] = ouf.nextLine().trim().toCharArray();
            boolean wrongFormat = field[i].length != 10;
            for (char c : field[i]) {
                wrongFormat |= ".#".indexOf(c) < 0;
            }
            if (wrongFormat) {
                return outcome(WA, "Wrong output format at line #%d: %s", i + 1, new String(field[i]));
            }
        }


        boolean[][] u = new boolean[10][10];

        int[] count = {4, 3, 2, 1};
        int totalShipNumber = 0;

        for (int i = 0; i < u.length; ++i) {
            for (int j = 0; j < u[i].length; ++j) {
                if (!u[i][j] && field[i][j] == '#') {
                    minI = maxI = i;
                    minJ = maxJ = j;
                    dfs(i, j, field, u);
                    int di = maxI - minI + 1;
                    int dj = maxJ - minJ + 1;
                    if (di != 1 && dj != 1 || di + dj > 5) {
                        return outcome(WA, "Strange ship found at (%d, %d)", i + 1, j + 1);
                    }
                    --count[di + dj - 2];
                    if (count[di + dj - 2] < 0) {
                        return outcome(WA, "Too many " + (di + dj - 1) + "-cell ships");
                    }
                    ++totalShipNumber;
                }
            }
        }

        if (totalShipNumber != 10) {
            return outcome(WA, "Only %d ships found", totalShipNumber);
        }

        if (field[li][lj] == '#') {
            return outcome(OK, "Well done!");
        } else {
            return outcome(WA, "No ship at the last move point");
        }
    }


    int minI, maxI, minJ, maxJ;

    void dfs(int i, int j, char[][] field, boolean[][] u) {
        minI = Math.min(i, minI);
        maxI = Math.max(i, maxI);
        minJ = Math.min(j, minJ);
        maxJ = Math.max(j, maxJ);

        u[i][j] = true;

        for (int di = -1; di <= 1; ++di) {
            for (int dj = -1; dj <= 1; ++dj) {
                int ti = i + di;
                int tj = j + dj;
                if (0 <= ti && ti < field.length && 0 <= tj && tj < field[ti].length && !u[ti][tj] && field[ti][tj] == '#') {
                    dfs(ti, tj, field, u);
                }
            }
        }
    }

}

