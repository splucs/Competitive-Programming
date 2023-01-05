/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem K. Kingdom Subdivision                                 */
/*                                                                */
/* Original idea        Andrew Stankevich                         */
/* Problem statement    Maxim Buzdalov                            */
/* Test set             Maxim Buzdalov                            */
/******************************************************************/
/* Tests                                                          */
/*                                                                */
/* Author               Maxim Buzdalov                            */
/******************************************************************/

import java.io.*;
import java.util.*;

public class Tests {
    private static File dir = new File("tests");
    private int curTest = 1;
    private Random random = new Random(4363426);
    private static PrintWriter testsLst;

    private static final int MAX_COORD = 1000000;

    static class Point {
        final int x, y;

        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        long vmul(Point l, Point r) {
            return (long) (l.x - x) * (r.y - y) - (long) (l.y - y) * (r.x - x);
        }

        public String toString() {
            return x + " " + y;
        }
    }

    void writeTest(String name, Point... points) {
        try {
            testsLst.printf("Test %02d [%d]: %s%n", curTest, points.length, name);
            testsLst.flush();
            PrintWriter out = new PrintWriter(new File(dir, String.format("%02d", curTest++)));
            out.println(points.length);
            for (Point p : points) {
                out.println(p);
            }
            out.close();
        } catch (IOException ex) {
            throw new RuntimeException(ex);
        }
    }

    void writeTestT(String name, Point... points) {
        writeTest(name, points);
        Point[] p2 = new Point[points.length];
        for (int i = 0, j = p2.length - 1; i < p2.length; ++i, --j) {
            p2[i] = new Point(points[j].y, points[j].x);
        }
        writeTest(name + " (transposed)", p2);
    }

    void writeSaw1(int size, int height) {
        Point[] pts = new Point[size * 2];
        for (int i = 0; i < size; ++i) {
            pts[i] = new Point(-MAX_COORD + i, i % 2 == 0 ? -height : (height - 1));
            pts[pts.length - 1 - i] = new Point(-MAX_COORD + i, i % 2 == 0 ? -(height - 1) : height);
        }
        writeTestT("Saw 1 (thickness = 1, pairs = " + size + ", height = " + height + ")", pts);
    }

    void writeSaw2(int size, int height) {
        Point[] pts = new Point[size * 2];
        for (int i = 0; i < size; ++i) {
            pts[i] = new Point(-MAX_COORD + i, i % 2 == 0 ? -height : -1);
            pts[pts.length - 1 - i] = new Point(-MAX_COORD + i, i % 2 == 0 ? height : 1);
        }
        writeTestT("Saw 2 (thickness = 2e6 or 2, pairs = " + size + ", height = " + height + ")", pts);
    }


    void writeStar(int size) {
        Point[] pts = new Point[size];
        for (int i = 0; i < size; ++i) {
            pts[i] = new Point(
                random.nextInt(2 * MAX_COORD + 1) - MAX_COORD,
                random.nextInt(2 * MAX_COORD + 1) - MAX_COORD
            );
        }
        Arrays.sort(pts, new Comparator<Point>() {
            public int compare(Point l, Point r) {
                boolean lh = l.y > 0 || l.y == 0 && l.x > 0;
                boolean rh = r.y > 0 || r.y == 0 && r.x > 0;
                if (lh != rh) return lh ? -1 : 1;
                long vmul = (long) (l.x) * r.y - (long) (l.y) * r.x;
                if (vmul != 0) return vmul < 0 ? 1 : -1;
                long ll = (long) (l.x) * l.x + (long) (l.y) * l.y;
                long rl = (long) (r.x) * r.x + (long) (r.y) * r.y;
                return ll == rl ? 0 : ll < rl ? -1 : 1;
            }
        });
        writeTest("Random star", pts);
    }

    void writeRandomSaw(int size, int height) {
        int amp = 2 * height + 1;
        Point[] pts = new Point[size * 2];
        Set<Integer> xss = new TreeSet<>();
        while (xss.size() < size) {
            xss.add(random.nextInt(2 * MAX_COORD + 1) - MAX_COORD);
        }
        Integer[] xs = xss.toArray(new Integer[size]);
        int last = pts.length - 1;
        for (int i = 0; i < size; ++i) {
            while (true) {
                int y1, y2;
                do {
                    y1 = random.nextInt(amp) - height;
                    y2 = random.nextInt(amp) - height;
                } while (y1 == y2);
                int yL = Math.min(y1, y2);
                int yH = Math.max(y1, y2);

                pts[i] = new Point(xs[i], yL);
                pts[last - i] = new Point(xs[i], yH);

                if (i >= 2) {
                    if (pts[i - 2].vmul(pts[i - 1], pts[i]) == 0) {
                        continue;
                    }
                    if (pts[last - (i - 2)].vmul(pts[last - (i - 1)], pts[last - i]) == 0) {
                        continue;
                    }
                }

                break;
            }
        }
        writeTestT("Random saw (pairs = " + size + ", max height = " + height + ")", pts);
    }

    void writeAntiCircle(int size) {
        if (size % 2 == 0) {
            --size;
        }
        int[] chain = new int[size / 2];
        chain[0] = 1;
        for (int i = 1, j = 2; i < chain.length; ++i) {
            chain[i] = chain[i - 1] + j;
            if (chain[i] > MAX_COORD) {
                throw new AssertionError("Max size: " + (i - 1));
            }
            j++;
        }

        Point[] pts = new Point[size];
        pts[0] = new Point(MAX_COORD, MAX_COORD);
        int sz = 1;
        for (int i = chain.length - 1; i >= 0; --i) {
            pts[sz++] = new Point(-chain[i], i);
        }
        for (int i = 0; i < chain.length; ++i) {
            pts[sz++] = new Point(i, -chain[i]);
        }

        writeTestT("Concave circle quarter", pts);
    }

    void writeHighDegree(int halfSize, int teethHeight, boolean stepDownEvery2) {
        if (halfSize % 2 == 0) {
            --halfSize;
        }
        Point[] pts = new Point[halfSize * 2];
        --halfSize;
        int sz = 0;
        pts[sz++] = new Point(MAX_COORD - teethHeight, MAX_COORD - teethHeight);
        for (int i = 0, d = 0, x = MAX_COORD - teethHeight; i < halfSize; ++i) {
            if (stepDownEvery2) {
                if (i % 4 == 3 || i + 1 == halfSize) {
                    ++d;
                }
            }
            if (i % 2 == 0) {
                pts[sz++] = new Point(x + 1, MAX_COORD);
                --x;
            } else {
                pts[sz++] = new Point(x, MAX_COORD - teethHeight - d);
            }
        }
        pts[sz++] = new Point(pts[0].x - 1, pts[0].y - 1);
        int last = sz - 2;
        while (sz < pts.length) {
            pts[sz++] = new Point(pts[last].y, pts[last].x);
            --last;
        }
        if (last != 0) {
            throw new AssertionError("Something wrong");
        }
        writeTest("Vertex with high degree (teeth height: " + teethHeight + ", step down every 2: " + stepDownEvery2 + ")", pts);
    }

    static Point p(int x, int y) {
        return new Point(x, y);
    }

    public Tests() {
        writeTest("Sample (arrow)", p(0, 0), p(-1, -1), p(1, 0), p(-1, 1));
        writeTest("Triangle", p(0, 0), p(1, 0), p(0, 1));
        writeTest("Big triangle", p(-MAX_COORD, -MAX_COORD), p(MAX_COORD, 42), p(-MAX_COORD + 1, MAX_COORD));
        writeTest("Thin big triangle", p(MAX_COORD, MAX_COORD), p(MAX_COORD - 1, -MAX_COORD), p(MAX_COORD, MAX_COORD - 1));
        writeTestT("Tricky", p(-MAX_COORD, 0), p(0, -1), p(MAX_COORD, 0), p(0, 1));
        writeTest("Square", p(-MAX_COORD, 0), p(0, -MAX_COORD), p(MAX_COORD, 0), p(0, MAX_COORD));
        writeTest("Rectangle with very different triangles", p(-MAX_COORD, MAX_COORD), p(-MAX_COORD + 1, -MAX_COORD + 2), p(-MAX_COORD + 2, -MAX_COORD + 1), p(MAX_COORD, -MAX_COORD));
        writeTest("Simple nonconvex", p(0, 0), p(1, 0), p(1, 1), p(3, 1), p(3, 2), p(0, 2));
        writeTestT("Three parts of equal square", p(1, 0), p(1, MAX_COORD - 1), p(-1, MAX_COORD - 1), p(-1, 0), p(-MAX_COORD, -MAX_COORD + 1), p(-MAX_COORD + 1, -MAX_COORD),
                   p(0, -1), p(MAX_COORD - 1, -MAX_COORD), p(MAX_COORD, -MAX_COORD + 1));
        writeTestT("Three parts of equal square, bigger", p(MAX_COORD, MAX_COORD), p(-MAX_COORD, MAX_COORD), p(-MAX_COORD, MAX_COORD - 4),
                   p(MAX_COORD - 6, MAX_COORD - 4), p(-MAX_COORD, -MAX_COORD + 2), p(-MAX_COORD + 2, -MAX_COORD), p(MAX_COORD - 4, MAX_COORD - 6), p(MAX_COORD - 4, -MAX_COORD), p(MAX_COORD, -MAX_COORD));
        writeTestT("Split vertex", p(0, 0), p(1, 1), p(2, 0), p(1, 2));
        writeTestT("Split vertex with unequal parts", p(0, -1), p(1, 1), p(2, 0), p(1, 2));
        writeTestT("Thin and high saw on 6 vertices", p(-1, -MAX_COORD), p(0, 0), p(1, -MAX_COORD), p(1, MAX_COORD), p(0, 1), p(-1, MAX_COORD));
        writeTestT("Thin and high saw on 6 vertices", p(0, MAX_COORD - 1), p(1, -MAX_COORD), p(2, MAX_COORD - 1), p(2, MAX_COORD), p(1, -MAX_COORD + 1), p(0, MAX_COORD));

        for (int size : new int[] { 101, 301, 901, 2425 }) {
            writeAntiCircle(size);
        }

        for (int halfSize : new int[] {2, 3, 5, 7, 9, 11, 21, 41}) {
            writeSaw1(halfSize, MAX_COORD);
        }

        for (int halfSize : new int[] {101, 1001, 2500}) {
            writeSaw1(halfSize, 15);
            writeSaw1(halfSize, MAX_COORD);
            writeSaw2(halfSize, 15);
            writeSaw2(halfSize, MAX_COORD);
            writeRandomSaw(halfSize, 15);
            writeRandomSaw(halfSize, MAX_COORD);
            writeStar(halfSize * 2);
            writeHighDegree(halfSize, 10, false);
            writeHighDegree(halfSize, MAX_COORD, false);
            writeHighDegree(halfSize, 10, true);
            writeHighDegree(halfSize, MAX_COORD, true);
        }
    }

    public static void main(String[] args) throws IOException {
        Locale.setDefault(Locale.US);
        dir.mkdirs();
        testsLst = new PrintWriter(new File(dir, "tests.lst"));
        new Tests();
        testsLst.close();
    }
}

