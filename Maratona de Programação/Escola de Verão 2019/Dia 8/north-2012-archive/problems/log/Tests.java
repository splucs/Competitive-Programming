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
/* Tests                                                          */
/*                                                                */
/* Author               Georgiy Korneev                           */
/******************************************************************/

import java.io.*;
import java.util.*;

public class Tests {
    int testNo = 0;
    PrintWriter out;
    static PrintWriter descriptions;
    Random random = new Random(938749237);

    static int MAX_NUMBER = 10000;

    void beginTest(String description, Object... args) {
        ++testNo;
        descriptions.format("%02d: %s\n", testNo, String.format(description, args));
        descriptions.flush();
        try {
            out = new PrintWriter(String.format("tests/%02d", testNo));
        } catch (FileNotFoundException e) {
            throw new AssertionError(e);
        }
    }

    void endTest() {
        out.close();
        assert !out.checkError();
        out = null;
    }

    private void randomTest(int n, int maxInsert, int maxDelete, double queryRatio) {
        n = n * 9 / 10 + random.nextInt(n / 10);
        beginTest("random n = %d, maxInsert = %d, maxDelete = %d, queryRatio = %.2f", n, maxInsert, maxDelete, queryRatio);
        int length = 0;
        int randoms = (int) (n - Math.max(n * queryRatio - n / 3, 0));
        out.println(n);
        maxInsert = Math.min(maxInsert, MAX_NUMBER);
        maxDelete = Math.min(maxDelete, MAX_NUMBER);
        for (int i = 0; i < randoms; i++) {
            switch (length >= 2 ? random.nextInt(3) : 1) {
                case 0:
                    int i1 = random.nextInt(length);
                    int i2 = random.nextInt(length);
                    query(Math.min(i1, i2), Math.max(i1, i2));
                    break;
                case 1:
                    int index = random.nextInt(length + 1);
                    int len = random.nextInt(maxInsert) + 1;
                    length += len;
                    add(index, len);
                    break;
                case 2:
                    index = random.nextInt(length - 1);
                    len = random.nextInt(Math.min(length - index - 1, maxDelete)) + 1;
                    remove(index, len);
                    length -= len;
                    break;
            }
        }
        for (int i = randoms; i < n; i++) {
            int i1 = random.nextInt(length);
            int i2 = random.nextInt(length);
            query(Math.min(i1, i2), Math.max(i1, i2));
        }
        endTest();
    }

    private void remove(int index, int len) {
        out.println("- " + (index + 1) + " " + len);
    }

    private void add(int index, int len) {
        out.println("+ " + (index + 1) + " " + len + " " + genWord());
    }

    private void query(int min, int max) {
        out.println("? " + (min + 1) + " " + (max + 1));
    }

    private String genWord() {
        StringBuilder sb = new StringBuilder();
        for (int i = 0; i < 1; i++) {
            sb.append((char)('a' + random.nextInt(26)));
        }
        return sb.toString();
    }

    public void maxInsertTest(int n) {
        beginTest("Max insert n = %d", n);
        out.println(n);
        int length = 0;
        int d = Math.min(MAX_NUMBER, n);
        for (int i = 0; i < n - 1; i++) {
            add(random.nextInt(length + 1), d);
            length += d;
        }
        query(length / 10 - 1, (int) (length * (long) 9 / 10 - 1));
        endTest();
    }

    public void maxQueryTest(int n) {
        beginTest("Max query n = %d", n);
        out.println(n);
        int length = 0;
        int d = Math.min(MAX_NUMBER, n);
        for (int i = 0; i < n / 2; i++) {
            add(random.nextInt(length + 1), d);
            length += d;
        }
        for (int i = 0; i < n / 2; i++) {
            query(random.nextInt(length / 10), (int) (length * (long) 9 / 10 + random.nextInt(length / 10)) - 1);
        }
        endTest();
    }

    public void maxRandomQueryTest(int n) {
        beginTest("Max random query n = %d", n);
        out.println(n);
        int length = 0;
        int d = Math.min(MAX_NUMBER, n);
        for (int i = 0; i < n / 2; i++) {
            add(random.nextInt(length + 1), d);
            length += d;
        }
        for (int i = 0; i < n / 2; i++) {
            int i1 = random.nextInt(length);
            int i2 = random.nextInt(length);
            query(Math.min(i1, i2), Math.max(i1, i2));
        }
        endTest();
    }

    public void maxDeleteTest(int n) {
        beginTest("Max delete test n = %d", n);
        out.println(n);
        int length = 0;
        int d = Math.min(MAX_NUMBER, n);
        for (int i = 0; i < n / 2; i++) {
            add(random.nextInt(length + 1), d);
            length += d;
        }
        for (int i = 0; i < n / 2 - 1; i++) {
            remove(random.nextInt(length - d), d);
            length -= d;
        }
        query(length / 10 - 1, (int) (length * (long) 9 / 10 - 1));
        endTest();
    }

    private void splitQueryTest(int n) {
        beginTest("splitQuery n = %d", n);
        int length = 0;
        int d = Math.min(MAX_NUMBER, n);
        out.println(n);
        for (int i = 0; i < 2 * n / d; i++) {
            add(0, d);
            length += d;
        }
        n -= 2 * n / d;
        for (int i = 0; i < n / 2; i++) {
            query(2 * i, length - 2 * i - 1);
        }
        for (int i = 0; i < n / 2; i++) {
            query(2 * i + 1, length - 2 * i - 2);
        }
        endTest();
    }

    private void splitInsertTest(int n) {
        beginTest("splitInsertQuery n = %d", n);
        int length = 0;
        int d = Math.min(MAX_NUMBER, n);
        out.println(n);
        for (int i = 0; i < n / d; i++) {
            add(0, d);
            length += d;
        }
        n -= n / d;
        for (int i = n / 2 - 1; 0 <= i; i--) {
            add(i, d);
            length += d;
        }
        for (int i = n / 2; i < n; i++) {
            int i1 = random.nextInt(length);
            int i2 = random.nextInt(length);
            query(Math.min(i1, i2), Math.max(i1, i2));
        }
        endTest();
    }

    private void splitDeleteTest(int n) {
        beginTest("splitDeleteQuery n = %d", n);
        int length = 0;
        int d = Math.min(MAX_NUMBER, n);
        out.println(n);
        for (int i = 0; i < 2 * n / d; i++) {
            add(0, d);
            length += d;
        }
        n -= 2 * n / d;
        for (int i = n / 2 - 1; i >= 0; i--) {
            remove(3 * i, 1);
            length -= 1;
        }
        for (int i = n / 2; i < n; i++) {
            int i1 = random.nextInt(length);
            int i2 = random.nextInt(length);
            query(Math.min(i1, i2), Math.max(i1, i2));
        }
        endTest();
    }

    public void sampleTest() {
        beginTest("Sample");
        out.println("8\r\n+ 1 4 w\r\n+ 3 3 o\r\n? 2 3\r\n- 2 2\r\n? 2 3\r\n+ 2 2 t\r\n? 1 6\r\n- 1 6");
        endTest();
    }

    public void run() throws IOException {
        sampleTest();
        for (int i = 0; i < 10; i++) {
            randomTest((i + 1) * 10, 10, 10, 0.5);
        }

        int MAX_N = 30000;
        for (int n : new int[]{500, 10000, 20000, MAX_N}) {
            splitQueryTest(n);
            splitInsertTest(n);
            splitDeleteTest(n);
            maxDeleteTest(n);
            maxInsertTest(n);
            maxQueryTest(n);
            maxRandomQueryTest(n);
            randomTest(n, n, n / 10, 0.3);
            randomTest(n, n, n / 10, 0.5);
            randomTest(n, n, n / 10, 0.9);
        }
    }

    public static void main(String[] args) throws IOException {
        descriptions = new PrintWriter("tests/tests.lst");
        new Tests().run();
        descriptions.close();
    }
}

