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
/* Solution                                                       */
/*                                                                */
/* Author               Georgiy Korneev                           */
/******************************************************************/

import java.io.*;
import java.util.*;

public class grid_gk {
    static Scanner in;
    static PrintWriter out;

    static class Point {
        int x, y;

        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (!(o instanceof Point)) return false;

            Point point = (Point) o;

            return x == point.x && y == point.y;

        }

        @Override
        public int hashCode() {
            int result = x;
            result = 31 * result + y;
            return result;
        }
    }

    void run() {
        int n = in.nextInt();
        List<Point> points = new ArrayList<>();
        for (int i = 0; i < n; i++) {
            points.add(new Point(in.nextInt(), in.nextInt()));
        }
        Collections.sort(points, new Comparator<Point>() {
            public int compare(Point p1, Point p2) {
                return p1.x != p2.x ? Integer.compare(p1.x, p2.x) : Integer.compare(p1.y, p2.y);
            }
        });
        if (!check(points.get(0), points.get(1), points)) {
            check(points.get(0), points.get(2), points);
        }
    }

    boolean check(Point p1, Point p2, List<Point> points) {
        long dx = p2.x - p1.x;
        long dy = p2.y - p1.y;
        int y0 = p1.y;
        int x0 = p1.x;
        int good = 0;
        List<Point> bad = new ArrayList<>();
        for (Point point : points) {
            if (isBad(point.x - x0, dx, good) || isBad(point.y - y0, dy, good)) {
                bad.add(point);
            } else {
                good++;
            }
        }
        if (bad.isEmpty()) {
            if (dx == 0) {
                answer(dx, dy, x0 + 1, y0, 1, good);
            } else if (dy == 0) {
                answer(dx, dy, x0, y0 + 1, good, 1);
            } else {
                answer(dx, dy, x0, y0, good, good);
            }
            return true;
        }
        if (bad.size() == 1) {
            answer(dx, 0, x0, bad.get(0).y, good, 1);
            return true;
        }
        int result = check2(bad.get(0), bad.get(1), points, new HashSet<>(bad));
        if (result != -1) {
            answer(dx, bad.get(1).y - bad.get(0).y, x0, bad.get(0).y, good, result);
            return true;
        }
        return false;
    }


    int check2(Point p1, Point p2, List<Point> points, Set<Point> bad) {
        Point prev = null;
        long dx = 0;
        long dy = 0;
        for (Point point : bad) {
            if (prev != null) {
                dx = gcd(dx, Math.abs(point.x - prev.x));
                dy = gcd(dy, Math.abs(point.y - prev.y));
            }
            prev = point;
        }
        int y0 = p1.y;
        int x0 = p1.x;
        int good = 0;
        boolean found = false;
        for (Point point : points) {
            found |= point == p1;
            if (!found) {
                continue;
            }
            if (isBad(point.x - x0, dx, good) || isBad(point.y - y0, dy, good)) {
                if (bad.contains(point)) {
                    return -1;
                }
            } else {
                good++;
            }
        }
        return good;
    }

    private long gcd(long a, long b) {
        if (a == 0) {
            return b;
        }
        return gcd(b % a, a);
    }

    private void answer(long dx, long dy, int x1, int y1, int gx, int gy) {
        long x2 = x1 + (gx - 1) * dx;
        long y2 = y1 + (gy - 1) * dy;
        if (dx == 0) {
            dx = 1;
        }
        if (dy == 0) {
            dy = 1;
        }
        out.format(
                "%d %d %d %d %d %d\n",
                Math.min(x1, x2), Math.max(x1, x2), Math.abs(dx),
                Math.min(y1, y2), Math.max(y1, y2), Math.abs(dy)
        );
    }

    private boolean isBad(int pdx, long dx, int good) {
        return dx != 0 ? pdx % dx != 0 || Math.abs(pdx / dx) != good : pdx != 0;
    }

    static class Scanner {
        final BufferedReader reader;
        StringTokenizer tokenizer = new StringTokenizer("");

        public Scanner(File file) throws FileNotFoundException {
            reader = new BufferedReader(new FileReader(file));
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public String next() {
            while (!tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new AssertionError();
                }
            }
            return tokenizer.nextToken();
        }

        public void close() {
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("grid.in"));
        out = new PrintWriter("grid.out");

        new grid_gk().run();

        in.close();
        out.close();
    }
}

