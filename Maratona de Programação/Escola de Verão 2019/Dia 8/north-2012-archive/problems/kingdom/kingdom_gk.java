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
import java.util.List;

public class kingdom_gk {
    static Scanner in;
    static PrintWriter out;

    static final double F = 1 / 6.0;
    static double remainingArea;
    static double eps;
    static List<FPoint> answer = new ArrayList<>();
    static int edgeY;

    NavigableMap<Edge, Helper> helpers = new TreeMap<>(new Comparator<Edge>() {
        public int compare(Edge e1, Edge e2) {
            double d = e1.x() - e2.x();
            return Math.abs(d) < 1e-10 ? 0 : d < 0 ? -1 : 1;
        }
    });

    static class Point {
        int x, y;

        Point(int x, int y) {
            this.x = x;
            this.y = y;
        }
    }

    static class Edge implements Comparable<Edge> {
        Point p;
        Edge next, prev;
        boolean u, u2;
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

        List<Edge> toList() {
            ArrayList<Edge> list = new ArrayList<>();
            Edge e = this;
            do {
                list.add(e);
                e = e.next;
            } while (e != this);
            return list;
        }

        double x() {
            int dpx = next.p.x - p.x;
            int dpy = next.p.y - p.y;
            return dpy != 0 ? p.x + (edgeY - p.y) / (double) dpy * dpx : p.x;
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

        static FPoint companion(FPoint pc, FPoint p1, FPoint p2, double f) {
            return new FPoint(
                    (pc.x + ((p1.x + p2.x) / 2.0 - pc.x) * f),
                    (pc.y + ((p1.y + p2.y) / 2.0 - pc.y) * f)
            );
        }

        boolean isDown() {
            return compareTo(next) < 0;
        }

        FPoint companion() {
            FPoint fp1 = new FPoint(p);
            FPoint fp2 = new FPoint(next.p);
            return companion(fp1, fp2, fp2, F);
        }
    }

    static double area(FPoint p1, FPoint p2, FPoint p3) {
        return (p2.x - p1.x) * (p2.y + p1.y) + (p3.x - p2.x) * (p3.y + p2.y) + (p1.x - p3.x) * (p1.y + p3.y) ;
    }

    static class Helper {
        boolean merge;
        Edge e;

        Helper(Edge e, boolean merge) {
            this.e = e;
            this.merge = merge;
        }

        Edge connect(Edge that, boolean split) {
            if (!merge && !split) {
                return that;
            }

            return this.e.diagonal(that);
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
        eps = remainingArea * 1e-8;

        triangulateMonotones(toMonotone(polygon));

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
            points[i] = new Point(in.nextInt(), -in.nextInt());
        }
        return points;
    }

    long area(Edge root) {
        long area = 0;
        for (Edge edge : root.toList()) {
            area += (edge.next.p.x - edge.p.x) * (long) (edge.next.p.y + edge.p.y);
        }
        return area;
    }

    List<Edge> toMonotone(Edge root) throws IOException {
        List<Edge> events = root.toList();
        Collections.sort(events);

        for (Edge edge : events) {
            boolean inside = v(edge.p, edge.prev.p, edge.next.p) < 0;
            boolean prev = edge.prev.isDown();
            boolean next = edge.isDown();

            edgeY = edge.p.y;

            if (prev && !next) {
                remove(edge.prev);
                if (inside) { // Merge
                    update(edge, true, false);
                } // End
            } else if (!prev && next){
                if (inside) { // Split
                    update(edge, false, true);
                } // Start
                add(edge);
            } else {
                if (prev) { // Regular right
                    remove(edge.prev);
                    add(edge);
                } else { // Regular left
                    update(edge, false, false);
                }
            }

        }
        return events;
    }

    static long v(Point p0, Point p1, Point p2) {
        return (p1.x - p0.x) * (long) (p2.y - p0.y) - (p1.y - p0.y) * (long) (p2.x - p0.x);
    }

    void remove(Edge edge) {
        helpers.remove(edge).connect(edge.next, false);
    }

    void add(Edge edge) {
        helpers.put(edge, new Helper(edge, false));
    }

    void update(Edge edge, boolean merge, boolean split) {
        Map.Entry<Edge, Helper> e = helpers.lowerEntry(edge);
        edge = e.getValue().connect(edge, split);
        helpers.put(e.getKey(), new Helper(edge, merge));
    }

    void triangulateMonotones(List<Edge> events) {
        for (Edge edge : events) {
            if (!edge.u) {
                new MonotoneTriangulator().triangulate(edge);
            }
        }
    }

    static class MonotoneTriangulator {
        Deque<Edge> stack = new ArrayDeque<>();
        Edge prev;
        Edge curr;
        boolean lastLeft;

        void triangulate(Edge edge) {
            NavigableSet<Edge> edges = new TreeSet<>(edge.toList());

            stack.push(edges.pollFirst());
            curr = edges.pollFirst();
            lastLeft = curr.isDown();
            stack.push(curr);

            while (edges.size() != 1) {
                curr = edges.pollFirst();
                boolean left = curr.isDown();

                if (lastLeft == left) {
                    addSame();
                } else {
                    addOther();
                }
                stack.push(prev);
                stack.push(curr);
                lastLeft = left;
            }
            curr = edges.pollFirst();
            addOther();
        }

        void addSame() {
            prev = stack.pop();
            while (!stack.isEmpty()) {
                Point next = stack.peek().p;
                long v = v(prev.p, curr.p, next);
                if (v == 0 || v > 0 == lastLeft) {
                    break;
                }
                addTriangle(lastLeft, stack.pop());
            }
        }

        void addOther() {
            prev = stack.peek();
            Deque<Edge> deque = new ArrayDeque<>();
            while (stack.size() > 1) {
                deque.push(stack.pop());
            }
            stack.pop();
            for (Edge next : deque) {
                if (curr.next != next && curr.prev != next) {
                    addTriangle(!lastLeft, next);
                }
            }
        }

        void addTriangle(boolean big, Edge next) {
            next.diagonal(curr);
            if (big) {
                prev = curr.prev;
            } else {
                curr = next.prev;
                prev = curr.next;
            }
        }
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

        new kingdom_gk().run();

        in.close();
        out.close();
    }
}

