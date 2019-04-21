/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem B. Battleship                                          */
/*                                                                */
/* Original idea        Anton Bannykh                             */
/* Problem statement    Anton Bannykh                             */
/* Test set             Anton Bannykh                             */
/******************************************************************/
/* Tests                                                          */
/*                                                                */
/* Author               Anton Bannykh                             */
/******************************************************************/

import java.io.*;
import java.util.*;

public class Tests {

    public static void main(String[] args) throws IOException {
        new File("tests").mkdir();
        genSample();
        genTest(3, 4);
        genTest(0, 0);
        genTest(0, 9);
        genTest(9, 0);
        genTest(9, 9);
        genTest(0, 8);
        genTest(8, 0);
        genTest(1, 0);
        genTest(0, 1);
        genTest(9, 1);
        for (int i = 0; i < 10; i++) {
            genTest(i, random.nextInt(10));
            genTest(random.nextInt(10), i);
        }
        for (int i = 0; i < 10; ++i) {
            genTest(random.nextInt(10), random.nextInt(10));
        }
    }

    final static Random random = new Random(1893842);
    static int testNumber = 1;

    static void genTest(int li, int lj) throws IOException {
        int[] p = new int[99];
        for (int i = 0; i < p.length; ++i) {
            int j = random.nextInt(i + 1);
            p[i] = p[j];
            p[j] = i;
        }
        PrintWriter out = new PrintWriter(String.format("tests/%02d", testNumber++));
        int m = 0;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (j > 0) out.print(" ");
                if (i == li && j == lj) {
                    out.print(100);
                } else {
                    out.print(p[m++] + 1);
                }
            }
            out.println();
        }
        out.close();
    }

    static void genSample()  throws IOException {
        PrintWriter out = new PrintWriter(String.format("tests/%02d", testNumber++));
        out.println("1 2 3 4 5 6 7 8 9 10");
        out.println("36 37 38 39 40 41 42 43 44 11");
        out.println("35 64 65 66 67 68 69 70 45 12");
        out.println("34 63 84 85 86 87 88 71 46 13");
        out.println("33 62 83 96 97 98 89 72 47 14");
        out.println("32 61 82 95 100 99 90 73 48 15");
        out.println("31 60 81 94 93 92 91 74 49 16");
        out.println("30 59 80 79 78 77 76 75 50 17");
        out.println("29 58 57 56 55 54 53 52 51 18");
        out.println("28 27 26 25 24 23 22 21 20 19");
        out.close();
    }

}

