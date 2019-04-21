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
/* Author               Vitaly Aksenov                            */
/******************************************************************/

import java.io.*;
import java.util.*;

public class electricity_va implements Runnable {
	public static void main(String[] args) {
		new Thread(new electricity_va()).run();
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
		int n = nextInt();
		int m = nextInt();

		ArrayList<Integer> a = new ArrayList<Integer>();
		for (int i = 0; i < n; i++) {
			a.add(nextInt());
		}

		ArrayList<Integer> B = new ArrayList<Integer>();
		for (int i = 0; i < m; i++) {
			B.add(nextInt());
		}

		Collections.sort(a);
		Collections.sort(B);

		int ap = 1;
		int bp = 0;

		int ai = n - 1;
		int bi = m - 1;

		while (true) {
			while (bp > 0 && bi >= 0) {
				bp--;
				ap += B.get(bi--);
			}
			if (ai < 0 || bi < 0)
				break;
			ap--;
			bp += a.get(ai--);
		}

		out.println(ap);
	}

	public void run() {
		try {
			br = new BufferedReader(new FileReader("electricity.in"));
			out = new PrintWriter("electricity.out");

			solve();

			out.close();
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}
}

