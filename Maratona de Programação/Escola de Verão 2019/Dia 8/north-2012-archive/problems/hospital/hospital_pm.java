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
import java.util.List;
import java.util.StringTokenizer;

public class hospital_pm {

    private void run() {
        int n = nextInt();
        int k = nextInt();

        Node[][] nodes = new Node[2][n + 1];
        for (int j = 0; j < 2; j++) {
            for (int i = 0; i < n + 1; i++) {
                nodes[j][i] = new Node();
            }
        }
        for (int i = 0; i < n + 1; i++) {
            nodes[0][i].addEdgeTo(nodes[1][i]);
        }

        for (int i = 0; i < k; i++) {
            int d = nextInt();
            for (int j = 0; j < d; j++) {
                int x = nextInt();
                nodes[1][x].addEdgeTo(nodes[0][i + 1]);
            }
        }
        for (int i = k + 1; i <= n; i++) {
            nodes[1][0].addEdgeTo(nodes[0][i]);
        }


        boolean[] bad = new boolean[n + 1];
        boolean[][] badPair = new boolean[n + 1][n + 1];

        for (int i = 1; i <= k; i++) {
            for (Node[] nodes1 : nodes) {
                for (Node node : nodes1) {
                    node.mark = false;
                    for (Edge edge : node.outgoing) {
                        edge.cp = edge.initialCp;
                    }
                }
            }
            if (dfs(nodes[1][0], nodes[1][i])) {
                for (Node[] nodes1 : nodes) {
                    for (Node node : nodes1) {
                        node.mark = false;
                    }
                }
                dfs(nodes[1][0], null);
                for (int j = 0; j <= n; j++) {
                    if (!nodes[1][j].mark) {
                        badPair[i][j] = true;
                    }
                }
            } else {
                bad[i] = true;
            }
        }

        List<String> res1 = new ArrayList<String>();
        List<String> res2 = new ArrayList<String>();

        for (int i = 1; i <= k; i++) {
            if (bad[i]) res1.add("" + i);
        }
        for (int i = 1; i <= k; i++)
            if (!bad[i]) {
                for (int j = i + 1; j <= n; j++)
                    if (!bad[j]) {
                        if (badPair[i][j]) res2.add(i + " " + j);
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

    public hospital_pm(String inputFileName, String outputFileName) {
        try {
            br = new BufferedReader(new FileReader(inputFileName));
            out = new PrintWriter(outputFileName);
        } catch (FileNotFoundException e) {
        }
    }

    public static void main(String[] args) {
        new hospital_pm("hospital.in", "hospital.out").run();
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

