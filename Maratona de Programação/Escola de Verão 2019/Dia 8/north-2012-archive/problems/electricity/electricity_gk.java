/******************************************************************/
/* ACM ICPC 2012-2013, NEERC                                      */
/* Northern Subregional Contest                                   */
/* St Petersburg, November 3, 2012                                */
/******************************************************************/
/* Problem E. Electricity                                         */
/*                                                                */
/* Original idea        Vitaly Aksenov                            */
/* Problem statement    Sergey Poromov                            */
/* Test set             Sergey Poromov                            */
/******************************************************************/
/* Solution                                                       */
/*                                                                */
/* Author               Georgiy Korneev                           */
/******************************************************************/

import java.util.*;
import java.io.*;

public class electricity_gk {
    static Scanner in;
    static PrintWriter out;

    void run() {
        long[] ab = new long[in.nextInt()];
        long[] ba = new long[in.nextInt()];
        for (int i = 0; i < ab.length; i++) {
            ab[i] = in.nextLong();
        }
        for (int i = 0; i < ba.length; i++) {
            ba[i] = in.nextLong();
        }
        Arrays.sort(ab);
        Arrays.sort(ba);
        int abi = ab.length;
        int bai = ba.length;
        int aSockets = 1;
        int bSockets = 0;
        while (true) {
            while (bSockets > 0 && bai > 0) {
                bSockets--;
                aSockets += ba[--bai];
            }
            if (bai == 0 || abi == 0) {
                break;
            }
            aSockets--;
            bSockets += ab[--abi];
        }
        out.println(aSockets);
    }


    public static void main(String[] args) throws Exception {
        Locale.setDefault(Locale.ENGLISH);
        in = new Scanner(new File("electricity.in"));
        out = new PrintWriter("electricity.out");

        new electricity_gk().run();

        in.close();
        out.close();
    }
}

