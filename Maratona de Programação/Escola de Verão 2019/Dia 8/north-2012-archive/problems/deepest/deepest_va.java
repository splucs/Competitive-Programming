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
/* Author               Vitaly Aksenov                            */
/******************************************************************/

import java.io.*;
import java.util.*;

public class deepest_va implements Runnable {
    public static void main(String[] args) {
        new Thread(new deepest_va()).run();
    }

    BufferedReader br;
    StringTokenizer in;
    PrintWriter out;

    public String nextToken() throws IOException {
        while (in == null || !in.hasMoreTokens()) {
            in = new StringTokenizer(br.readLine());
        }

        return in.nextToken();
    }

    public int nextInt() throws IOException {
        return Integer.parseInt(nextToken());
    }

    public long nextLong() throws IOException {
        return Long.parseLong(nextToken());
    }

    public double nextDouble() throws IOException {
        return Double.parseDouble(nextToken());
    }

    public void solve() throws IOException {
        int x = nextInt();
        int y = nextInt();
        int d = nextInt();

        if (x * x + y * y > d * d) {
            out.println("Impossible");
            return;
        }

        if (x * x + y * y == d * d) {
            out.println("Single staircase");
            return;
        }

        double z = .5 * (x * x + y * y - d * d) / (x - d);
        out.println(z + " " + 0 + " " + (d - z));
    }

    public void run() {
        try {
            br = new BufferedReader(new FileReader("deepest.in"));
            out = new PrintWriter("deepest.out");

            solve();

            out.close();
        } catch (IOException e) {
            e.printStackTrace();
            System.exit(1);
        }
    }
}

