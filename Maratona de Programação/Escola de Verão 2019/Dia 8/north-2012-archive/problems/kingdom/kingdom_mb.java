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

public class kingdom_mb {
    static enum Type {
        START, SPLIT, MERGE, END, REGULAR
    }

    static class Point implements Comparable<Point> {
        static final Map<Point, Point> uniquifier = new HashMap<Point, Point>();
        final int x;
        final int y;

        Type type = null;

        Edge innerEdge;

        public TreeSet<Edge> outs = new TreeSet<Edge>(new Comparator<Edge>() {
            public int compare(Edge lhs, Edge rhs) {
                int lc = compareTo(lhs.target);
                int rc = compareTo(rhs.target);
                if (lc != rc) {
                    return lc - rc;
                } else {
                    return Long.signum(vmulAround(rhs.target, lhs.target));
                }
            }
        });

        private Point(int x, int y) {
            this.x = x;
            this.y = y;
        }

        public int compareTo(Point that) {
            if (y != that.y) return y < that.y ? -1 : 1;
            if (x != that.x) return x < that.x ? -1 : 1;
            return 0;
        }

        private void insertEdge(Edge e) {
            if (outs.isEmpty()) {
                outs.add(e);
                e.prev = e.twin;
                e.twin.next = e;
            } else {
                Edge next = outs.higher(e);
                if (next == null) {
                    next = outs.first();
                }
                Edge prev = outs.lower(e);
                if (prev == null) {
                    prev = outs.last();
                }
                e.twin.next = next;
                next.prev = e.twin;
                e.prev = prev.twin;
                prev.twin.next = e;
                outs.add(e);
            }
        }

        public Edge link(Point that) {
            Edge fw = new Edge(this, that);
            insertEdge(fw);
            that.insertEdge(fw.twin);
            return fw;
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

        Point helper = null;

        boolean visited = false;

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

        public String toString() {
            return source + "--" + target;
        }
    }

    static class Out {
        final double x, y;
        Out(double x, double y) {
            this.x = x;
            this.y = y;
        }

        public void addTo(StringBuilder sb) {
            sb.append(x).append(" ").append(y);
        }
    }

    static Out interpolate(Point p0, Point p1, double t) {
        return new Out(p0.x * (1 - t) + p1.x * t, p0.y * (1 - t) + p1.y * t);
    }

    static void dfs(Face current, Edge entrance, List<Out> answer, double t) {
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
                answer.add(new Out(x, y));
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

    private static void triangulateMonotone(Edge e, List<Edge> allEdges) {
        Edge minSource = e, maxSource = e;
        Edge curr = e;
        int cnt = 0;
        do {
            if (curr.source.compareTo(minSource.source) < 0) {
                minSource = curr;
            }
            if (curr.source.compareTo(maxSource.source) > 0) {
                maxSource = curr;
            }
            ++cnt;
            curr = curr.next;
        } while (curr != e);
        List<Edge> sorted = new ArrayList<Edge>(cnt);
        sorted.add(minSource);
        Edge currUp = minSource.next;
        Edge currDn = minSource.prev;
        while (currUp != maxSource || currDn != maxSource) {
            if (currUp.source.compareTo(currDn.source) < 0) {
                sorted.add(currUp);
                currUp = currUp.next;
            } else {
                sorted.add(currDn);
                currDn = currDn.prev;
            }
        }
        sorted.add(maxSource);

        List<Edge> stack = new ArrayList<Edge>();
        stack.add(sorted.get(0));
        stack.add(sorted.get(1));
        for (int i = 2; i < sorted.size(); ++i) {
            Edge last = stack.get(stack.size() - 1);
            Edge first = stack.get(0);
            curr = sorted.get(i);
            if (curr.next == first) {
                while (curr.target != last.source) {
                    if (last.next == curr && curr.next.next == last) {
                        curr = last.twin;
                    } else {
                        curr = curr.source.link(curr.next.target);
                        allEdges.add(curr);
                        allEdges.add(curr.twin);
                    }
                    new Face(curr.twin);
                }
                stack.clear();
                stack.add(last);
                stack.add(curr);
            } else if (curr.prev == first) {
                while (first.source != last.source) {
                    if (curr.next == last && curr.prev.prev == last) {
                        first = curr.twin;
                    } else {
                        first = first.prev.source.link(first.target);
                        allEdges.add(first);
                        allEdges.add(first.twin);
                    }
                    new Face(first.twin);
                }
                stack.clear();
                stack.add(first);
                stack.add(curr);
            } else if (curr.next == last) {
                while (curr.target != first.source && curr.source.vmulAround(curr.target, curr.next.target) < 0) {
                    stack.remove(stack.size() - 1);
                    curr = curr.source.link(curr.next.target);
                    allEdges.add(curr);
                    allEdges.add(curr.twin);
                    new Face(curr.twin);
                }
                stack.add(curr);
            } else if (curr.prev == last) {
                while (last.source != first.source && last.source.vmulAround(last.prev.source, last.target) > 0) {
                    stack.remove(stack.size() - 1);
                    last = last.prev.source.link(last.target);
                    allEdges.add(last);
                    allEdges.add(last.twin);
                    new Face(last.twin);
                }
                stack.remove(stack.size() - 1);
                stack.add(last);
                stack.add(curr);
            } else {
                throw new AssertionError();
            }
        }
        if (stack.size() != 2) {
            throw new AssertionError();
        }
    }

    public static void main(String[] args) throws IOException {
        Point.uniquifier.clear();

        BufferedReader in = new BufferedReader(new FileReader("kingdom.in"));
        int n = Integer.parseInt(in.readLine());
        Point[] pts = new Point[n];
        for (int i = 0; i < n; ++i) {
            String ln = in.readLine();
            int ws = ln.indexOf(' ');
            pts[i] = Point.make(Integer.parseInt(ln.substring(0, ws)), Integer.parseInt(ln.substring(ws + 1)));
        }
        in.close();

        //1. Adding edges between consecutive vertices.
        List<Edge> allEdges = new ArrayList<Edge>(3 * n + 2);
        Edge anOuterEdge = null;
        for (int i = 0; i < n; ++i) {
            Edge outer = pts[i].link(pts[(i + 1) % n]);
            Edge inner = outer.twin;
            if (anOuterEdge == null) {
                anOuterEdge = outer;
            }
            allEdges.add(outer);
            allEdges.add(inner);
        }

        if (new Face(anOuterEdge).squareImpl() <= 0) {
            throw new AssertionError("Input polygon is not given counterclockwise");
        }

        //2. Determining types of vertices.
        for (Point curr : pts) {
            Iterator<Edge> ei = curr.outs.iterator();
            Edge inner = ei.next();
            if (inner.face != null && inner.face.outer) {
                inner = ei.next();
            }

            if (inner.source.vmulAround(inner.target, inner.prev.source) == 0) {
                throw new AssertionError("Collinear points in input file: " + inner.prev.source + "-" + inner.source + "-" + inner.target);
            }

            curr.innerEdge = inner;
            Point prev = inner.prev.source;
            Point next = inner.target;
            boolean prevL = prev.compareTo(curr) < 0;
            boolean nextL = next.compareTo(curr) < 0;
            if (prevL != nextL) {
                curr.type = Type.REGULAR;
            } else if (prevL) {
                if (curr.vmulAround(prev, next) > 0) {
                    curr.type = Type.END;
                } else {
                    curr.type = Type.MERGE;
                }
            } else {
                if (curr.vmulAround(prev, next) > 0) {
                    curr.type = Type.START;
                } else {
                    curr.type = Type.SPLIT;
                }
            }
        }

        //3.1. Sweepline init.
        Point[] events = pts.clone();
        Arrays.sort(events);
        TreeSet<Edge> edges = new TreeSet<Edge>(new Comparator<Edge>() {
            public int compare(Edge l, Edge r) {
                int vmulLRs = Long.signum(l.source.vmulAround(l.target, r.source));
                int vmulLRt = Long.signum(l.source.vmulAround(l.target, r.target));
                if (vmulLRs == 0 && vmulLRt == 0) {
                    return l.source.compareTo(r.source);
                }
                if (vmulLRs * vmulLRt >= 0) {
                    return +(vmulLRs == 0 ? vmulLRt : vmulLRs);
                }
                int vmulRLs = Long.signum(r.source.vmulAround(r.target, l.source));
                int vmulRLt = Long.signum(r.source.vmulAround(r.target, l.target));
                if (vmulRLs * vmulRLt >= 0) {
                    return -(vmulRLs == 0 ? vmulRLt : vmulRLs);
                }
                throw new AssertionError("Segments " + l + " and " + r + " intersect by interiors");
            }
        });
        //3.2. Sweepline loop.
        for (int i = 0; i < n; ++i) {
            Point curr = events[i];
            switch (curr.type) {
                case START: {
                    curr.innerEdge.helper = curr;
                    edges.add(curr.innerEdge);
                    break;
                }
                case END: {
                    Edge prev = curr.innerEdge.prev;
                    if (prev.helper.type == Type.MERGE) {
                        Edge e = curr.link(prev.helper);
                        allEdges.add(e);
                        allEdges.add(e.twin);
                    }
                    edges.remove(prev);
                    break;
                }
                case SPLIT: {
                    Edge left = edges.lower(curr.innerEdge);
                    Edge e = curr.link(left.helper);
                    allEdges.add(e);
                    allEdges.add(e.twin);
                    left.helper = curr;
                    curr.innerEdge.helper = curr;
                    edges.add(curr.innerEdge);
                    break;
                }
                case MERGE: {
                    Edge prev = curr.innerEdge.prev;
                    if (prev.helper.type == Type.MERGE) {
                        Edge e = curr.link(prev.helper);
                        allEdges.add(e);
                        allEdges.add(e.twin);
                    }
                    edges.remove(prev);
                    Edge left = edges.lower(prev);
                    if (left.helper.type == Type.MERGE) {
                        Edge e = curr.link(left.helper);
                        allEdges.add(e);
                        allEdges.add(e.twin);
                    }
                    left.helper = curr;
                    break;
                }
                case REGULAR: {
                    if (curr.compareTo(curr.innerEdge.target) < 0) {
                        Edge prev = curr.innerEdge.prev;
                        if (prev.helper.type == Type.MERGE) {
                            Edge e = curr.link(prev.helper);
                            allEdges.add(e);
                            allEdges.add(e.twin);
                        }
                        edges.remove(prev);
                        curr.innerEdge.helper = curr;
                        edges.add(curr.innerEdge);
                    } else {
                        Edge left = edges.lower(curr.innerEdge.twin);
                        if (left.helper.type == Type.MERGE) {
                            Edge e = curr.link(left.helper);
                            allEdges.add(e);
                            allEdges.add(e.twin);
                        }
                        left.helper = curr;
                    }
                    break;
                }
            }
        }

        //4. Triangulate monotone polygons.
        for (Edge e : allEdges) {
            if (e.face != null && !e.face.outer) {
                e.face = null;
            }
        }
        List<Edge> newEdges = new ArrayList<Edge>();
        for (Edge e : allEdges) {
            if (e.face == null) {
                triangulateMonotone(e, newEdges);
            }
        }
        allEdges.addAll(newEdges);

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
                        throw new AssertionError(f);
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
                double xt1 = (-B - D) / A;
                double xt2 = (-B + D) / A;
                if (0 < xt1 && xt1 < 0.5) {
                    t = xt1;
                } else if (0 < xt2 && xt2 < 0.5) {
                    t = xt2;
                } else {
                    throw new AssertionError("t1 = " + xt1 + " t2 = " + xt2);
                }
            }

            //8(b).2. Calculating inner points.
            List<Out> inner = new ArrayList<Out>();
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
            StringBuilder sb = new StringBuilder(10000000);
            //8(b).3. Inner polygon.
            sb.append(inner.size() + 1).append("\n");
            sb.append(start.x).append(" ").append(start.y).append("\n");
            for (int i = inner.size() - 1; i >= 0; --i) {
                inner.get(i).addTo(sb);
                sb.append("\n");
            }
            //8(b).4. Outer polygon.
            sb.append(n - 1 + inner.size()).append("\n");
            for (int i = 0; i < inner.size(); ++i) {
                inner.get(i).addTo(sb);
                sb.append("\n");
            }
            for (int i = index + 1; i < n; ++i) {
                sb.append(pts[i].x).append(" ").append(pts[i].y).append("\n");
            }
            for (int i = 0; i < index; ++i) {
                sb.append(pts[i].x).append(" ").append(pts[i].y).append("\n");
            }
            out.append(sb);
        }
        out.close();
    }
}

