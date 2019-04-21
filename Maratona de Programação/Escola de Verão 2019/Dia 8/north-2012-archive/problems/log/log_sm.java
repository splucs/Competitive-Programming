/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem L. Log Analysis                                        */
/*                                                                */
/* Original idea        Georgiy Korneev                           */
/* Problem statement    Georgiy Korneev                           */
/* Test set             Georgiy Korneev                           */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author               Sergey Melnikov                           */
/******************************************************************/

import java.io.*;
import java.util.Random;
import java.util.StringTokenizer;

public class log_sm {

    class Node {
        Node l, r;
        int y;
        int number;
        int sum;
        int type;
        int or;

        Node(Node l, Node r, int y, int number, int type) {
            this.l = l;
            this.r = r;
            this.y = y;
            this.number = number;
            this.type = type;
            this.or = this.type;
            this.sum = this.number;
        }
    }

    void update(Node a) {
        a.or = ((a.l == null) ? 0 : a.l.or) | ((a.r == null) ? 0 : a.r.or) | a.type;
        a.sum = ((a.l == null) ? 0 : a.l.sum) + ((a.r == null) ? 0 : a.r.sum) + a.number;
    }

    Node merge(Node a, Node b) {
        if (a == null) {
            return b;
        }
        if (b == null) {
            return a;
        }
        if (a.y > b.y) {
            a.r = merge(a.r, b);
            update(a);
            return a;
        } else {
            b.l = merge(a, b.l);
            update(b);
            return b;
        }
    }

    int getSum(Node a) {
        if (a == null) {
            return 0;
        }
        return a.sum;
    }

    Node[] split(Node a, int k) {
        if (a == null) {
            if (k == 0) {
                return new Node[2];
            } else {
                throw new AssertionError();
            }
        }
        int leftSize = getSum(a.l);
        if (k <= leftSize) {
            Node[] r = split(a.l, k);
            a.l = r[1];
            update(a);
            r[1] = a;
            return r;
        } else if (k < leftSize + a.number) {
            Node b = new Node(null, a.r, a.y, a.number, a.type);
            a.r = null;
            int oldNUmber = a.number;
            a.number = k - leftSize;
            b.number = oldNUmber - a.number;
            update(a);
            update(b);
            return new Node[]{a, b};
        } else {
            Node[] r = split(a.r, k - leftSize - a.number);
            a.r = r[0];
            update(a);
            r[0] = a;
            return r;
        }
    }

    Node getLast(Node a) {
        if (a.r == null) {
            return a;
        } else {
            return getLast(a.r);
        }
    }

    Node addToLast(Node a, int number) {
        if (a.r == null) {
            a.number += number;
            update(a);
            return a;
        } else {
            a.r = addToLast(a.r, number);
            update(a);
            return a;
        }
    }

    Node removeFirst(Node a) {
        if (a.l == null) {
            return a.r;
        } else {
            a.l = removeFirst(a.l);
            update(a);
            return a;
        }
    }

    Node getFirst(Node a) {
        if (a.l == null) {
            return a;
        } else {
            return getFirst(a.l);
        }
    }

    Node carefulMerge(Node a, Node b) {
        if (a == null || b == null) {
            return merge(a, b);
        }
        Node aLast = getLast(a);
        Node bFirst = getFirst(b);
        if (aLast.type == bFirst.type) {
            a = addToLast(a, bFirst.number);
            b = removeFirst(b);
        }
        return merge(a, b);
    }

    Random rand = new Random(1);

    void solve() throws IOException {
        int n = nextInt();
        Node root = null;
        for (int i = 0; i < n; i++) {
            String op = nextToken();
            if (op.equals("+")) {
                int index = nextInt();
                int number = nextInt();
                int type = nextToken().charAt(0) - 'a';
                Node newNode = new Node(null, null, rand.nextInt(), number, 1 << type);
                Node[] r = split(root, index - 1);
                root = carefulMerge(carefulMerge(r[0], newNode), r[1]);
            } else if (op.equals("-")) {
                int index = nextInt();
                int number = nextInt();
                Node[] r1 = split(root, index - 1);
                Node[] r2 = split(r1[1], number);
                root = carefulMerge(r1[0], r2[1]);
            } else if (op.equals("?")) {
                int index1 = nextInt();
                int index2 = nextInt();
                Node[] r1 = split(root, index1 - 1);
                Node[] r2 = split(r1[1], index2 - index1 + 1);
                out.println(Integer.bitCount(r2[0].or));
                root = carefulMerge(r1[0], carefulMerge(r2[0], r2[1]));
            }
        }
    }

    StringTokenizer st;
    BufferedReader br;
    PrintWriter out;

    void run() throws IOException {
        br = new BufferedReader(new FileReader("log.in"));
        out = new PrintWriter("log.out");
        solve();
        out.close();
    }

    String nextToken() throws IOException {
        while (st == null || !st.hasMoreTokens()) {
            st = new StringTokenizer(br.readLine());
        }
        return st.nextToken();
    }

    int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public static void main(String[] args) throws IOException {
        new log_sm().run();
    }
}

