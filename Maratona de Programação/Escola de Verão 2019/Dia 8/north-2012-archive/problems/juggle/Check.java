/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem J. Juggle with Criteria                                */
/*                                                                */
/* Original idea        Mikhail Dvorkin                           */
/* Problem statement    Mikhail Dvorkin                           */
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
	@Override
	public Outcome test(InStream inf, InStream ouf, InStream ans) {
        int n = inf.nextInt();
        int l = inf.nextInt();
        for (int i = 0; i < n; i++) {
            char[] criteria = inf.nextToken().toCharArray();
            boolean ja = checkPair(FAIL, ans, i + 1, criteria, l);
            boolean pa = checkPair(WA, ouf, i + 1, criteria, l);
            if (ja != pa) {
                if (!pa) {
                    return outcome(WA, "Subtest %d: Participant not found solution", i + 1);
                }
                return outcome(FAIL, "Subtest %d: Participant found solution, while jury does not", i + 1);
            }
        }
		return outcome(OK, "n = %d, length = %d", n, l);
	}

    private boolean checkPair(final Outcome.Type type, final InStream ouf, final int subtest, final char[] criteria, final int l) {
        String exists = ouf.nextLine();
        if ("Not exists".equalsIgnoreCase(exists)) {
            return false;
        }
        if (!"Exists".equalsIgnoreCase(exists)) {
            throw outcome(type, "Subtest %d:, 'Exists' or 'Not exists' expected, '%s' found", subtest, exists);
        }
        int[][] p = new int[2][l];
        int[][] c = new int[2][];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < l; j++) {
                p[i][j] = ouf.nextInt();
            }
            checkPermutation(type, subtest, p[i]);
            c[i] = calculateCriteria(p[i]);
        }
        ouf.nextLine();
        for (int i = 0; i < criteria.length; i++) {
            char sign = "<=>".charAt(Integer.compare(c[0][i], c[1][i]) + 1);
            if (sign != criteria[i]) {
                char criterion = (char) ('a' + i);
                throw outcome(type, "Subtest %d: Expected %s(p)%s%s(q), found %s(p)=%d, %s(q)=%d",
                        subtest, criterion, criteria[i], criterion, criterion, c[0][i], criterion, c[1][i]);
            }
        }
        return true;
    }

    private static void checkPermutation(final Outcome.Type type, final int subtest, int[] p) {
		int n = p.length;
		boolean[] mark = new boolean[n + 1];
		for (int i = 0; i < n; i++) {
			if (p[i] < 1 || p[i] > n) {
                throw outcome(type, "Subtest %d: Number out of the range 1..N: %d", subtest, p[i]);
			}
			if (mark[p[i]]) {
				throw outcome(type, "Subtest %d: Permutation contains duplicate number: %d", subtest, p[i]);
			}
			mark[p[i]] = true;
		}
	}

    private static Outcome outcome(final Outcome.Type type, final String format, final Object... args) {
        return new Outcome(type, String.format(format, args));
    }

    public static int[] calculateCriteria(int[] p) {
		int n = p.length;
		int[] c = new int[5];
		int[] giSeq = new int[n];
		int giStr = 0;
		for (int i = 0; i < n; i++) {
			giSeq[i] = 1;
			for (int j = 0; j < i; j++) {
				if (p[j] > p[i]) {
					c[0]++;
				} else {
					giSeq[i] = Math.max(giSeq[i], giSeq[j] + 1);
				}
			}
			if (i > 0 && p[i - 1] > p[i]) {
				c[1]++;
			}
			c[2] = Math.max(c[2], giSeq[i]);
			if (i == 0 || p[i - 1] > p[i]) {
				giStr = 1;
			} else {
				giStr++;
			}
			c[3] = Math.max(c[3], giStr);
			if (p[i] == i + 1) {
				c[4]++;
			}
		}
		return c;
	}
}

