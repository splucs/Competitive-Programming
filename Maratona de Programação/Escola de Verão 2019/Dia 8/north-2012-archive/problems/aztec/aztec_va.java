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
/* Author               Vitaly Aksenov                            */
/******************************************************************/

import java.io.*;
import java.util.*;

public class aztec_va implements Runnable {
	public static void main(String[] args) {
		new Thread(new aztec_va()).run();
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
		long n = nextInt();

		long h = 1;
		n--;
		while (n >= 0) {
			n -= 2 * h * h + 2 * h + 1;
			h++;
		}
		h--;

		out.println(h);
	}

	public void run() {
		try {
			br = new BufferedReader(new FileReader("aztec.in"));
			out = new PrintWriter("aztec.out");

			solve();

			out.close();
		} catch (IOException e) {
			e.printStackTrace();
			System.exit(1);
		}
	}
}

