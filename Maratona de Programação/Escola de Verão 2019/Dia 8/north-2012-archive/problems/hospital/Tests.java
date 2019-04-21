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
/* Tests                                                          */
/*                                                                */
/* Author               Pavel Mavrin                              */
/******************************************************************/

import java.io.*;
import java.util.*;

public class Tests {
    private static final int MAX_N = 1000;
    private static final int MAX_M = 10000;

    public static void main(String[] args) throws IOException {
        new File("tests").mkdir();
        new Tests().run();
    }

    private void run() {
        // Sample
        printTest(7, 5, new int[][]{{6, 7}, {7}, {2, 7}, {5}, {4}}, "Sample test");

        // Small tests
        for (int n = 2; n <= 3; n++) {
            for (int k = 1; k < n; k++) {
                int z = k * n;
                Set<Integer> tt = new HashSet<Integer>();
                for (int m = 0; m < (1 << z); m++) {
                    boolean ok = true;
                    int[][] a = new int[k][];
                    for (int i = 0; i < k; i++) {
                        int zz = 0;
                        int[] aa = new int[n];
                        int mm = (m >> (n * i)) & ((1 << n) - 1);
                        for (int j = 0; j < n; j++) {
                            if (((mm >> j) & 1) == 1) {
                                aa[zz++] = j;
                                if (j == i) ok = false;
                            }
                        }
                        if (zz == 0) ok = false;
                        a[i] = new int[zz];
                        for (int j = 0; j < zz; j++) {
                            a[i][j] = aa[j] + 1;
                        }
                    }
                    if (ok) {
                        int[] h = new int[n];
                        Arrays.fill(h, 1);
                        for (int i = 0; i < 10; i++) {
                            int[] hh = new int[k];
                            for (int j = 0; j < k; j++) {
                                for (int t : a[j]) {
                                    hh[j] += h[t - 1];
                                }
                            }
                            System.arraycopy(hh, 0, h, 0, k);
                        }
                        int hh = 0;
                        for (int i : h) {
                            hh += i;
                        }
                        if (!tt.contains(hh)) {
                            printTest(n, k, a, "Small test, n = " + n + ", k = " + k);
                            tt.add(hh);
                        }
                    }
                }
            }
        }
        {
            int n = 20;
            for (int k = n - 5; k < n; k++) {
                for (int al = 1; al < n; al += 5) {
                    printRandomTest(n, k, al);
                }
            }
        }
        {
            int n = 1000;
            int k = n - 10;
            for (int al = 1; al <= 10; al++) {
                printRandomTest(n, k, al);
            }
        }
        {
            int n = 1000;
            for (int k = n - 10; k <= n - 2; k++) {
                List<Node> special = new ArrayList<>();
                List<Node> staff = new ArrayList<>();
                for (int i = 0; i < k; i++) {
                    special.add(new Node());
                }
                for (int i = 0; i < n - k; i++) {
                    staff.add(new Node());
                }
                for (int i = 0; i < k; i++) {
                    special.get(i).addEdgeTo(special.get((i + 1) % k));
                }
                for (int i = 0; i < n - k; i++) {
                    staff.get(i).addEdgeTo(special.get(random.nextInt(k)));
                }
                shuffle(special, staff);
                printTest(special, staff, "Big cycle + " + (n - k) + " staff nurses.");
            }
        }
        {
            int n = 1000;
            for (int k = 500; k < n; k = n - ((n - k) / 2)) {
                List<Node> special = new ArrayList<>();
                List<Node> staff = new ArrayList<>();
                for (int i = 0; i < k; i++) {
                    special.add(new Node());
                }
                for (int i = 0; i < n - k; i++) {
                    staff.add(new Node());
                }
                int m = 0;
                for (int i = 0; i < k; i++) {
                    int j = random.nextInt(k);
                    while (j == i) {
                        j = random.nextInt(k);
                    }
                    special.get(i).addEdgeTo(special.get(j));
                    m++;
                }
                for (int i = 0; i < n - k; i++) {
                    staff.get(i).addEdgeTo(special.get(random.nextInt(k)));
                    m++;
                }
                while (m < MAX_M) {
                    int i = random.nextInt(k);
                    int j = random.nextInt(k);
                    while (j == i) {
                        i = random.nextInt(k);
                        j = random.nextInt(k);
                    }
                    special.get(i).addEdgeTo(special.get(j));
                    m++;

                }
                shuffle(special, staff);
                printTest(special, staff, "Big random test with " + (n - k) + " staff nurses.");
            }
        }
        {
            int n = 1000;
            for (int k = 500; k < n; k = n - ((n - k) / 2)) {
                List<Node> special = new ArrayList<>();
                List<Node> staff = new ArrayList<>();
                for (int i = 0; i < k; i++) {
                    special.add(new Node());
                }
                for (int i = 0; i < n - k; i++) {
                    staff.add(new Node());
                }
                int m = 0;
                for (int i = 1; i < k; i++) {
                    int j = random.nextInt(i);
                    special.get(i).addEdgeTo(special.get(j));
                    m++;
                }
                for (int i = 0; i < n - k; i++) {
                    staff.get(i).addEdgeTo(special.get(random.nextInt(k)));
                    m++;
                }
                while (m < MAX_M) {
                    int i = random.nextInt(k);
                    int j = random.nextInt(k);
                    while (j <= i) {
                        i = random.nextInt(k);
                        j = random.nextInt(k);
                    }
                    special.get(i).addEdgeTo(special.get(j));
                    m++;

                }
                shuffle(special, staff);
                printTest(special, staff, "Big random acyclic test with " + (n - k) + " staff nurses.");
            }
        }


    }

    private void printRandomTest(int n, int k, int al) {
        int[][] a = new int[k][];
        for (int i = 0; i < k; i++) {
            int z = random.nextInt(al) + 1;
            a[i] = new int[z];
            boolean[] zz = new boolean[n];
            for (int j = 0; j < z; j++) {
                int x = random.nextInt(n);
                while (x == i || zz[x]) {
                    x = random.nextInt(n);
                }
                zz[x] = true;
                a[i][j] = x + 1;
            }
        }
        printTest(n, k, a, "Random test, n = " + n + ", k = " + k + ", al = " + al);
    }

    private void printTest(int n, int k, int[][] a, String comment) {
        List<Node> nurses = new ArrayList<Node>();
        for (int i = 0; i < n; i++) {
            nurses.add(new Node());
        }
        int s = 0;
        for (int[] ints : a) {
            s += ints.length;
        }
        if (s > MAX_M) {
            throw new RuntimeException();
        }
        for (int i = 0; i < k; i++) {
            for (int j : a[i]) {
                nurses.get(j - 1).addEdgeTo(nurses.get(i));
            }
        }
        printTest(nurses.subList(0, k), nurses.subList(k, n), comment);
    }

    int testNumber = 0;
    Random random = new Random(1446457568679890890L);

    void printTest(List<Node> special, List<Node> staff, String comment) {
        try {
            testNumber++;
            System.out.println("Print test " + testNumber + ": " + comment);
            PrintWriter out = new PrintWriter(String.format("tests/%02d", testNumber));
            int n = special.size() + staff.size();
            int k = special.size();
            int c = 0;
            for (Node node : special) {
                node.id = ++c;
            }
            for (Node node : staff) {
                node.id = ++c;
            }
            out.println(n + " " + k);
            for (Node node : special) {
                List<Node> dst = new ArrayList<Node>();
                for (Edge edge : node.outgoing) {
                    if (edge.initialCp == 0) {
                        dst.add(edge.dst);
                    }
                }
                out.print(dst.size());
                for (Node node1 : dst) {
                    out.print(" " + node1.id);
                }
                out.println();
            }
            out.close();
        } catch (FileNotFoundException e) {
        }

    }

    private void shuffle(List<Node> special, List<Node> staff) {
        Collections.shuffle(special, random);
        Collections.shuffle(staff, random);
        List<Node> all = new ArrayList<Node>(special);
        all.addAll(staff);
        for (Node node : all) {
            Collections.shuffle(node.outgoing);
        }
    }

    class Node {
        int id;
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


}

