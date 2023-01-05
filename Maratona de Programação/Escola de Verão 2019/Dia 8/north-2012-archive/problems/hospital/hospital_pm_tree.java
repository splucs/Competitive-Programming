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
/* Author               Pavel Mavrin                              */
/******************************************************************/

import java.io.*;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.StringTokenizer;

public class hospital_pm_tree {

    private void run() {
        int n = nextInt();
        int k = nextInt();

        Node[] nodes = new Node[n + 1];
        for (int i = 0; i < n + 1; i++) {
            nodes[i] = new Node();
        }
        for (int i = 0; i < k; i++) {
            int d = nextInt();
            for (int j = 0; j < d; j++) {
                int x = nextInt();
                nodes[x - 1].addEdgeTo(nodes[i]);
            }
        }
        for (int i = k; i < n; i++) {
            nodes[n].addEdgeTo(nodes[i]);
        }

        boolean[][] a = new boolean[n][n];

        boolean[] bad = new boolean[n + 1];
        dfs(nodes[n], null);
        for (int j = 0; j < n; j++) {
            bad[j] = !nodes[j].mark;
        }

        for (int i = 0; i < n; i++) if (!bad[i]) {
            for (Node node : nodes) {
                node.mark = false;
            }
            for (Edge edge  : nodes[i].outgoing) {
                edge.rev.cp = 0;
            }
            dfs(nodes[n], null);
            for (int j = 0; j < n; j++) if (!bad[j]) {
                a[i][j] = !nodes[j].mark;
            }
            for (Edge edge  : nodes[i].outgoing) {
                edge.rev.cp = edge.rev.initialCp;
            }
        }

//        for (int i = 0; i < n; i++) {
//            for (int j = 0; j < n; j++) {
//                System.out.print(a[i][j] ? "1" : "0");
//            }
//            System.out.println();
//        }

        int[] d = new int[n];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                if (a[i][j]) {
                    d[j]++;
                }
            }
        }

        int[] p = new int[n];
        Arrays.fill(p, -1);
        for (int i = 0; i < n; i++) if (!bad[i]) {
            for (int j = 0; j < n; j++) if (a[j][i] && d[j] == d[i] - 1) {
                p[i] = j;
            }
        }

//        System.out.println(Arrays.toString(d));
//        System.out.println(Arrays.toString(p));

        int[] c = new int[n];
        Arrays.fill(c, -1);

        for (int i = 0; i < n; i++) {
            dfs2(p, c, i);
        }

//        System.out.println(Arrays.toString(c));

        List<String> res1 = new ArrayList<String>();
        List<String> res2 = new ArrayList<String>();

        for (int i = 0; i < k; i++) {
            if (bad[i]) res1.add("" + (i + 1));
        }
        for (int i = 0; i < k; i++)
            if (!bad[i]) {
                for (int j = i + 1; j < n; j++)
                    if (!bad[j]) {
                        if (c[i] == c[j] || c[i] == j || c[j] == i) res2.add((i + 1) + " " + (j + 1));
                    }
            }

        out.println(res1.size());
        for (String s : res1) {
            out.println(s);
        }
        out.println(res2.size());
        if (res2.size() <= 10000) {
            for (String s : res2) {
                out.println(s);
            }
        }

        out.close();

    }

    private void dfs2(int[] p, int[] c, int i) {
        if (c[i] >= 0) return;
        if (p[i] == -1) {
            c[i] = i;
        } else {
            dfs2(p, c, p[i]);
            c[i] = c[p[i]];
        }
    }

    private boolean dfs(Node x, Node sink) {
        if (x.mark) return false;
        x.mark = true;
        if (x == sink) return true;
        for (Edge edge : x.outgoing) {
            if (edge.cp > 0 && dfs(edge.dst, sink)) {
                edge.cp--;
                edge.rev.cp++;
                return true;
            }
        }
        return false;
    }

    class Node {
        List<Edge> outgoing = new ArrayList<Edge>();
        public boolean mark;

        void addEdgeTo(Node dst) {
            Edge there = new Edge(this, dst, 1);
            Edge back = new Edge(dst, this, 0);
            there.rev = back;
            back.rev = there;
            outgoing.add(there);
            dst.outgoing.add(back);
        }
    }

    class Edge {
        Node src;
        Node dst;
        Edge rev;
        int cp;
        int initialCp;

        Edge(Node src, Node dst, int cp) {
            this.src = src;
            this.dst = dst;
            this.cp = cp;
            this.initialCp = cp;
        }
    }


    // Reading

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;

    public hospital_pm_tree(String inputFileName, String outputFileName) {
        try {
            br = new BufferedReader(new FileReader(inputFileName));
            out = new PrintWriter(outputFileName);
        } catch (FileNotFoundException e) {
        }
    }

    public static void main(String[] args) {
        new hospital_pm_tree("hospital.in", "hospital.out").run();
    }

    private int nextInt() {
        return Integer.parseInt(nextString());
    }

    private String nextString() {
        while (st == null || !st.hasMoreTokens()) {
            try {
                st = new StringTokenizer(br.readLine());
            } catch (IOException e) {
                return "";
            }
        }
        return st.nextToken();
    }
}

