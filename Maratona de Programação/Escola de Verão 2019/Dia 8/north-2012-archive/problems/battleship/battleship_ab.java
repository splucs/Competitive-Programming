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
/* Solution                                                       */
/*                                                                */
/* Author               Anton Bannykh                             */
/******************************************************************/

import java.io.*;
import java.util.*;

public class battleship_ab {

    final static String[] STUB = new String[]{"####.##.##", "###.###.##", "#.#.#.....", ".........."};

    public static void main(String[] arg) throws IOException {
        Scanner in = new Scanner(new File("battleship.in"));
        PrintWriter out = new PrintWriter("battleship.out");
        int li, lj;
        li = lj = -1;
        for (int i = 0; i < 10; ++i) {
            for (int j = 0; j < 10; ++j) {
                if (in.nextInt() == 100) {
                    li = i;
                    lj = j;
                }
            }
        }

        int j = 0;
        for (int i = 0; i < 10; ++i) {
            if ((i ^ li) % 2 == 0) {
                if (i == li) {
                    out.print(STUB[3].substring(0, lj));
                    out.print("#");
                    out.println(STUB[3].substring(lj + 1, 10));
                } else {
                    out.println(STUB[j++]);
                }
            } else {
                out.println(STUB[3]);
            }
        }
        out.close();
    }
}
