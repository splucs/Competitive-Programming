import java.io.BufferedReader;
import java.io.FileInputStream;
import java.io.FileReader;
import java.io.InputStream;
import java.io.PrintStream;
import java.math.BigInteger;
import java.util.Scanner;

public final class B {
//public final class Main {

	public static BigInteger pwn[], pwx[], pwnx[];
	public static BigInteger dp[][][];

	public static BigInteger power(int a, int b) {
		if (b == 0) return BigInteger.ONE;
		BigInteger c = power(a, b/2);
		c = c.multiply(c);
		if (b%2 != 0) c = c.multiply(BigInteger.valueOf(a));
		return c;
	}

	public static BigInteger solve(int n, final int l, final int r, final int less, final int great) {
		//System.out.println("r-l: " + (r-l) + " less: " + less + " great: " + great);
		if (dp[r-l][less][great] != null) {
			return dp[r-l][less][great];
		}
		if (r == l+1) {
			int aless = less;
			if (aless > 0) aless--;
			//System.out.println("(l,r):" + l + "," + r + " less: " + less + " great: " + great + " x: " + x);
			return dp[r-l][less][great] = pwx[aless].multiply(pwnx[great]).multiply(pwn[n-aless-great-1]);
		}
		int m = (l + r) / 2;
		return dp[r-l][less][great] = solve(n, l, m, less, great+1)
			.add(solve(n, m, r, less+1, great));
	}

	public static void main(String args[]) throws Exception {
		InputStream in = System.in;
		PrintStream out = System.out;
		//InputStream in = new FileInputStream("binary.in");
		//PrintStream out = new PrintStream("binary.out");
		
		Scanner sc = new Scanner(in);
		int n = sc.nextInt();

		pwn = new BigInteger[n+1];
		pwn[0] = BigInteger.ONE;
		for(int i = 1; i <= n; i++) {
			pwn[i] = pwn[i-1].multiply(BigInteger.valueOf(n));
		}


		pwx = new BigInteger[11];
		pwnx = new BigInteger[11];
		BigInteger ans = BigInteger.ZERO;
		for(int x = 1; x <= n; x++) {
			pwx[0] = pwnx[0] = BigInteger.ONE;
			for(int j = 1; j <= 10; j++) {
				pwx[j] = pwx[j-1].multiply(BigInteger.valueOf(x));
				pwnx[j] = pwnx[j-1].multiply(BigInteger.valueOf(n-x));
			}
			dp = new BigInteger[n+1][11][11];

			ans = ans.add(solve(n, 0, n, 0, 0));
		}
		out.println(ans);

		sc.close();
		in.close();
		out.close();
	}
}