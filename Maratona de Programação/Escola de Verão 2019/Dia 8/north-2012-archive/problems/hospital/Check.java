/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem H. Hospital                                            */
/*                                                                */
/* Original idea        Pavel Mavrin                              */
/* Problem statement    Pavel Mavrin                              */
/* Test set             Pavel Mavrin                              */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author               Pavel Mavrin                              */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.HashSet;
import java.util.Set;

import static ru.ifmo.testlib.Outcome.Type.*;

public class Check implements Checker {

    private static final int MAX = 1000000;
    private static final int NO_LIST = 10000;

    public Outcome outcome(Outcome.Type type, final String format, final Object... args) {
        return new Outcome(type, String.format(format, args));
    }

    static class Answer {
        int n1;
        int n2;
        int[] res1;
        Pair[] res2;
        boolean ok = true;
        String comment;

        Set<Integer> res1set = new HashSet<>();
        Set<Pair> res2set = new HashSet<>();

        Answer(InStream in) {
            n1 = in.nextInt();
            if (n1 > MAX) {
                ok = false;
                comment = "Number is too large, did not read: " + n1;
                return;
            }
            res1 = new int[n1];
            for (int i = 0; i < n1; i++) {
                res1[i] = in.nextInt();
                if (res1set.contains(res1[i])) {
                    ok = false;
                    comment = "Duplicate number: " + res1[i];
                    return;
                }
                res1set.add(res1[i]);
            }
            n2 = in.nextInt();
            if (n2 > MAX) {
                ok = false;
                comment = "Number is too large, did not read: " + n2;
                return;
            }
            if (n2 <= NO_LIST) {
                res2 = new Pair[n2];
                for (int i = 0; i < n2; i++) {
                    res2[i] = new Pair(in.nextInt(), in.nextInt());
                    if (res2set.contains(res2[i])) {
                        ok = false;
                        comment = "Duplicate pair: " + res2[i];
                        return;
                    }
                    res2set.add(res2[i]);
                }
            }
        }
    }

    static class Pair {
        int x;
        int y;

        public Pair(int x, int y) {
            this.x = Math.min(x, y);
            this.y = Math.max(x, y);
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;
            Pair pair = (Pair) o;
            return x == pair.x && y == pair.y;
        }

        @Override
        public int hashCode() {
            int result = x;
            result = 31 * result + y;
            return result;
        }

        @Override
        public String toString() {
            return "(" + x + ", " + y + ")";
        }
    }


    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        Answer pa = new Answer(ouf);
        Answer ja = new Answer(ans);
        if (!ja.ok) return outcome(FAIL, ja.comment);
        if (!pa.ok) return outcome(WA, pa.comment);

        for (int i : pa.res1) {
            if (!ja.res1set.contains(i)) return outcome(WA, "Nurse " + i + " should not be in list");
        }
        for (int i : ja.res1) {
            if (!pa.res1set.contains(i)) return outcome(WA, "Nurse " + i + " should be in list");
        }

        if (pa.n2 > NO_LIST || ja.n2 > NO_LIST) {
            if (pa.n2 != ja.n2) {
                return outcome(WA, "Wrong number of pairs");
            } else {
                return outcome(OK, "");
            }
        } else {
            for (Pair pair : pa.res2) {
                if (!ja.res2set.contains(pair)) return outcome(WA, "Pair " + pair + " should not be in list");
            }
            for (Pair pair : ja.res2) {
                if (!pa.res2set.contains(pair)) return outcome(WA, "Pair " + pair + " should be in list");
            }
        }
        return outcome(OK, "");
    }
}

