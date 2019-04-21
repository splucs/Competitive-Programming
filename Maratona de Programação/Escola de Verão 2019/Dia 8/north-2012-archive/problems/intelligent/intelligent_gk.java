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
/* Author               Georgiy Korneev                           */
/******************************************************************/

import java.io.File;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.List;
import java.util.Scanner;

public class intelligent_gk {
    static Scanner in;
    static PrintWriter out;
    static final int MAX_VARS = 12;
    static final int CHUNK = 32;
    static final int M = (1 << MAX_VARS) / CHUNK;

    char[] line;
    int pos = 0;
    List<Node> nodes = new ArrayList<>();
    Node[] VARS = new Node[MAX_VARS];
    Node NULL = new Node(null, null, null);
    String vars = "";

    enum Op {
        TRUE { int apply(int op1, int op2) { return -1; } },
        FALSE { int apply(int op1, int op2) { return 0; } },
        NOT { int apply(int op1, int op2) { return ~op1; } },
        AND { int apply(int op1, int op2) { return op1 & op2; } },
        OR { int apply(int op1, int op2) { return op1 | op2; } },
        IMP { int apply(int op1, int op2) { return ~op1 | op2; } },
        EQ { int apply(int op1, int op2) { return ~op1 ^ op2; } };

        abstract int apply(int op1, int op2);
    }

    class Node {
        Op op;
        Node op1, op2;
        int[] r = new int[M];

        Node(Op op, Node op1, Node op2) {
            this.op = op;
            this.op1 = op1;
            this.op2 = op2;
        }

        private void calc() {
            for (int i = 0; i < r.length; i++) {
                r[i] = op.apply(op1.r[i], op2.r[i]);
            }
        }
    }

    void run() {
        for (int i = 0; i < VARS.length; i++) {
            VARS[i] = new Node(null, null, null);
        }
        String read = in.nextLine();
        Node root = parse(read);
        int n = vars.length();
        boolean[] f = table(root, n);

        int c = 0;
        for (boolean b : f) {
            if (b) c++;
        }

        if (c == 0) {
            out.println("2\n1 0\n1 0");
            return;
        }
        if (c == 1 << n) {
            out.println("2\n1 0\n1 ~0");
            return;
        }

        if (c < f.length / 2) {
            out.println(c + 1);
            generateAnds(n, f, false);
            generateOr(c);
        } else {
            c = f.length - c;
            out.println(c + 1);
            generateAnds(n, f, true);
            generateNor(c);
        }
    }

    private void generateAnds(int n, boolean[] f, boolean not) {
        boolean[] v = new boolean[n];
        for (int i = 0; i < f.length; i++) {
            if (!f[i] ^ not) continue;
            for (int j = 0; j < n; j++) {
                v[j] = ((i >> j) & 1) == 1;
            }
            generateAnd(v);
        }
    }

    private boolean[] table(Node root, int n) {
        final Node[] nodes = this.nodes.toArray(new Node[this.nodes.size()]);
        for (int v = 0; v < 1 << n; v++) {
            for (int i = 0; i < n; i++) {
                VARS[i].r[v / CHUNK] |= ((v >> i) & 1) << (v % CHUNK);
            }
        }

        for (Node node : nodes) {
            node.calc();
        }

        boolean[] f = new boolean[1 << n];
        for (int v = 0; v < 1 << n; v++) {
            f[v] = ((root.r[v / CHUNK] >> (v % CHUNK)) & 1) == 1;
        }
        return f;
    }

    private Node parse(String s) {
        line = (s.replaceAll("\\s", "") + "#").toCharArray();
        Node root = parseEq();
        expect('#');
        return root;
    }

    Node parseTerm() {
        final char token = nextToken();
        switch (token) {
            case '~': return addNode(Op.NOT, parseTerm(), NULL);
            case '1': return addNode(Op.TRUE, NULL, NULL);
            case '0': return addNode(Op.FALSE, NULL, NULL);
            case '(':
                Node z = parseEq();
                expect(')');
                return z;
            default:
                if ('A' <= token && token <= 'Z') {
                    int index = vars.indexOf(token);
                    if (index == -1) {
                        index = vars.length();
                        vars += token;
                    }
                    return VARS[index];
                }
                throw new AssertionError("Invalid term " + pos);
        }
    }

    Node parseAnd() {
        Node op = parseTerm();
        while (test('&')) {
            op = addNode(Op.AND, op, parseTerm());
        }
        return op;
    }

    Node parseOr() {
        Node op = parseAnd();
        while (test('|')) {
            op = addNode(Op.OR, op, parseAnd());
        }
        return op;
    }

    Node parseImp() {
        Node op = parseOr();
        if (test('-')) {
            expect('>');
            op = addNode(Op.IMP, op, parseImp());
        }
        return op;
    }

    Node parseEq() {
        Node op = parseImp();
        Node prev = null;
        while (test('<')) {
            expect('=');
            expect('>');
            Node next = parseImp();
            if (prev == null) {
                op = addNode(Op.EQ, op, next);
            } else {
                op = addNode(Op.AND, op, addNode(Op.EQ, prev, next));
            }
            prev = next;
        }
        return op;
    }

    private void expect(char ch) {
        if (nextToken() != ch) {
            throw new AssertionError(String.format("%d: '%c' expected, '%c' found", pos, ch, line[pos - 1]));
        }
    }

    private Node addNode(Op op, Node op1, Node op2) {
        Node node = new Node(op, op1, op2);
        nodes.add(node);
        return node;
    }

    char nextToken() {
        return line[pos++];
    }

    boolean test(char ch) {
        if (line[pos] == ch) {
            pos++;
            return true;
        }
        return false;
    }

    private void generateOr(int c) {
        out.print(2 * c);
        for (int i = 0; i < c; i++) {
            out.print(" " + (i + 1) + " ~0");
        }
        out.println();
    }

    private void generateAnd(boolean[] v) {
        out.print(2 * v.length - 1);
        for (int i = 0; i < v.length; i++) {
            if (i != 0) out.print(" 0");
            out.print(" " + (v[i] ? "" : "~") + vars.charAt(i));
        }
        out.println();
    }

    private void generateNor(int c) {
        out.print(2 * c - 1);
        for (int i = 0; i < c; i++) {
            if (i != 0) out.print(" 0");
            out.print(" ~" + (i + 1));
        }
        out.println();
    }


    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("intelligent.in"));
        out = new PrintWriter("intelligent.out");

        new intelligent_gk().run();

        in.close();
        out.close();
    }
}

