/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem F. Final                                               */
/*                                                                */
/* Original idea        Yury Petrov                               */
/* Problem statement    Vitaly Aksenov                            */
/* Test set             Vitaly Aksenov                            */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author               Vitaly Aksenov                            */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;
import static ru.ifmo.testlib.Outcome.Type.*;

public class Check implements Checker {
    public Outcome outcome(Outcome.Type type, final String format, final Object... args) {
        return new Outcome(type, String.format(format, args));
    }

    public final String wi = "Wrong information";

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        String ja = ans.nextLine();
        String pa = ouf.nextLine();

        if (pa.equals(wi)) {
            if (!ja.equals(wi)) {
                return outcome(WA, "Contestant didn't find solution!");
            } else {
                return outcome(OK, "There isn't solution!");
            }
        }

        ouf.reset();

        int n = inf.nextInt();
        int x = inf.nextInt();
        int k = inf.nextInt();
        int d = inf.nextInt();
        int b = x + 1;
        int different = 0;
        for (int i = 0; i < n; i++) {
            int a = ouf.nextInt();

            x = x - a;
            if (x < 0) {
                return outcome(WA, "Contestant use more points, that have given!");
            }

            if (a < 0) {
                return outcome(WA, "%d-th driver points are negative: %d", i + 1, a);
            }

            if (b < a) {
                return outcome(WA, "Contestants scoreboard isn't sorted! %d-th driver points are less than have next one!", i);
            }

            if (a != b) {
                different = different + 1;
            }

            if (i == k - 1 && d != different) {
                return outcome(WA, "Contestants scoreboard doesn't satisfy conditions -lll only %d different in the first %d!", different, k);
            }

            b = a;
        }

        if (x != 0) {
            return outcome(WA, "Contestant use less points, that have given! He has %d more!", x);
        }

        if (ja.equals(wi)) {
            return outcome(FAIL, "Contestant build right scoreboard, but we can't!");
        }

        return outcome(OK, "");
    }
}

