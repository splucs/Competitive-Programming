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
/* Tests                                                          */
/*                                                                */
/* Author               Maxim Buzdalov                            */
/******************************************************************/

import java.io.*;
import java.util.*;

public class Tests {
    private static final int MAX_N = 50;
    private static final List<Integer> samples = Arrays.asList(6, 12);

    public static void main(String[] args) throws IOException {
        new File("tests").mkdir();
        int[] tests = new int[MAX_N];
        for (int i = 0; i < samples.size(); ++i) {
            tests[i] = samples.get(i);
        }
        for (int i = 1, j = 2; i <= MAX_N; ++i) {
            if (!samples.contains(i)) {
                tests[j++] = i;
            }
        }
        for (int i = 0; i < tests.length; ++i) {
            PrintWriter out = new PrintWriter(String.format("tests/%02d", i + 1));
            out.println(tests[i]);
            out.close();
        }
    }
}

