/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem F. Final                                               */
/*                                                                */
/* Original idea        Yury Petrov                               */
/* Problem statement    Vitaly Aksenov                            */
/* Test set             Vitaly Aksenov                            */
/******************************************************************/
/* Tests                                                          */
/*                                                                */
/* Author               Vitaly Aksenov                            */
/******************************************************************/

import java.io.*;
import java.util.*;

public class Tests {
    static final int MAXN = 1000;
    static final int MAXX = 1000000;
    static int tests = 1;
    static Random rnd = new Random(239);

    public static void writeTest(int n, int x, int k, int d) throws IOException {
        System.out.println("Writing " + tests + " test!");
        PrintWriter out = new PrintWriter(String.format("tests/%02d", tests++));
        out.println(n + " " + x + " " + k + " " + d);
        out.close();
    }

    public static void genGood(int n, int d) throws IOException {
      if (d == 1) {
            d++;
          }

          int need = d * (d - 1) / 2;

          writeTest(n, rnd.nextInt(MAXX - need) + need, d + rnd.nextInt(n - d + 1), d);
        }

    public static void genFail(int n, int d) throws IOException {
      if (d == 1) {
        d++;
      }
      writeTest(n, d * (d - 1) / 2 - 1, d + rnd.nextInt(n - d + 1), d);
    }

    public static void main(String[] args) throws IOException {
        File dir = new File("tests");
        if (!dir.exists()) {
            dir.mkdir();
        }

        writeTest(3, 4, 2, 2);
        writeTest(3, 5, 2, 2);
        writeTest(2, 5, 2, 1);

        writeTest(1, 1, 1, 1);

        for (int i = 0; i < 2; i++) {
            int n = rnd.nextInt(10) + 2;
            genFail(n, rnd.nextInt(n) + 1);
        }

        for (int i = 0; i < 2; i++) {
             int n = rnd.nextInt(10) + 2;
             genGood(n, rnd.nextInt(n) + 1);
        }

        for (int i = 0; i < 5; i++) {
            int n = rnd.nextInt(MAXN - 1) + 2;
            genFail(n, rnd.nextInt(n) + 1);
        }

        for (int i = 0; i < 5; i++) {
            int n = rnd.nextInt(MAXN - 1) + 2;
            genGood(n, rnd.nextInt(n) + 1);
        }

        for (int i = 0; i < 5; i++) {
            int n = rnd.nextInt(MAXN) + 1;
            int x = rnd.nextInt(MAXX) + 1;
            int k = rnd.nextInt(n) + 1;
            int d = rnd.nextInt(k) + 1;
            writeTest(n, x, k, d);
         }

         for (int i = 0; i < 2; i++) {
           int n = rnd.nextInt(MAXN) + 1;
           int x = rnd.nextInt(MAXX) + 1;
           int k = rnd.nextInt(n) + 1;
           writeTest(n, x, k, 1);
          }

        genFail(MAXN, rnd.nextInt(MAXN) + 1);
        genGood(MAXN, rnd.nextInt(MAXN) + 1);

        writeTest(MAXN, MAXX, MAXN, 1);
        writeTest(MAXN, MAXX - 1, MAXN, 1);
        writeTest(MAXN, MAXX, MAXN, MAXN);
    }
}
