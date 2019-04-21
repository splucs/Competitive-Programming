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
/* Author               Maxim Buzdalov                            */
/******************************************************************/

import java.io.*;
import java.util.*;

public class kingdom_mb_n2 {
    static class Point implements Comparable<Point> {
        static final Map<Point, Point> uniquifier = new HashMap<Point, Point>();

        final int x;
        final int y;

        boolean inserted = false;

        List<Edge> outs = new ArrayList<Edge>();

        private Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public int compareTo(Point that) {
            if (y != that.y) return y - that.y;
            if (x != that.x) return x - that.x;
            return 0;
        }

        public long vmulAround(Point lhs, Point rhs) {
            long ldx = lhs.x - x;
            long ldy = lhs.y - y;
            long rdx = rhs.x - x;
            long rdy = rhs.y - y;
            return ldx * rdy - ldy * rdx;
        }

        public int hashCode() {
            return x * 239 + y * 31;
        }

        public boolean equals(Object o) {
            if (o instanceof Point) {
                Point that = (Point) (o);
                return x == that.x && y == that.y;
            }
            return false;
        }

        public String toString() {
            return "(" + x + "; " + y + ")";
        }

        public static Point make(int x, int y) {
            Point pt = new Point(x, y);
            Point ref = uniquifier.get(pt);
            if (ref == null) {
                uniquifier.put(pt, ref = pt);
            }
            return ref;
        }
    }

    static class Face {
        final Edge sample;
        final boolean outer;
        boolean visited = false;

        Face(Edge sample) {
            this.sample = sample;
            Edge curr = sample;
            do {
                curr.face = this;
                curr = curr.next;
            } while (curr != sample);
            this.outer = squareImpl() > 0;
        }

        long squareImpl() {
            long rv = 0;
            Edge curr = sample;
            do {
                rv += (long) (curr.source.x) * curr.target.y - (long) (curr.source.y) * curr.target.x;
                curr = curr.next;
            } while (curr != sample);
            return rv;
        }

        double square() {
            return Math.abs(squareImpl()) / 2.0;
        }

        public String toString() {
            StringBuilder sb = new StringBuilder(outer ? "O" : "I");
            Edge curr = sample;
            do {
                if (curr != sample) {
                    sb.append("--");
                }
                sb.append(curr.source);
                curr = curr.next;
            } while (curr != sample);
            return sb.toString();
        }
    }

    static class Edge {
        final Point source;
        final Point target;
        final Edge twin;
        Face face;

        Edge prev, next;

        private Edge(Point source, Point target, Edge twin) {
            this.source = source;
            this.target = target;
            this.twin = twin;
        }

        public Edge(Point source, Point target) {
            this.source = source;
            this.target = target;
            prev = next = twin = new Edge(target, source, this);
            twin.prev = twin.next = this;
        }

        public int hashCode() {
            return source.hashCode() * 31 + target.hashCode();
        }

        public boolean equals(Object o) {
            if (o instanceof Edge) {
                Edge that = (Edge) o;
                return source.equals(that.source) && target.equals(that.target);
            }
            return false;
        }

        public String toString() {
            return source + "--" + target;
        }
    }


    static void dfs(Face current, Edge entrance, List<String> answer, double t) {
        if (entrance == null) {
            int count = 0;
            Edge connected = null;
            Edge c = current.sample;
            do {
                if (!c.twin.face.outer) {
                    count++;
                    connected = c;
                }
                c = c.next;
            } while (c != current.sample);
            if (count != 1) {
                throw new AssertionError();
            }
            Point p0 = connected.source;
            Point p1 = connected.target;
            Point p2 = connected.next.target;
            answer.add(interpolate(p0, p2, 2 * t));
            answer.add(interpolate(p0, p1, t));
            dfs(connected.twin.face, connected.twin, answer, t);
            answer.add(interpolate(p1, p0, t));
            answer.add(interpolate(p1, p2, 2 * t));
        } else {
            if (current != entrance.face) {
                throw new AssertionError();
            }
            Point p0 = entrance.source;
            Point p1 = entrance.target;
            Point p2 = entrance.next.target;

            int degree = 1;
            if (!entrance.next.twin.face.outer) ++degree;
            if (!entrance.prev.twin.face.outer) ++degree;
            if (degree == 1) {
                double xl = p0.x * (1 - t) + p1.x * t;
                double yl = p0.y * (1 - t) + p1.y * t;
                double xr = p2.x * (1 - t) + p1.x * t;
                double yr = p2.y * (1 - t) + p1.y * t;
                double t2 = t / (1 - t);
                double x = xl * t2 + xr * (1 - t2);
                double y = yl * t2 + yr * (1 - t2);
                answer.add(x + " " + y);
            } else {
                if (!entrance.next.twin.face.outer) {
                    answer.add(interpolate(p1, p2, t));
                    dfs(entrance.next.twin.face, entrance.next.twin, answer, t);
                    answer.add(interpolate(p2, p1, t));
                }
                if (!entrance.prev.twin.face.outer) {
                    answer.add(interpolate(p2, p0, t));
                    dfs(entrance.prev.twin.face, entrance.prev.twin, answer, t);
                    answer.add(interpolate(p0, p2, t));
                }
            }
        }
    }

    static String interpolate(Point p0, Point p1, double t) {
        return (p0.x * (1 - t) + p1.x * t) + " " + (p0.y * (1 - t) + p1.y * t);
    }

    static boolean isConvex(Edge e) {
        Point prev = e.prev.source;
        Point curr = e.source;
        Point next = e.target;
        return prev.vmulAround(curr, next) < 0;
    }

    static boolean isEar(Edge e, Collection<Edge> concave) {
        Point prev = e.prev.source;
        Point curr = e.source;
        Point next = e.target;
        for (Edge c : concave) {
            if (c.next != e && e.next != c) {
                Point m = c.source;
                if (prev.vmulAround(m, curr) >= 0 && curr.vmulAround(m, next) >= 0 && next.vmulAround(m, prev) >= 0) {
                    return false;
                }
            }
        }
        return true;
    }

    static void earClipping(Face face, List<Edge> allEdges) {
        Set<Edge> concave = new LinkedHashSet<Edge>();
        List<Edge> convex = new ArrayList<Edge>();
        Set<Edge> ears = new HashSet<Edge>();

        Edge curr = face.sample;
        do {
            if (isConvex(curr)) {
                convex.add(curr);
            } else {
                concave.add(curr);
            }
            curr = curr.next;
        } while (curr != face.sample);

        for (Edge e : convex) {
            if (isEar(e, concave)) {
                ears.add(e);
            }
        }
        convex.clear();

        while (true) {
            Edge ear = ears.iterator().next();
            if (ear.next.next.next == ear) {
                new Face(ear);
                break;
            }
            ears.remove(ear);
            concave.remove(ear.prev);
            ears.remove(ear.prev);

            Edge newEdge = new Edge(ear.prev.source, ear.target);
            allEdges.add(newEdge);
            allEdges.add(newEdge.twin);

            newEdge.next = ear.next;
            newEdge.prev = ear.prev.prev;
            newEdge.next.prev = newEdge;
            newEdge.prev.next = newEdge;
            ear.prev.prev = newEdge.twin;
            ear.next = newEdge.twin;
            newEdge.twin.prev = ear;
            newEdge.twin.next = ear.prev;
            newEdge.twin.prev.next = newEdge.twin;
            newEdge.twin.next.prev = newEdge.twin;
            newEdge.face = ear.face;
            new Face(ear);

            for (Edge e : new Edge[] { newEdge.next, newEdge }) {
                concave.remove(e);
                ears.remove(e);

                if (isConvex(e)) {
                    if (isEar(e, concave)) {
                        ears.add(e);
                    }
                } else {
                    concave.add(e);
                }
            }
        }
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("kingdom.in"));
        int n = Integer.parseInt(in.readLine());
        Point[] pts = new Point[n];
        for (int i = 0; i < n; ++i) {
            String ln = in.readLine();
            int ws = ln.indexOf(' ');
            pts[i] = Point.make(Integer.parseInt(ln.substring(0, ws)), Integer.parseInt(ln.substring(ws + 1)));
        }
        in.close();

        List<Edge> allEdges = new ArrayList<Edge>();
        Edge anInnerEdge = null;
        for (int i = 0; i < n; ++i) {
            Edge outer = new Edge(pts[i], pts[(i + 1) % n]);
            Edge inner = outer.twin;
            allEdges.add(outer);
            allEdges.add(inner);
            if (anInnerEdge == null) {
                anInnerEdge = inner;
            }
            outer.source.outs.add(outer);
            inner.source.outs.add(inner);
        }
        for (int i = 0; i < n; ++i) {
            Edge a = pts[i].outs.get(0);
            Edge b = pts[i].outs.get(1);
            a.prev = b.twin;
            b.twin.next = a;
            b.prev = a.twin;
            a.twin.next = b;
        }
        Face outerFace = new Face(anInnerEdge.twin);
        Face innerFace = new Face(anInnerEdge);

        earClipping(innerFace, allEdges);

        //6. Collect and check faces
        List<Face> faces = new ArrayList<Face>();
        int outerCount = 0;
        for (Edge e : allEdges) {
            Face f = e.face;
            if (!f.visited) {
                f.visited = true;
                if (f.outer) {
                    ++outerCount;
                } else {
                    if (f.sample == f.sample.next || f.sample == f.sample.next.next || f.sample != f.sample.next.next.next) {
                        throw new AssertionError();
                    }
                }
                faces.add(f);
            }
        }
        if (outerCount != 1) {
            throw new AssertionError();
        }

        //7. Count the squares and arities of faces.
        Face leaf = null;
        double[] squares = new double[4];
        for (Face f : faces) {
            if (f.outer) {
                continue;
            }
            f.visited = false;
            Edge curr = f.sample;
            int count = 0;
            do {
                if (!curr.twin.face.outer) {
                    ++count;
                }
                curr = curr.next;
            } while (curr != f.sample);
            if (count <= 1) {
                leaf = f;
            }
            squares[count] += f.square();
        }

        PrintWriter out = new PrintWriter("kingdom.out");
        if (squares[0] > 0) {
            //8(a). The special case of one triangle.
            Point p0 = leaf.sample.source;
            Point p1 = leaf.sample.next.source;
            Point p2 = leaf.sample.next.next.source;
            out.println(3);
            out.println(p0.x + " " + p0.y);
            out.println(p2.x + " " + p2.y);
            out.println((p2.x + p1.x) / 2.0 + " " + (p2.y + p1.y) / 2.0);
            out.println(3);
            out.println((p2.x + p1.x) / 2.0 + " " + (p2.y + p1.y) / 2.0);
            out.println(p1.x + " " + p1.y);
            out.println(p0.x + " " + p0.y);
        } else {
            //8(b).1. Counting the value of the parameter.
            //count[3] => 3 * t * t
            //count[2] => 2 * t
            //count[1], non-starting => 4 * t - 4 * t * t
            //count[1], starting => 4 * t * t

            //A * t * t + 2 * B * t + C = 0
            double C = -0.5 * (squares[1] + squares[2] + squares[3]);
            double B = squares[2] + 2 * (squares[1] - leaf.square());
            double A = 3 * squares[3] - 4 * (squares[1] - leaf.square()) + 4 * leaf.square();
            double D = B * B - A * C;

            double t;
            if (Math.abs(A) < 1e-9) {
                t = -C / (2 * B);
            } else {
                if (Math.abs(D) < 1e-9) {
                    D = 0;
                }
                if (D < 0) {
                    throw new AssertionError();
                }
                D = Math.sqrt(D);
                double t1 = (-B - D) / A;
                double t2 = (-B + D) / A;
                if (0 < t1 && t1 < 0.5) {
                    t = t1;
                } else if (0 < t2 && t2 < 0.5) {
                    t = t2;
                } else {
                    throw new AssertionError("t1 = " + t1 + " t2 = " + t2);
                }
            }

            //8(b).2. Calculating inner points.
            List<String> inner = new ArrayList<String>();
            dfs(leaf, null, inner, t);

            Edge connected = leaf.sample;
            while (connected.twin.face.outer) {
                connected = connected.next;
            }
            Point start = connected.next.target;
            int index = -1;
            for (int i = 0; i < n; ++i) {
                if (pts[i] == start) {
                    index = i;
                    break;
                }
            }

            //8(b).3. Inner polygon.
            out.println(inner.size() + 1);
            out.println(start.x + " " + start.y);
            for (int i = inner.size() - 1; i >= 0; --i) {
                out.println(inner.get(i));
            }
            //8(b).4. Outer polygon.
            out.println(n - 1 + inner.size());
            for (int i = 0; i < inner.size(); ++i) {
                out.println(inner.get(i));
            }
            for (int i = index + 1; i < n; ++i) {
                out.println(pts[i].x + " " + pts[i].y);
            }
            for (int i = 0; i < index; ++i) {
                out.println(pts[i].x + " " + pts[i].y);
            }
        }
        out.close();
    }
}

