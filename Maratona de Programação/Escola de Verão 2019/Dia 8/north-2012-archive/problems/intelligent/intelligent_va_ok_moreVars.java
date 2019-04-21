/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem I. Intelligent Design                                  */
/*                                                                */
/* Original idea        Jury                                      */
/* Problem statement    Dmitry Shtukenberg                        */
/* Test set             Dmitry Shtukenberg                        */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author               Vitaly Aksenov                            */
/******************************************************************/

import java.io.*;
import java.util.*;

public class intelligent_va_ok_moreVars implements Runnable {
    public static void main(String[] args) {
        new Thread(new intelligent_va_ok_moreVars()).start();
    }

    BufferedReader br;
    StringTokenizer in;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (in == null || !in.hasMoreTokens()) {
            in = new StringTokenizer(br.readLine());
        }

        return in.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    int v = 12;
    int all = 1 << v;
    int c = all / 32;

    public enum Operation {
        TRUE {
            int make(int a, int b) {
                return -1;
            }
        },
        FALSE {
            int make(int a, int b) {
                return 0;
            }
        },
        NOT {
            int make(int a, int b) {
                return ~a;
            }
        },
        EQ {
            int make(int a, int b) {
                return ~(a ^ b);
            }
        },
        IMPL {
            int make(int a, int b) {
                return ~a | b;
            }
        },
        OR {
            int make(int a, int b) {
                return a | b;
            }
        },
        AND {
            int make(int a, int b) {
                return a & b;
            }
        };

        abstract int make(int a, int b);
    }

    public class Node {
        Operation op;
        Node l, r;
        int[] ans = new int[c];

        public Node(Operation op, Node l, Node r) {
            this.op = op;
            this.l = l;
            this.r = r;
        }

        public void count() {
            if (op == null)
                return;
            l.count();
            r.count();
            for (int i = 0; i < ans.length; i++) {
                ans[i] = op.make(l.ans[i], r.ans[i]);
            }
        }
    }

    int now = 0;
    char[] s;

    public char next() {
        return s[now++];
    }

    public boolean check(char c) {
        return now != s.length && s[now] == c;
    }

    public Node parseTerm() {
        char c = next();
        switch (c) {
        case '~':
            return new Node(Operation.NOT, parseTerm(), nil);
        case '1':
            return new Node(Operation.TRUE, nil, nil);
        case '0':
            return new Node(Operation.FALSE, nil, nil);
        case '(':
            Node z = parseEq();
            next();
            return z;
        default:
            return vars[c - 'A'];
        }
    }

    public Node parseAnd() {
        Node n = parseTerm();
        while (check('&')) {
            next();
            n = new Node(Operation.AND, n, parseTerm());
        }
        return n;
    }

    public Node parseOr() {
        Node n = parseAnd();
        while (check('|')) {
            next();
            n = new Node(Operation.OR, n, parseAnd());
        }
        return n;
    }

    public Node parseImpl() {
        Node n = parseOr();
        if (check('-')) {
            next();
            next();
            n = new Node(Operation.IMPL, n, parseImpl());
        }
        return n;
    }

    public Node parseEq() {
        Node n = parseImpl();
        Node prev = null;
        while (check('<')) {
            next();
            next();
            next();
            Node now = parseImpl();
            if (prev == null) {
                n = new Node(Operation.EQ, n, now);
            } else {
                n = new Node(Operation.AND, n,
                        new Node(Operation.EQ, prev, now));
            }
            prev = now;
        }
        return n;
    }

    Node[] vars = new Node[v];
    Node nil = new Node(null, null, null);

    public void solve() throws IOException {
        s = nextToken().toCharArray();

        for (int i = 0; i < vars.length; i++) {
            vars[i] = new Node(null, null, null);
        }

        Node n = parseEq();

        for (int i = 0, j = 0; j < c; j++) {
            for (; i < 32 * (j + 1); i++) {
                for (int k = 0; k < v; k++) {
                    if ((i & (1 << k)) != 0) {
                        vars[k].ans[j] += 1 << (i - 32 * j);
                    }
                }
            }
        }

        n.count();
        ArrayList<Integer> trues = new ArrayList<Integer>();
        int z = 0;
        for (int i = 0; i < n.ans.length; i++) {
            for (int j = 0; j < 32; j++) {
                if ((n.ans[i] & (1 << j)) != 0) {
                    trues.add(z);
                }
                z++;
            }
        }

        if (trues.size() == 0) {
            out.println("2\n1 0\n1 0");
            return;
        }

        out.println(trues.size() + 1);
        for (int x : trues) {
            out.print(2 * v - 1);
            for (int i = 0; i < v; i++) {
                out.print(" ");
                if ((x & (1 << i)) == 0) {
                    out.print('~');
                }
                out.print((char) (i + 'A'));
            }
            for (int i = 0; i < v - 1; i++) {
                out.print(" 0");
            }
            out.println();
        }

        out.print(2 * trues.size() - 1);
        for (int i = 0; i < trues.size(); i++) {
            out.print(" " + (i + 1));
        }
        for (int i = 0; i < trues.size() - 1; i++) {
            out.print(" ~0");
        }
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("intelligent.in"));
            out = new PrintWriter("intelligent.out");

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}

