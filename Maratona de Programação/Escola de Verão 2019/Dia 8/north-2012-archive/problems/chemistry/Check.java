/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem C. Chemistry                                           */
/*                                                                */
/* Original idea        Maxim Buzdalov                            */
/* Problem statement    Anton Akhi                                */
/* Test set             Maxim Buzdalov                            */
/******************************************************************/
/* Checker                                                        */
/*                                                                */
/* Author               Maxim Buzdalov                            */
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
        BigInteger ja = ans.nextBigInteger();
        BigInteger pa = ouf.nextBigInteger();

        if (!ja.equals(pa)) {
            return outcome(WA, "Expected %d, found %d", ja, pa);
        }
        return outcome(OK, "%d", ja);
    }
}

