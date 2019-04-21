/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem D. Deepest Station                                     */
/*                                                                */
/* Original idea        Oleg Davydov                              */
/* Problem statement    Oleg Davydov                              */
/* Test set             Oleg Davydov                              */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author               Georgiy Korneev                           */
/******************************************************************/

import java.util.*;
import java.io.*;

public class deepest_gk {
    static Scanner in;
    static PrintWriter out;

    void run() {
        int x = in.nextInt();
        int y = in.nextInt();
        int d = in.nextInt();
        int z2 = x * x + y * y;
        if (z2 > d * d) {
            out.println("Impossible");
        } else if (z2 < d * d) {
            double a = 0.5 * (d * d - z2) / d;
            double z = Math.sqrt(z2);
            out.format("%.12f %.12f %.12f\n", -y * a / z, x * a / z, d - a);
        } else {
            out.println("Single staircase");
        }
    }


    public static void main(String[] args) throws Exception {
        Locale.setDefault(Locale.ENGLISH);
        in = new Scanner(new File("deepest.in"));
        out = new PrintWriter("deepest.out");

        new deepest_gk().run();

        in.close();
        out.close();
    }
}

