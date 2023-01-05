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
/* Tests                                                          */
/*                                                                */
/* Author               Yury Petrov                               */
/******************************************************************/

import java.io.FileNotFoundException;
import java.io.IOException;
import java.io.PrintWriter;
import java.util.*;

public class Tests {
    int testNo = 0;
    PrintWriter out;
    static PrintWriter descriptions;

    void beginTest(String description, Object... args) {
        ++testNo;
        descriptions.format("%02d: %s\n", testNo, String.format(description, args));
        descriptions.flush();
        try {
            out = new PrintWriter(String.format("tests/%02d", testNo));
        } catch (FileNotFoundException e) {
            throw new AssertionError(e);
        }
    }

    void endTest() {
        out.close();
        assert !out.checkError();
        out = null;
    }

    Random random = new Random(212343);

    private void test(int n, int sx, int sy, int dx, int dy, int x0, int y0, int x1, int y1) {
        List<int[]> points = new ArrayList<>();
        int x = x1, y = x1;
        for (int i = 0; i < n; i++) {
            int tx = dx - x % dx;
            int ty = dy - y % dy;
            if (tx < ty) {
                x += tx;
                y += tx;
            } else {
                x += ty;
                y += ty;
            }
            points.add(new int[]{x0 + x * sx, y0 + y * sy});
        }
        Collections.shuffle(points, random);
        writeTest(points.toArray(new int[0][]), "n=%d, sx=%d, sy=%, dx=%d, dy=%d, x0=%d, y0=%d, x1=%d, y1=%d", n, sx, sy, dx, dy, x0, y0, x1, y1);
    }

    private void writeTest(int[][] points, String format, Object... args) {
        beginTest(format, args);
        out.println(points.length);
        for (int[] point : points) {
            out.println(point[0] + " " + point[1]);
        }
        endTest();
    }

    public void run() throws IOException {
        testSample();

        test(7, 2, 1, 2, 3, 1, 2, 1, 0);
        test(7, -2, -1, 20, 30, 1000, 2300, 0, 13);
        test(3, 2, 1, 7, 5, 1, 0, 4, 3);
        test(3, 100, 2, 3, 12, 17, 12, 2, 3);

        test(3, 1, 0, 2, 3, 1, 2, 1, 0);
        test(3, 0, 2, 2, 3, 1, 2, 1, 0);

        test(4, 2, 1000000, 17, 5, 13, 3, 7, 3);
        test(4, 10000000, 1, 2, 2, 99, 1, 1, 1);
        test(17, -32, -77, 2, 3, 10000, 100000, 0, 2);
        test(30, 6, 12, 7, 3, 1, 1, 2, 1);
        test(128, -1, 3, 3, 1, 13012, 1, 1, 0);
        test(239, 1, 1, 4, 3, 1, 1, 3, 2);
        test(666, 1000, -1, 2, 3, 1, 7770, 1, 1);
        test(1000, 2, 8, 66, 3, 1, 1, 13, 1);
        test(1013, 5, 1, 1000, 3, 1, 1, 770, 2);
        test(7777, -239, 342, 2, 3, 3789001, 0, 1, 1);
        test(23900, -3, 1, 17, 88, 1213321, 0, 9, 8);
        test(100000, 2, -7, 2, 3, 1, 8000210, 1, 1);
        test(100000, 2, 1, 30, 33, 1, 0, 27, 3);
        test(100000, -5, -3, 2, 3, 1000000000, 1000000000, 1, 0);
        test(100000, 3, 5, 3, 2, 1, 3, 0, 3);

        test(100000, 0, 5, 10000000, 2, 1, 3, 0, 3);
        test(100000, 3, 0, 3, 100000000, 1, 3, 0, 3);
        test(100000, 0, -2, 100000000, 2, 1, 1000000000, 0, 3);
        test(100000, 100, 0, 3, 100000000, 1, 3, 0, 3);
    }

    private void testSample() {
        writeTest(new int[][]{{1, 1}, {5, 3}, {3, 2}, {9, 5}}, "Sample");
    }

    public static void main(String[] args) throws IOException {
        descriptions = new PrintWriter("tests/tests.lst");
        new Tests().run();
        descriptions.close();
    }
}

