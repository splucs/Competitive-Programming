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
/* Solution                                                       */
/*                                                                */
/* Author               Georgiy Korneev                           */
/******************************************************************/

import java.util.*;
import java.io.*;

public class aztec_gk {
    static Scanner in;
    static PrintWriter out;

    void run() {
        int n = in.nextInt();
        int h = 0;
        for (int l = 1, c = 1; c <= n; h++, l += h * 4, c += l);
        out.println(h);
    }


    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("aztec.in"));
        out = new PrintWriter("aztec.out");

        new aztec_gk().run();

        in.close();
        out.close();
    }
}

