/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem G. Grid                                                */
/*                                                                */
/* Original idea        Yury Petrov                               */
/* Problem statement    Yury Petrov                               */
/* Test set             Yury Petrov                               */
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
        int x1 = ouf.nextInt();
        int x2 = ouf.nextInt();
        int dx = ouf.nextInt();
        int y1 = ouf.nextInt();
        int y2 = ouf.nextInt();
        int dy = ouf.nextInt();
        if (x1 > x2) {
            return outcome(WA, "(x1 = %d) > (x2 = %d)", x1, x2);
        }
        if (y1 > y2) {
            return outcome(WA, "(y1 = %d) > (y2 = %d)", y1, y2);
        }
        if (dx <= 0) {
            return outcome(WA, "(dx = %d) <= 0", dx);
        }
        if (dy <= 0) {
            return outcome(WA, "(dy = %d) <= 0", dy);
        }
        if ((x2 - x1) % dx != 0) {
            return outcome(WA, "(x2 = %d) - (x1 = %d) = %d is not divisible by (dx = %d)", x2, x1, x2 - x1, dx);
        }
        if ((y2 - y1) % dy != 0) {
            return outcome(WA, "(y2 = %d) - (y1 = %d) = %d is not divisible by (dy = %d)", y2, y1, y2 - y1, dy);
        }

        int n = inf.nextInt();
        boolean[] xs = new boolean[(x2 - x1) / dx + 1];
        boolean[] ys = new boolean[(y2 - y1) / dy + 1];
        int minx = Integer.MAX_VALUE, maxx = -Integer.MAX_VALUE;
        int miny = Integer.MAX_VALUE, maxy = -Integer.MAX_VALUE;
        for (int i = 0; i < n; i++) {
            int x = inf.nextInt();
            int y = inf.nextInt();
            minx = Math.min(minx, x);
            maxx = Math.max(maxx, x);
            miny = Math.min(miny, y);
            maxy = Math.max(maxy, y);
            if (!check(dx, x1, x2, xs, x) & !check(dy, y1, y2, ys, y)) { // No short-circuit!
                return outcome(WA, "Point (%d, %d) s neither on horizontal, nor on vertical line", x, y);
            }
        }

        if (minx == maxx) {
            if (x1 <= minx && maxx <= x2 && (minx - x1) % dx == 0) {
                return outcome(WA, "Line (x = %d) equals to Mike's line", minx);
            }
        } else {
            for (int i = 0; i < xs.length; i++) {
                if (!xs[i]) {
                    return outcome(WA, "No intersection for line (x = %d)", x1 + i * dx);
                }
            }
        }

        if (miny == maxy) {
            if (y1 <= miny && maxy <= y2 && (miny - y1) % dy == 0) {
                return outcome(WA, "Line (y = %d) equals to Mike's line", miny);
            }
        } else {
            for (int i = 0; i < ys.length; i++) {
                if (!ys[i]) {
                    return outcome(WA, "No intersection for line (y = %d)", y1 + i * dy);
                }
            }

        }

        return outcome(OK, "");
    }

    private boolean check(int dv, int v1, int v2, boolean[] vs, int v) {
        if (v1 <= v && v <= v2 && (v - v1) % dv == 0) {
            vs[(v - v1) / dv] = true;
            return true;
        }
        return false;
    }
}

