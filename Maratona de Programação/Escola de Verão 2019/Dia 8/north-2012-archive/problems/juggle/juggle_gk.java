/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem J. Juggle with Criteria                                */
/*                                                                */
/* Original idea        Mikhail Dvorkin                           */
/* Problem statement    Mikhail Dvorkin                           */
/* Test set             Georgiy Korneev                           */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author               Georgiy Korneev                           */
/******************************************************************/

import java.io.File;
import java.io.PrintWriter;
import java.util.ArrayList;
import java.util.Arrays;
import java.util.List;
import java.util.Scanner;

public class juggle_gk {
    static Scanner in;
    static PrintWriter out;

    int c1(int[] p) {
        int r = 0;
        for (int i = 0; i < p.length; i++) {
            for (int j = i + 1; j < p.length; j++) {
                if (p[i] > p[j]) r++;
            }
        }
        return r;
    }

    int c2(int[] p) {
        int r = 0;
        for (int i = 1; i < p.length; i++) {
            if (p[i - 1] > p[i]) r++;
        }
        return r;
    }

    int c3(int[] p) {
        int[] z = new int[p.length];
        int r = 0;
        for (int i = 0; i < p.length; i++) {
            for (int j = 0; j < i; j++) {
                if (p[j] < p[i]) {
                    z[i] = Math.max(z[j], z[i]);
                }
            }
            z[i]++;
            r = Math.max(r, z[i]);
        }
        return r;
    }

    int c4(int[] p) {
        int r = 1;
        int z = 1;
        for (int i = 1; i < p.length; i++) {
            if (p[i] > p[i - 1]) {
                z++;
            } else {
                z = 1;
            }
            r = Math.max(r, z);
        }
        return r;
    }

    int c5(int[] p) {
        int r = 0;
        for (int i = 0; i < p.length; i++) {
            if (p[i] == i) {
                r++;
            }
        }
        return r;
    }


    int[] restore(int n, int r) {
        boolean[] u = new boolean[n];
        int[] p = new int[n];
        for (int i = 0; i < n; i++) {
            int v = r % (n - i);
            r /= (n - i);
            for (int j = 0; j < n; j++) {
                if (!u[j] && v-- == 0) {
                    u[j] = true;
                    p[i] = j;
                }
            }
        }
        return p;
    }

    int length;
    void run() {
        int n = in.nextInt();
        length = in.nextInt();
        in.nextLine();
        int[][][] answers = calculateAnswers(Math.min(7, length));
        for (int i = 0; i < n; i++) {
            char[] input = in.nextLine().toCharArray();
            int target = 0;
            for (int k = 0; k < 5; k++) {
                int d = input[k] == '=' ? 0 : input[k] == '<' ? -1 : 1;
                target = target * 3 + d;
            }
            if (answers[target + answers.length / 2] != null) {
                out.println("Exists");
                for (int[] p : answers[target + answers.length / 2]) {
                    for (int j : p) {
                        out.print((j + 1) + " ");
                    }
                    out.println();
                }
            } else {
                out.println("Not exists");
            }
        }
    }

    int[][][] calculateAnswers(int n) {
        int f = 1;
        for (int i = 1; i <= n; i++) {
            f *= i;
        }
        List<int[]> c = new ArrayList<>();
        List<int[]> permutations = new ArrayList<>();
        List<int[]> extended = new ArrayList<>();

        for (int q = 0; q < f; q++) {
            int[] p;
            if (n == length) {
                p = restore(n, q);
            } else {
                int[] p1 = restore(n, q);
                p = new int[n + 1];
                for (int i = 0; i < n; i++) {
                    p[i] = p1[i] + 1;
                }
            }
            permutations.add(p);
            c.add(new int[]{c1(p), c2(p), c3(p), c4(p), c5(p)});
            extended.add(extend(p));
        }
        int found = 0;
        final int MAX_C = 3 * 3 * 3 * 3 * 3;
        int[][][] answers = new int[MAX_C][][];
        for (int i = 0; i < permutations.size(); i++) {
            for (int j = 0; j < permutations.size(); j++) {
                int r = 0;
                int[] ci = c.get(i);
                int[] cj = c.get(j);
                for (int k = 0; k < 5; k++) {
                    int d = Integer.compare(ci[k], cj[k]);
                    r = r * 3 + d;
                }
                if (answers[r + answers.length / 2] == null) {
                    answers[r + answers.length / 2] = new int[][]{extended.get(i), extended.get(j)};
                    if (answers[r + answers.length / 2] != null) {
                        found++;
                        if (found == MAX_C) {
                            return answers;
                        }
                    }
                }
            }
        }
        return answers;
    }

    int[] extend(final int[] p) {
        int[] r = new int[length];
        for (int i = 0; i < p.length; i++) {
            r[i] = p[i];
        }
        for (int i = p.length; i < length; i++) {
            r[i] = length - 1 - (i - p.length);  
        }
        return r;
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("juggle.in"));
        out = new PrintWriter("juggle.out");

        new juggle_gk().run();

        in.close();
        out.close();
    }
}

