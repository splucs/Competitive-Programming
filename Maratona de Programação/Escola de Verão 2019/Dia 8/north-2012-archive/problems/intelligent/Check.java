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
/* Checker                                                        */
/*                                                                */
/* Author               Georgiy Korneev                           */
/******************************************************************/

import ru.ifmo.testlib.Checker;
import ru.ifmo.testlib.InStream;
import ru.ifmo.testlib.Outcome;

import java.util.ArrayList;
import java.util.List;

import static ru.ifmo.testlib.Outcome.Type.OK;
import static ru.ifmo.testlib.Outcome.Type.WA;

public class Check implements Checker {
    public static final int MAX_NODES = 5000;
    public static final int MAX_INPUTS = 5000;
    public static final String INPUTS = "ABCDEFGHIJKL";

    public static class OutcomeException extends RuntimeException {
        final Outcome outcome;

        public OutcomeException(Outcome outcome) {
            this.outcome = outcome;
        }
    }

    public Outcome test(InStream inf, InStream ouf, InStream ans) {
        try {
            check(inf, ouf);
            throw new AssertionError("No outcome");
        } catch (OutcomeException e) {
            return e.outcome;
        }
    }

    private void check(InStream inf, InStream ouf) {
        vars = INPUTS;
        boolean[] f = table(parse(inf.nextLine()), vars.length());

        int n = ouf.nextInt();
        if (n <= 0) {
            quit(WA, "Negative number of nodes: %d", n);
        }
        if (n == 1) {
            quit(WA, "No nodes on first layer, number of nodes: = %d", n);
        }
        if (n > MAX_NODES) {
            quit(WA, "Too many nodes: %d", n);
        }

        int totalInputs = 0;
        vars += "0";
        int[][] layer1 = new int[n - 1][vars.length()];
        for (int i = 0; i < n - 1; i++) {
            int d = ouf.nextInt();
            if (d <= 0) {
                quit(WA, "Invalid number of inputs for node %d: %d", i + 1, d);
            }
            if (d > MAX_INPUTS) {
                quit(WA, "Too many inputs for node %d: %d", i + 1, d);
            }
            totalInputs += d;

            for (int j = 0; j < d; j++) {
                String token = ouf.nextToken();
                boolean not = token.startsWith("~");
                String var = not ? token.substring(1) : token;
                if (var.length() != 1 || vars.indexOf(var.charAt(0)) == -1) {
                    quit(WA, "Invalid input %d for first-layer node %d: %s", j + 1, i + 1, token);
                }
                layer1[i][vars.indexOf(var.charAt(0))] += not ? -1 : 1;
            }
        }


        int d = ouf.nextInt();
        if (d <= 0) {
            quit(WA, "Invalid number of inputs for node %d: %d", n, n);
        }

        totalInputs += d;

        int[] layer2 = new int[n];
        for (int j = 0; j < d; j++) {
            String token = ouf.nextToken();
            boolean not = token.startsWith("~");
            try {
                int var = Integer.parseInt(not ? token.substring(1) : token);
                if (var < 0 || n <= var) {
                    quit(WA, "Invalid variable for input %d of second-layer node %d: %s", (j + 1), n, var);
                }
                layer2[var] += not ? -1 : 1;
            } catch (NumberFormatException e) {
                quit(WA, "Invalid input %d of second-layer node %d: %s: %s", (j + 1), n, token, e.getMessage());
            }
        }

        int[] bits = new int[vars.length()];
        int[] c = new int[layer2.length];
        for (int v = 0; v < f.length; v++) {
            for (int j = 0; j < vars.length(); j++) {
                int nb = (v >> j & 1) * 2 - 1;
                if (bits[j] == nb) {
                    continue;
                }
                int dv = nb - bits[j];
                for (int i = 0; i < layer1.length; i++) {
                    c[i + 1] += layer1[i][j] * dv;
                }
                bits[j] = nb;
            }
            int total = 0;
            for (int i = 0; i < layer2.length; i++) {
                total += layer2[i] * (c[i] > 0 ? 1 : -1);
            }

            boolean axon = total > 0;
            if (axon != f[v]) {
                final StringBuilder sb = new StringBuilder();
                for (int i = 0; i < vars.length() - 1; i++) {
                    sb.append(vars.charAt(i)).append("=").append((v >> i) & 1).append(" ");
                }
                quit(WA, "For %s expected %d, found %d", sb, f[v] ? 1 : 0, axon ? 1 : 0);
            }
        }
        quit(OK, "%d variables, %d nodes, %d inputs", vars.length() - 1, n, totalInputs);
    }

    char[] line;
    int pos = 0;
    List<Node> nodes = new ArrayList<>();
    String vars = "";


    enum Op {
        TRUE { int apply(int op1, int op2) { return -1; } },
        FALSE { int apply(int op1, int op2) { return 0; } },
        VAR { int apply(int op1, int op2) { throw new AssertionError("Cannot apply VAR");} },
        NOT { int apply(int op1, int op2) { return ~op1; } },
        AND { int apply(int op1, int op2) { return op1 & op2; } },
        OR { int apply(int op1, int op2) { return op1 | op2; } },
        IMP { int apply(int op1, int op2) { return ~op1 | op2; } },
        EQ { int apply(int op1, int op2) { return ~op1 ^ op2; } };

        abstract int apply(int op1, int op2);
    }

    class Node {
        Op op;
        int op1, op2;

        Node(Op op, int op1, int op2) {
            this.op = op;
            this.op1 = op1;
            this.op2 = op2;
        }
    }

    static final int CHUNK = 32;

    private boolean[] table(int root, int n) {
        int m = Math.max((1 << n) / CHUNK, 1);
        int[][] q = new int[nodes.size()][m];
        int[][] vars = new int[n][m];
        final Node[] nodes = this.nodes.toArray(new Node[this.nodes.size()]);
        for (int v = 0; v < 1 << n; v++) {
            for (int i = 0; i < n; i++) {
                vars[i][v / CHUNK] |= ((v >> i) & 1) << (v % CHUNK);
            }
        }
        for (int i = 0; i < nodes.length; i++) {
            final Node node = nodes[i];
            if (node.op == Op.VAR) {
                q[i] = vars[node.op1];
            } else {
                for (int j = 0; j < m; j++) {
                    q[i][j] = node.op.apply(q[node.op1][j], q[node.op2][j]);
                }
            }
        }

        boolean[] f = new boolean[1 << n];
        for (int v = 0; v < 1 << n; v++) {
            f[v] = ((q[root][v / CHUNK] >> (v % CHUNK)) & 1) == 1;
        }
        return f;
    }

    private int parse(String s) {
        line = (s.replaceAll("\\s", "") + "#").toCharArray();
        int root = parseEq();
        expect('#');
        return root;
    }

    int parseTerm() {
        final char token = nextToken();
        switch (token) {
            case '~': return addNode(Op.NOT, parseTerm(), 0);
            case '1': return addNode(Op.TRUE, 0, 0);
            case '0': return addNode(Op.FALSE, 0, 0);
            case '(':
                int z = parseEq();
                expect(')');
                return z;
            default:
                if ('A' <= token && token <= 'Z') {
                    int index = vars.indexOf(token);
                    if (index == -1) {
                        index = vars.length();
                        vars += token;
                    }
                    return addNode(Op.VAR, index, 0);
                }
                throw new AssertionError("Invalid term " + pos);
        }
    }

    int parseAnd() {
        int op = parseTerm();
        while (test('&')) {
            op = addNode(Op.AND, op, parseTerm());
        }
        return op;
    }

    int parseOr() {
        int op = parseAnd();
        while (test('|')) {
            op = addNode(Op.OR, op, parseAnd());
        }
        return op;
    }

    int parseImp() {
        int op = parseOr();
        if (test('-')) {
            expect('>');
            op = addNode(Op.IMP, op, parseImp());
        }
        return op;
    }

    int parseEq() {
        int op = parseImp();
        Integer prev = null;
        while (test('<')) {
            expect('=');
            expect('>');
            int next = parseImp();
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

    private int addNode(Op op, int op1, int op2) {
        nodes.add(new Node(op, op1, op2));
        return nodes.size() - 1;
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

    public void quit(Outcome.Type type, final String format, final Object... args) {
        throw new OutcomeException(new Outcome(type, String.format(format, args)));
    }
}

