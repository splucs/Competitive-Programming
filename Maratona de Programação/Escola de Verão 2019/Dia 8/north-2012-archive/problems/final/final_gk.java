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
/* Solution                                                       */
/*                                                                */
/* Author               Georgiy Korneev                           */
/******************************************************************/

import java.util.*;
import java.io.*;

public class final_gk {
    static Scanner in;
    static PrintWriter out;

    void run() {
        int n = in.nextInt();
        int x = in.nextInt();
        int k = in.nextInt();
        int d = in.nextInt() - 1;

        if (d != 0) {
            int best = x - d * (d - 1) / 2;
            if (best <= d) {
                out.println("Wrong information");
            } else {
                out.println(best);
                for (int i = 1; i < d; i++) {
                    out.println(d - i);
                }
                for (int i = d; i < n; i++) {
                    out.println(0);
                }
            }
        } else if (x % k == 0) {
            for (int i = 0; i < k; i++) {
                out.println(x / k);
            }
            for (int i = k; i < n; i++) {
                out.println(0);
            }
        } else if (k < n && x / k * (n - k) >= x % k) {
            int f = x / k;
            for (int i = 0; i < k; i++) {
                out.println(f);
                 x -= f;
            }
            for (int i = k; i < n; i++) {
                int s = Math.min(f, x);
                out.println(s);
                x -= s;
            }
        } else {
            out.println("Wrong information");
        }
    }


    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("final.in"));
        out = new PrintWriter("final.out");

        new final_gk().run();

        in.close();
        out.close();
    }
}

