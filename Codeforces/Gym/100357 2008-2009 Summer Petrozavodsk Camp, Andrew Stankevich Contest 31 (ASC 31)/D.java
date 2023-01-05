import java.io.FileInputStream;
import java.io.FileOutputStream;
import java.io.InputStream;
import java.io.PrintStream;
import java.math.BigInteger;
import java.util.Scanner;

public final class Main {

	public static BigInteger pascal(BigInteger n, int k, BigInteger z) {
		BigInteger ans = BigInteger.ONE;
		for(int i = 1; i <= k; i++) {
			ans = ans.multiply(n).divide(BigInteger.valueOf(i));
			if (z.compareTo(ans) < 0) return ans;
			n = n.subtract(BigInteger.ONE);
		}
		return ans;
	}

	public static BigInteger search(final int k, final BigInteger z) {
		BigInteger lo = BigInteger.ZERO;
		BigInteger hi = z;
		while(hi.compareTo(lo.add(BigInteger.ONE)) == 1) {
			BigInteger mid = hi.add(lo).divide(BigInteger.valueOf(2));
			int cmp = pascal(mid, k, z).compareTo(z);
			if (cmp == 0) return mid;
			if (cmp < 0) lo = mid;
			if (cmp > 0) hi = mid;
		}
		return z;
	}

	public static void main(String args[]) throws Exception {
		InputStream in = new FileInputStream("discuss.in");
		PrintStream out = new PrintStream(new FileOutputStream("discuss.out"));
		//InputStream in = System.in;
		//PrintStream out = System.out;

		Scanner sc = new Scanner(in);

		BigInteger z = sc.nextBigInteger();
		BigInteger n = z;
		for(int k = 1; k <= 200; k++) {
			BigInteger cur = search(k, z);
			if (cur.compareTo(n) < 0) n = cur;
		}
		out.println(n);

		in.close();
		out.close();
	}
}