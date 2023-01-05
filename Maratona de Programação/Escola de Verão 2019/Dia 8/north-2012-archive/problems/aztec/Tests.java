/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem A. Aztec Pyramid                                       */
/*                                                                */
/* Original idea        Georgiy Korneev                           */
/* Problem statement    Georgiy Korneev                           */
/* Test set             Georgiy Korneev                           */
/******************************************************************/
/* Tests                                                          */
/*                                                                */
/* Author               Georgiy Korneev                           */
/******************************************************************/

import java.io.File;
import java.io.FileNotFoundException;
import java.io.PrintWriter;
import java.io.IOException;
import java.util.Scanner;

public class Tests {
    int testNo = 1;

    public void printTest(String line) {
        PrintWriter out = null;
        new File("tests").mkdir();
        try {
            out = new PrintWriter("tests/" + testNo / 10 + testNo % 10);
        } catch (FileNotFoundException e) {
            e.printStackTrace();
            return;
        }

        out.println(line);

        out.close();
        testNo++;
    }

    public void run() throws IOException {
        final Scanner in = new Scanner(new File("tests.lst"));
        while (in.hasNextLine()) {
            printTest(in.nextLine());
        }
    }

    public static void main(String[] args) throws IOException {
        new Tests().run();
    }
}

