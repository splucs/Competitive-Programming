import java.util.*;
import java.io.BufferedReader;
import java.io.BufferedWriter;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.FileWriter;
import java.io.InputStream;
import java.io.OutputStream;
import java.io.PrintStream;
import java.math.*;

public final class A {
	public static int gcd(int a, int b) {
		if (b == 0) return a;
		return gcd(b, a%b);
	}

	public static final int MAXN = 69;

	public static BigInteger pascal(final BigInteger n, final int k) {
		BigInteger ans = BigInteger.ONE;
		BigInteger cur = n.subtract(BigInteger.valueOf(k));
		for(int i = 1; i <= k; i++) {
			cur = cur.add(BigInteger.ONE);
			ans = ans.multiply(cur).divide(BigInteger.valueOf(i));
		}
		return ans;
	}

	public static boolean visAll[][];
	public static BigInteger cntAll[][];
	public static BigInteger countAll(final int n, final int t) {
		if (visAll[n][t]) return cntAll[n][t];
		if (n == 0 && t == 0) return BigInteger.ONE;
		if (n == 0 || t == 0) return BigInteger.ZERO;
		BigInteger ans = BigInteger.ZERO;
		for(int i = 1; i <= n; i++) {
			ans = ans.add(countFigures(i).multiply(countAll(n-i, t-1)));
		}
		visAll[n][t] = true;
		return cntAll[n][t] = ans;
	}

	public static boolean visCycle[][];
	public static BigInteger cntCycle[][];
	public static BigInteger countCycle(final int n, final int c) {
		if (visCycle[n][c]) return cntCycle[n][c];
		BigInteger ans = BigInteger.ZERO;
		for(int i = 1; i <= c; i++) {
			int m = gcd(i, c);
			if (n % (c/m) != 0) continue;
			ans = ans.add(countAll(n/(c/m), m));
		}
		ans = ans.divide(BigInteger.valueOf(c));
		visCycle[n][c] = true;
		return cntCycle[n][c] = ans;
	}

	public static boolean visMov[];
	public static BigInteger cntMov[];
	public static BigInteger countMov(final int n) {
		if (visMov[n]) return cntMov[n];
		BigInteger ans = BigInteger.ZERO;
		for(int c = 1; c <= n; c++) {
			BigInteger cur = countCycle(n, c);
			ans = ans.add(cur);
		}
		visMov[n] = true;
		return cntMov[n] = ans;
	}

	public static boolean visFig[][];
	public static BigInteger cntFig[][];
	public static BigInteger countFigures(final int n, final int m) {
		if (visFig[n][m]) return cntFig[n][m];
		if (m == 0) {
			visFig[n][m] = true;
			if (n == 0) return cntFig[n][m] = BigInteger.ONE;
			else return cntFig[n][m] = BigInteger.ZERO;
		}
		BigInteger ans = BigInteger.ZERO;
		for(int i = 0; i*m <= n; i++) {
			BigInteger k = countMov(m);
			BigInteger cur = pascal(k.add(BigInteger.valueOf(i-1)), i)
				.multiply(countFigures(n-i*m, m-1));
			ans = ans.add(cur);
		}
		visFig[n][m] = true;
		return cntFig[n][m] = ans;
	}

	public static BigInteger countFigures(int n) {
		return countFigures(n-1, n-1);
	}

	public static void main(String[] args) throws Exception {
		InputStream in = new FileInputStream("abstract.in");
		PrintStream out = new PrintStream("abstract.out");

		visFig = new boolean[MAXN][MAXN];
		cntFig = new BigInteger[MAXN][MAXN];
		visMov = new boolean[MAXN];
		cntMov = new BigInteger[MAXN];
		visCycle = new boolean[MAXN][MAXN];
		cntCycle = new BigInteger[MAXN][MAXN];
		visAll = new boolean[MAXN][MAXN];
		cntAll = new BigInteger[MAXN][MAXN];

		Scanner sc = new Scanner(in);
		int caseNo = 0;
		while(true) {
			int n = sc.nextInt();
			if (n == 0) break;
			caseNo++;
			out.println("Case " + caseNo + ": " + countMov(n));
		}
		sc.close();
		in.close();
		out.close();
	}
}