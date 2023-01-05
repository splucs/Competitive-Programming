/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem C. Chemistry                                           */
/*                                                                */
/* Original idea        Maxim Buzdalov                            */
/* Problem statement    Anton Akhi                                */
/* Test set             Maxim Buzdalov                            */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author               Georgiy Korneev                           */
/******************************************************************/

import java.math.BigInteger;
import java.util.*;
import java.io.*;
import static java.lang.Math.*;

public class chemistry_gk_bi {
    static Scanner in;
    static PrintWriter out;

    // q[0][j][o] -- i atoms, depth = j
    // q[1][j][i] -- i atoms, depth < j
    BigInteger[][][] q;

    BigInteger get(int h, int mf, int... p) {
        int n = p.length;
        if (p[n - 1] > p[n - 2]) {
            return BigInteger.ZERO;
        }

        BigInteger sum = BigInteger.ZERO;
        int[] b = new int[n];
        bits: for (int bits = 0; bits < (1 << n); bits++) {
            int bs = b[0] = bits & 1;
            int s = 0;
            BigInteger prod = q[b[0]][h][p[0]];

            for (int i = 1; i < n; i++) {
                b[i] = (bits >> i) & 1;
                bs += b[i];
                if (p[i - 1] == p[i] && b[i - 1]  < b[i]) continue bits;
                s = p[i - 1] == p[i] && b[i - 1] == b[i] ? s + 1 : 0;
                prod = q[b[i]][h][p[i]].add(BigInteger.valueOf(s)).multiply(prod).divide(BigInteger.valueOf(s + 1));
            }

            if (bs <= n - mf) {
                sum = sum.add(prod);
            }
        }
        return sum;
    }

    void run() {
        int n = in.nextInt();
        q = new BigInteger[2][n / 2 + 1][n + 1];
        for (int i = 0; i < 2; i++) {
            for (int j = 0; j < n / 2 + 1; j++) {
                Arrays.fill(q[i][j], BigInteger.ZERO);
            }
        }
        q[0][0][0] = BigInteger.ONE;

        for (int j = 1; j <= n / 2; j++) {
            q[1][j][0] = BigInteger.ONE;
            System.out.print(j);
            for (int i = 1; i <= n; i++) {
                for (int p1 = j - 1; p1 <= i - 1; p1++) {
                    for (int p2 = 0; p2 <= min(p1, i - 1 - p1); p2++) {
                        q[0][j][i] = q[0][j][i].add(get(j - 1, 1, p1, p2, i - 1 - p1 - p2));
                    }
                }
                q[1][j][i] = q[1][j - 1][i].add(q[0][j - 1][i]);
            }
        }

        BigInteger sum = BigInteger.ZERO;
        for (int d = 1; d <= n; d++) {
            int h = d / 2;
            if (d % 2 == 0) {
                for (int p1 = h; p1 < n; p1++) {
                    sum = sum.add(get(h, 2, p1, n - p1));
                }
            } else {
                for (int p1 = h; p1 <= n - 1; p1++) {
                    for (int p2 = h; p2 <= min(p1, n - 1 - p1); p2++) {
                        for (int p3 = 0; p3 <= min(p2, n - 1 - p1 - p2); p3++) {
                            sum = sum.add(get(h, 2, p1, p2, p3, n - 1 - p1 - p2 - p3));
                        }
                    }
                }
            }
        }
        out.println(sum);
    }

    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("chemistry.in"));
        out = new PrintWriter("chemistry.out");

        while (in.hasNext()) {
            new chemistry_gk_bi().run();
        }

        in.close();
        out.close();
    }
}

