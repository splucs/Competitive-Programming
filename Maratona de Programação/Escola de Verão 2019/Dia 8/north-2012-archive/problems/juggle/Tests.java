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

    private void writeTest(final String description, final int l, final String... criteria) {
        writeTest(description, l, Arrays.asList(criteria));
    }

    private void writeTest(final String description, final int l, final List<String> criteria) {
        beginTest(description);
        out.println(criteria.size() + " " + l);
        for (String criterion : criteria) {
            out.println(criterion);
        }
        endTest();
    }

    private void sampleTest() {
        writeTest("Sample", 4, "<==<>", "<<<<<", "=====");
    }

    List<String> allCriteria;
    private void maxTest(final int l) {
        if (allCriteria == null) {
            allCriteria = new ArrayList<>();
            for (int i = 0; i < 3 * 3 * 3 * 3 * 3; i++) {
                String criterion = "";
                int p = 1;
                for (int j = 0; j < 5; j++) {
                    criterion = criterion + "<=>".charAt(i / p % 3);
                    p *= 3;
                }
                allCriteria.add(criterion);
            }
        }
        Collections.shuffle(allCriteria, random);
        writeTest("max, l = " + l, l, allCriteria);
    }

    private final Random random = new Random(302740238);
    private void randomTest(final int l) {
        List<String> criteria = new ArrayList<>();
        for (int i = 0; i < 3 * 3 * 3 * 3 * 3; i++) {
            criteria.add(allCriteria.get(random.nextInt(200)));
        }
        writeTest("random, l = " + l, l, criteria);
    }

    public void run() throws IOException {
        sampleTest();

        for (int i = 1; i <= 10; i++) {
            maxTest(i);
        }
        randomTest(10);
        for (int i : new int[]{20, 30, 100, 300, 997, 1000}) {
            maxTest(i);
        }
        randomTest(1000);
    }

    public static void main(String[] args) throws IOException {
        new File("tests").mkdir();
        descriptions = new PrintWriter("tests/tests.lst");
        new Tests().run();
        descriptions.close();
    }
}

