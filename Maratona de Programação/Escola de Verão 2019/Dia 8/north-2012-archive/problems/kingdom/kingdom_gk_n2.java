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
/* Solution                                                       */
/*                                                                */
/* Author               Georgiy Korneev                           */
/******************************************************************/

import java.io.*;
import java.util.*;

public class kingdom_gk_n2 {
    static Scanner in;
    static PrintWriter out;

    static final double F = 1 / 6.0;
    static double remainingArea;
    static double eps;
    static List<FPoint> answer = new ArrayList<>();

    static class Point {
        int i, x, y;

        Point(int i, int x, int y) {
            this.i = i;
            this.x = x;
            this.y = y;
        }
    }

    static class Edge implements Comparable<Edge> {
        Point p;
        Edge next, prev;
        boolean u2;
        Edge twin;

        Edge(Point p) {
            this.p = p;
            next = prev = this;
        }

        public int compareTo(Edge that) {
            return this.p.y != that.p.y ? this.p.y - that.p.y : this.p.x - that.p.x;
        }

        Edge append(Point p) {
            prev.flip(new Edge(p));
            return prev;
        }

        void flip(Edge that) {
            Edge t = this.next; this.next = that.next; that.next = t;
            this.next.prev = this;
            that.next.prev = that;
        }

        Edge diagonal(Edge that) {
            Edge nthat = new Edge(p);
            Edge nthis = nthat.append(that.p);
            nthat.twin = nthis;
            nthis.twin = nthat;
            prev.flip(nthis);
            that.prev.flip(nthat);
            return prev;
        }

        void dfs(FPoint c1, FPoint c2) {
            assert next.next == prev && prev.prev == next;
            if (remainingArea <= eps) {
                answer.add(c2);
                return;
            }

            this.u2 = next.u2 = prev.u2 = true;

            boolean hasNext = next.twin != null && !next.twin.u2;
            boolean hasPrev = prev.twin != null && !prev.twin.u2;

            if (hasNext) {
                c2 = next.process(c1, c2);
            }
            if (hasPrev && remainingArea > eps) {
                c2 = prev.process(c1, c2);
            }

            if (!hasNext && !hasPrev) {
                FPoint c3 = companion(new FPoint(next.next.p), new FPoint(prev.next.p), new FPoint(next.p), F);
                if (addTriangle(c1, c2, c3)) {
                    answer.add(c3);
                }
            }
        }

        FPoint process(FPoint c1, FPoint c2) {
            FPoint nc1 = this.companion();
            FPoint nc2 = twin.companion();
            if (addTriangle(c1, c2, nc1)) {
                answer.add(nc1);
                if (addTriangle(c1, nc1, nc2)) {
                    twin.dfs(nc2, nc1);
                    answer.add(nc2);
                }
            }
            return nc2;
        }

        boolean addTriangle(FPoint b1, FPoint b2, FPoint n) {
            if (remainingArea < eps) {
                return true;
            }
            double da = area(b1, b2, n);

            if (remainingArea >= da) {
                remainingArea -= da;
                return true;
            }

            FPoint ln = companion(n, b1, b2, 1 - remainingArea / da);
            remainingArea -= area(b1, b2, ln);
            answer.add(ln);
            return false;
        }

        FPoint companion(FPoint pc, FPoint p1, FPoint p2, double f) {
            return new FPoint(
                    (pc.x + ((p1.x + p2.x) / 2.0 - pc.x) * f),
                    (pc.y + ((p1.y + p2.y) / 2.0 - pc.y) * f)
            );
        }

        double area(FPoint p1, FPoint p2, FPoint p3) {
            return (p2.x - p1.x) * (p2.y + p1.y) + (p3.x - p2.x) * (p3.y + p2.y) + (p1.x - p3.x) * (p1.y + p3.y) ;
        }

        FPoint companion() {
            FPoint fp1 = new FPoint(p);
            FPoint fp2 = new FPoint(next.p);
            return companion(fp1, fp2, fp2, F);
        }

        void cutEars() {
            if (next.next.next == this) {
                return;
            }
            Edge edge = this;
            do {
                if (v(edge.p, edge.prev.p, edge.next.p) > 0) {
                    edge.cutEar();
                    return;
                }
                edge = edge.next;
            } while (edge != this);
        }

        boolean inside(Point p1, Point p2, Point p3, Point p) {
            return v(p1, p2, p) <= 0 && v(p2, p3, p) <= 0 && v(p3, p1, p) <= 0;
        }

        void cutEar() {
            Point pn = next.p;
            Point pp = prev.p;

            long bestV = Long.MAX_VALUE;
            Edge best = null;
            Edge edge = this.next.next;
            do {
                if (inside(prev.p, p, next.p, edge.p)) {
                    long v = v(pn, pp, edge.p);
                    if (bestV > v) {
                        bestV = v;
                        best = edge;
                    }
                }
                edge = edge.next;
            } while (edge != prev);
            if (best != null) {
                diagonal(best);
                cutEars();
                best.cutEars();
            } else {
                Edge next = this.next;
                next.diagonal(prev);
                next.cutEars();
            }
        }

        long v(Point p0, Point p1, Point p2) {
            return (p1.x - p0.x) * (long) (p2.y - p0.y) - (p1.y - p0.y) * (long) (p2.x - p0.x);
        }
    }

    static class FPoint {
        double x;
        double y;

        FPoint(double x, double y) {
            this.x = x;
            this.y = y;
        }

        FPoint(Point point) {
            this(point.x, point.y);
        }
    }

    void run() throws Exception {
        Point[] points = readPoints();
        Edge polygon = createPolygon(points);

        remainingArea = area(polygon) / 2.0;
        assert remainingArea > 0;
        eps = remainingArea * 1e-8;

        polygon.cutEars();

        FPoint c1 = new FPoint(polygon.next.p);
        FPoint c2 = new FPoint(polygon.p);
        answer.add(c1);
        polygon.dfs(c2, c1);
        answer.add(c2);

        out.println(answer.size());
        for (FPoint anAnswer : answer) {
            out.println(anAnswer.x + " " + (-anAnswer.y));
        }

        out.println(points.length + answer.size() - 2);
        for (int i = 1; i < points.length; i++) {
            out.format("%d %d\n", points[i].x, -points[i].y);
        }
        for (int i = answer.size() - 1; i >= 1; i--) {
            out.println(answer.get(i).x + " " + (-answer.get(i).y));
        }
    }

    Edge createPolygon(Point[] points) {
        Edge root = new Edge(points[0]);
        for (int i = 1; i < points.length; i++) {
            root.append(points[i]);
        }
        return root;
    }

    Point[] readPoints() {
        Point[] points = new Point[in.nextInt()];
        for (int i = 0; i < points.length; i++) {
            points[i] = new Point(i, in.nextInt(), -in.nextInt());
        }
        return points;
    }

    long area(Edge root) {
        long area = 0;
        Edge edge = root;
        do {
            edge = edge.next;
            area += (edge.next.p.x - edge.p.x) * (long) (edge.next.p.y + edge.p.y);
        } while (edge != root);
        return area;
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
        Locale.setDefault(Locale.ENGLISH);
        in = new Scanner(new File("kingdom.in"));
        out = new PrintWriter("kingdom.out");

        new kingdom_gk_n2().run();

        in.close();
        out.close();
    }
}

