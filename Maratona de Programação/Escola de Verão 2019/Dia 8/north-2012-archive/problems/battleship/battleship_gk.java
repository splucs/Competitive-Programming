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
/* Author               Georgiy Korneev                           */
/******************************************************************/

import java.util.*;
import java.io.*;

public class battleship_gk {
    static Scanner in;
    static PrintWriter out;

    void run() {
        int r = 0;
        int c = 0;
        for (int i = 0; i < 10; i++) {
            for (int j = 0; j < 10; j++) {
                if (in.nextInt() == 100) {
                    r = i;
                    c = j;
                }
            }
        }

        String[] rows = new String[10];
        if (c % 2 == 1) {
            rows[(r + 0) % 10] = "####.###.#";
            rows[(r + 2) % 10] = "###.#.#.##";
            rows[(r + 4) % 10] = "##.##.#...";
        } else {
            rows[(r + 0) % 10] = "###.#.#.##";
            rows[(r + 2) % 10] = "####.###.#";
            rows[(r + 4) % 10] = "##.##.#...";
        }
        for (String row : rows) {
            out.println(row == null ? ".........." : row);
        }
    }


    public static void main(String[] args) throws Exception {
        in = new Scanner(new File("battleship.in"));
        out = new PrintWriter("battleship.out");

        new battleship_gk().run();

        in.close();
        out.close();
    }
}

