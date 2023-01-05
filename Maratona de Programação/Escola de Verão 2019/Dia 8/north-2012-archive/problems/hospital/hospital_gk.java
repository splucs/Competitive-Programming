/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem H. Hospital                                            */
/*                                                                */
/* Original idea        Pavel Mavrin                              */
/* Problem statement    Pavel Mavrin                              */
/* Test set             Pavel Mavrin                              */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author               Georgiy Korneev                           */
/******************************************************************/

import java.io.File;
import java.io.PrintWriter;
import java.util.*;

public class hospital_gk {
    static Scanner in;
    static PrintWriter out;

    boolean[][] u;
    boolean[][] v;
    Graph graph;

    public static class Arc {
        final int begin, end;
        int capacity;
        Arc reverse;

        public Arc(int begin, int end) {
            this.begin = begin;
            this.end = end;
        }
    }

    int n;
    void run() {
        n = in.nextInt();
        int k = in.nextInt();

        graph = new Graph(2 * n + 1);

        for (int i = 1; i <= n; i++) {
            graph.addCapacity(i, i + n);
        }
        for (int i = 1; i <= k; i++) {
            int d = in.nextInt();
            for (int j = 0; j < d; j++) {
                graph.addCapacity(in.nextInt() + n, i);
            }
        }
        for (int i = k + 1; i <= n; i++) {
            graph.addCapacity(0, i);
        }

        u = new boolean[2][2 * n + 1];
        v = new boolean[2 * n + 1][2 * n + 1];

        dfs(0, 0);
        int cn = 0;
        int cp = 0;
        for (int i = 1; i <= n; i++) {
            if (u[0][i + n]) {
                for (int j = i + 1; j <= n; j++) {
                    if (u[0][j + n] && !v[i + n][j + n]) cp++;
                }
            } else {
                cn++;
            }
        }
        out.println(cn);
        for (int i = 1; i <= n; i++) {
            if (!u[0][i]) out.print(i + " ");
        }
        out.println();
        out.println(cp);
        if (cp <= 10000) {
            for (int i = 1; i <= n; i++) {
                if (u[0][i + n]) {
                    for (int j = i + 1; j <= n; j++) {
                        if (u[0][j + n] && !v[i + n][j + n]) out.println(i + " " + j);
                    }
                }
            }
        }
    }

    private void dfs(int level, int i) {
        if (u[level][i]) {
            return;
        }
        u[level][i] = true;
        if (level < 1 && n < i) {
            u[level + 1] = v[i];
            dfs(level + 1, 0);
        }
        for (Arc arc : graph.getArcs(i)) {
            if (arc.capacity > 0) {
                arc.capacity--;
                arc.reverse.capacity++;
                dfs(level, arc.end);
                arc.capacity++;
                arc.reverse.capacity--;
            }
        }
    }

    public static class Graph {
        final List<Map<Integer, Arc>> arcsMap = new ArrayList<>();
        final List<List<Arc>> arcsList = new ArrayList<>();

        Graph(int n) {
            for (int i = 0; i < n; i++) {
                arcsMap.add(new HashMap<Integer, Arc>());
                arcsList.add(new ArrayList<Arc>());
            }
        }

        Iterable<Arc> getArcs(int i) {
            return arcsList.get(i);
        }

        void setArc(int i, int j, Arc arc) {
            arcsMap.get(i).put(j, arc);
            arcsList.get(i).add(arc);
        }

        Arc getArc(int i, int j) {
            return arcsMap.get(i).get(j);
        }

        private void addCapacity(int i, int j) {
            Arc arc = getArc(i, j);
            if (arc == null) {
                arc = new Arc(i, j);
                Arc reverse = new Arc(j, i);
                arc.reverse = reverse;
                reverse.reverse = arc;
                setArc(i, j, arc);
                setArc(j, i, reverse);
            }
            arc.capacity++;
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("hospital.in"));
        out = new PrintWriter("hospital.out");

        new hospital_gk().run();

        in.close();
        out.close();
    }
}

