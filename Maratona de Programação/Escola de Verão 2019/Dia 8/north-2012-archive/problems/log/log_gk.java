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
/* Author               Georgiy Korneev                           */
/******************************************************************/

import java.io.*;
import java.util.*;

public class log_gk {
    static Scanner in;
    static PrintWriter out;

    Node spans = NULL;
    Map<String, Integer> indices = new HashMap<>();

    private int getIndex(String value) {
        Integer index = indices.get(value);
        if (index == null) {
            index = indices.size();
            indices.put(value, index);
        }
        return index;
    }

    void run() {
        int n = in.nextInt();
        for (int i = 0; i < n; i++) {
            switch (in.next()) {
                case "+":
                    add(in.nextInt() - 1, in.nextInt(), getIndex(in.next()));
                    break;
                case "?":
                    query(in.nextInt() - 1, in.nextInt() - 1);
                    break;
                case "-":
                    remove(in.nextInt() - 1, in.nextInt());
                    break;
                default:
                    throw new AssertionError("Unknown operation");
            }
        }
    }

    private void query(int l, int r) {
        BitSet set = new BitSet();
        spans.query(set, l, r);
        out.println(set.cardinality());
    }

    void add(int index, int count, int value) {
        spans = spans.add(index, new Node(count, value));
    }

    void remove(int index, int count) {
        spans = spans.remove(index, index + count);
    }

    static final Node NULL = new Node();
    static class Node {
        static final Random random = new Random(34583051);

        final int y;
        Node left = NULL;
        Node right = NULL;
        int length, sum;
        int value;
        BitSet all = new BitSet();

        Node() {
            y = 0;
        }

        Node(int length, int value) {
            this.length = length;
            this.value = value;
            y = random.nextInt();
        }

        void updateSum() {
            sum = left.sum + length + right.sum;
            all.clear();
            all.or(left.all);
            all.or(right.all);
            all.set(value);
        }

        Node setLeft(Node node) {
            left = node;
            updateSum();
            return this;
        }

        Node setRight(Node node) {
            right = node;
            updateSum();
            return this;
        }

        Node[] split(int index) {
            if (this == NULL) {
                return new Node[]{NULL, NULL};
            }
            if (left.sum < index) {
                Node[] result = right.split(index - left.sum - length);
                result[0] = setRight(result[0]);
                return result;
            } else {
                Node[] result = left.split(index);
                result[1] = setLeft(result[1]);
                return result;
            }
        }


        static Node merge(Node left, Node right) {
            if (left == NULL) {
                return right;
            }
            if (right == NULL) {
                return left;
            }
            if (left.y < right.y) {
                return left.setRight(merge(left.right, right));
            } else {
                return right.setLeft(merge(left, right.left));
            }
        }

        public void query(BitSet set, int l, int r) {
            if (this == NULL) {
                return;
            }
            if (left.sum + length <= l) {
                right.query(set, l - left.sum - length, r - left.sum - length);
            } else if (r < left.sum) {
                left.query(set, l, r);
            } else {
                set.set(value);
                left.queryLeft(set, l);
                right.queryRight(set, r - left.sum - length);
            }
        }

        private void queryRight(BitSet set, int r) {
            if (this == NULL) {
                return;
            }
            if (r < left.sum) {
                left.queryRight(set, r);
            } else {
                set.or(left.all);
                set.set(value);
                if (left.sum + length <= r) {
                    right.queryRight(set, r - left.sum - length);
                }
            }
        }

        private void queryLeft(BitSet set, int l) {
            if (this == NULL) {
                return;
            }
            if (left.sum + length <= l) {
                right.queryLeft(set, l - left.sum - length);
            } else {
                set.or(right.all);
                set.set(value);
                if (l <= left.sum) {
                    left.queryLeft(set, l);
                }
            }
        }

        public Node remove(int l, int r) {
            if (this == NULL) {
                return NULL;
            }

            int nr = r - left.sum - length;
            if (left.sum + length <= l) {
                return setRight(right.remove(l - left.sum - length, nr));
            } else if (r < left.sum) {
                return setLeft(left.remove(l, r));
            } else {
                if (l <= left.sum && left.sum + length <= r) {
                    return merge(left.removeLeft(l), right.removeRight(nr));
                }

                length = length - (Math.min(length, r - left.sum) - Math.max(0, l - left.sum));
                return setLeft(left.removeLeft(l)).setRight(right.removeRight(nr));
            }
        }

        private Node removeLeft(int l) {
            if (this == NULL) {
                return NULL;
            }
            if (l <= left.sum) {
                return left.removeLeft(l);
            } else {
                int nl = l - left.sum - length;
                length = Math.min(l - left.sum, length);
                return setRight(right.removeLeft(nl));
            }
        }


        private Node removeRight(int r) {
            if (this == NULL) {
                return NULL;
            }
            if (left.sum + length <= r) {
                return right.removeRight(r - left.sum - length);
            } else {
                length = length - Math.max(r - left.sum, 0);
                return setLeft(left.removeRight(r));
            }
        }

        static class FindAndCutResult {
            Node node;
            int value;
            int after;

            FindAndCutResult(Node node, int value, int after) {
                this.node = node;
                this.value = value;
                this.after = after;
            }
        }

        public Node add(int index, Node node) {
            FindAndCutResult result = findAndCut(index);
            Node root = result.node;
            if (result.after != 0) {
                root = root.addBefore(index, new Node(result.after, result.value));
            }
            root = root.addBefore(index, node);
            return root;
        }

        private Node addBefore(int index, Node node) {
            if (this == NULL) {
                node.updateSum();
                return node;
            }
            if (node.y > y) {
                if (index < left.sum + length) {
                    return setLeft(left.addBefore(index, node));
                } else {
                    return setRight(right.addBefore(index - left.sum - length, node));
                }
            } else {
                Node[] result = split(index);
                return node.setLeft(result[0]).setRight(result[1]);
            }
        }

        public FindAndCutResult findAndCut(int index) {
            if (this == NULL) {
                return new FindAndCutResult(NULL, -1, 0);
            }
            if (index < left.sum) {
                FindAndCutResult result = left.findAndCut(index);
                result.node = setLeft(result.node);
                return result;
            }
            int length = left.sum + this.length;
            if (index < length) {
                int after = length - index;
                int before = this.length - (length - index);
                this.length = before;
                updateSum();
                return new FindAndCutResult(before > 0 ? this : merge(left, right), value, after);
            }
            FindAndCutResult result = right.findAndCut(index - length);
            result.node = setRight(result.node);
            return result;
        }

        @Override
        public String toString() {
            if (this == NULL) {
                return "";
            }
            return left + " " + length + "@" + value + " " + right;
        }
    }
    static class Scanner {
        final BufferedReader reader;
        StringTokenizer tokenizer = new StringTokenizer("");

        public Scanner(File file) throws FileNotFoundException {
            reader = new BufferedReader(new FileReader(file));
        }

        public int nextInt() {
            return Integer.parseInt(next());
        }

        public String next() {
            while (!tokenizer.hasMoreTokens()) {
                try {
                    tokenizer = new StringTokenizer(reader.readLine());
                } catch (IOException e) {
                    throw new AssertionError();
                }
            }
            return tokenizer.nextToken();
        }

        public void close() {
        }
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("log.in"));
        out = new PrintWriter("log.out");

        new log_gk().run();

        in.close();
        out.close();
    }
}
