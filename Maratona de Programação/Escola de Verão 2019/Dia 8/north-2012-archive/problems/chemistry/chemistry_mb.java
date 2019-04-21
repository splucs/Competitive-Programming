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
/* Author               Maxim Buzdalov                            */
/******************************************************************/

import java.io.*;
import java.util.*;

public class chemistry_mb {
    long[][] dp;

    private long combi(int[] ns, int[] ms) {
        long rv = dp[ns[0]][ms[0]];
        for (int i = 1; i < ns.length; ++i) {
            int count = 0;
            for (int j = 0; j < i; ++j) {
                if (ns[i] == ns[j] && ms[i] == ms[j]) {
                    ++count;
                }
            }
            rv = rv * (dp[ns[i]][ms[i]] + count) / (count + 1);
        }
        return rv;
    }

    public chemistry_mb(int N) {
        dp = new long[N + 1][N + 1];

        dp[0][0] = dp[1][1] = 1;

        int[] ns = new int[3];
        int[] ms = new int[3];

        for (int n = 2; n <= N; ++n) {
            for (int m = n; m <= N; ++m) {
                long sum = 0;

                int n0 = n - 1;
                for (int m0 = n0; m0 < m; ++m0) {
                    if (dp[n0][m0] == 0) continue;
                    for (int n1 = 0; n1 <= n0; ++n1) {
                        for (int m1 = n1, max1 = Math.min(m - m0 - 1, n0 == n1 ? m0 : m - 1); m1 <= max1; ++m1) {
                            if (dp[n1][m1] == 0) continue;
                            for (int n2 = 0; n2 <= n1; ++n2) {
                                int m2 = m - m0 - m1 - 1;
                                if (dp[n2][m2] == 0) continue;
                                if (n1 != n2 || m2 <= m1) {
                                    ns[0] = n0;
                                    ns[1] = n1;
                                    ns[2] = n2;
                                    ms[0] = m0;
                                    ms[1] = m1;
                                    ms[2] = m2;
                                    sum += combi(ns, ms);
                                }
                            }
                        }
                    }
                }

                dp[n][m] = sum;
            }
        }
    }

    public long solve(int n) {
        if (n < 0 || n >= dp.length) {
            throw new IllegalArgumentException("precalc array has the size of " + (dp.length - 1) + ", arg is " + n);
        }

        long sum = 0;

        int[] ns = new int[4];
        int[] ms = new int[4];

        for (int length = 0; length <= n; ++length) {
            int half = length / 2;
            if (length % 2 == 0) {
                for (int m = 0; m <= n - m; ++m) {
                    long l = dp[half][m];
                    long r = dp[half][n - m];
                    if (m + m == n) {
                        sum += l * (l + 1) / 2;
                    } else {
                        sum += l * r;
                    }
                }
            } else {
                int n0 = half;
                int n1 = half;
                for (int m0 = n0; m0 < n; ++m0) {
                    if (dp[n0][m0] == 0) continue;
                    for (int m1 = n1, max1 = Math.min(m0, n - m0 - 1); m1 <= max1; ++m1) {
                        if (dp[n1][m1] == 0) continue;
                        for (int n2 = 0; n2 <= n1; ++n2) {
                            for (int m2 = n2, max2 = Math.min(n - m0 - m1 - 1, n2 == n1 ? m1 : n - 1); m2 <= max2; ++m2) {
                                if (dp[n2][m2] == 0) continue;
                                for (int n3 = 0; n3 <= n2; ++n3) {
                                    int m3 = n - m0 - m1 - m2 - 1;
                                    if (dp[n3][m3] == 0) continue;
                                    if (n3 != n2 || m3 <= m2) {
                                        ns[0] = n0;
                                        ns[1] = n1;
                                        ns[2] = n2;
                                        ns[3] = n3;
                                        ms[0] = m0;
                                        ms[1] = m1;
                                        ms[2] = m2;
                                        ms[3] = m3;

                                        sum += combi(ns, ms);
                                    }
                                }
                            }
                        }
                    }
                }
            }
        }

        return sum;
    }

    public static void main(String[] args) throws IOException {
        BufferedReader in = new BufferedReader(new FileReader("chemistry.in"));
        int n = Integer.parseInt(in.readLine());
        in.close();

        chemistry_mb solver = new chemistry_mb(n);

        PrintWriter out = new PrintWriter("chemistry.out");
        out.println(solver.solve(n));
        out.close();
    }
}

