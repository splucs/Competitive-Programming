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
/* Author               Sergey Poromov                            */
/******************************************************************/

import java.util.*;
import java.io.*;

public class electricity_sp implements Runnable {
    public static void main(String[] args) {
        new Thread(new electricity_sp()).start();
    }

    @Override
    public void run() {
        try {
            br = new BufferedReader(new FileReader("electricity.in"));
            out = new PrintWriter("electricity.out");
            solve();
            out.close();
        } catch (FileNotFoundException e) {
        }
    }

    BufferedReader br;
    StringTokenizer st;
    PrintWriter out;
    boolean eof = false;

    String nextToken() {
        while (st == null || !st.hasMoreTokens()) {
            try {
                st = new StringTokenizer(br.readLine());
            } catch (Exception e) {
                eof = true;
                return "0";
            }
        }
        return st.nextToken();
    }

    int nextInt() {
        return Integer.parseInt(nextToken());
    }

    double nextDouble() {
        return Double.parseDouble(nextToken());
    }

    long nextLong() {
        return Long.parseLong(nextToken());
    }

    final int MAXNM = 100000;
    final int MAX = 1000;

    void solve() {
        int n = nextInt();
        assert((0 <= n) && (n <= MAXNM));
        int m = nextInt();
        assert((0 <= m) && (m <= MAXNM));
        int[] a = new int[n];
        for (int i = 0; i < n; i++) {
            a[i] = nextInt();
            assert((1 <= a[i]) && (a[i] <= MAX));
        }
        int[] b = new int[m];
        for (int i = 0; i < m; i++) {
            b[i] = nextInt();
            assert((1 <= b[i]) && (b[i] <= MAX));
        }
        Arrays.sort(a);
        Arrays.sort(b);
        long ans = 1;
        for (int i = n - 1, j = m - 1; i >= 0 && j >= 0; i--) {
            int cnt = a[i];
            ans--;
            while (cnt > 0 && j >= 0) {
                cnt--;
                ans += b[j--];
            }
        }
        out.println(ans);
    }
}

