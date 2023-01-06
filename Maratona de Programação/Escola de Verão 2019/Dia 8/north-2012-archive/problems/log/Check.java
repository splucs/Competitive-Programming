/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem L. Log Analysis                                        */
/*                                                                */
/* Original idea        Georgiy Korneev                           */
/* Problem statement    Georgiy Korneev                           */
/* Test set             Georgiy Korneev                           */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author               Georgiy Korneev                           */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;
import static ru.ifmo.testlib.Outcome.Type.*;

public class Check implements Checker {
    public Outcome outcome(Outcome.Type type, final String format, final Object... args) {
        return new Outcome(type, String.format(format, args));
    }

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int index = 0;
        while (!ans.seekEoF()) {
            ++index;
            int ja = ans.nextInt();
            int pa = ouf.nextInt();

            if (ja != pa) {
                return outcome(WA, "%d number differs: expected %d, found %d", index, ja, pa);
            }
        }
        return outcome(OK, "%d numbers", index);
    }
}
