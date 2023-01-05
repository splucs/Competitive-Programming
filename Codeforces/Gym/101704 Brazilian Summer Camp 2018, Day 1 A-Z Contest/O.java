import java.util.Scanner;
import java.math.BigInteger;

public final class O {
	public static BigInteger gcd(BigInteger a, BigInteger b) {
		if (b.equals(BigInteger.ZERO)) return a;
		return gcd(b, a.remainder(b));
	}

	public static BigInteger lcm(BigInteger a, BigInteger b) {
		return a.divide(gcd(a, b)).multiply(b);
	}

	public static void main(String[] args) {
		Scanner sc = new Scanner(System.in);
		int n = sc.nextInt();
		BigInteger ans = BigInteger.ONE;
		for(int i = 1; i <= n; i++) {
			ans = lcm(ans, BigInteger.valueOf(i));
		}
		System.out.println(ans);
	}
}